#include <Arduino.h>
#include <ESP32Servo.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// === Pin Mapping ===
#define LED_RUN 3
#define LED_SORT 7
#define LED_STOP 15
#define BTN_START 21
#define BTN_STOP 19
#define POT_SPEED 5

// Encoder Pins
#define CLK 14
#define DT 16
#define SW 17

// Servo Gate
#define SERVO_PIN 42

// Stepper Motor (Conveyor)
#define BMINUS 37
#define BPLUS 38
#define APLUS 39
#define AMINUS 40

// OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// === Global Variables ===
Servo gateServo;

QueueHandle_t speedQueue;
QueueHandle_t countQueue;
SemaphoreHandle_t oledMutex;

// Encoder Counter
volatile int encoderCount = 0;
volatile unsigned long lastEncoderTime = 0;

// Conveyor state
bool conveyorRunning = false;

// === Stepper Sequence ===
int seq[4][4] = {
  {1,0,0,1},
  {0,1,0,1},
  {0,1,1,0},
  {1,0,1,0}
};

// ===================================================================
// ENCODER ISR — FINAL FIX
// ===================================================================
void IRAM_ATTR encoderISR() {
  unsigned long now = micros();
  if (now - lastEncoderTime < 1500) return;  // debounce 1.5ms
  lastEncoderTime = now;

  // Logika arah yang sudah terbukti benar
  if (digitalRead(DT) == HIGH)
      encoderCount++;     // clockwise
  else
      encoderCount--;     // counter-clockwise
}

// ===================================================================
// TASK: Baca Pot → Speed Queue
// ===================================================================
void TaskPot(void *pvParameters) {
  while (1) {
    int speedVal = analogRead(POT_SPEED);
    speedVal = map(speedVal, 0, 4095, 2, 15);

    xQueueSend(speedQueue, &speedVal, 0);
    vTaskDelay(200 / portTICK_PERIOD_MS);
  }
}

// ===================================================================
// TASK: Stepper (Conveyor)
// ===================================================================
void TaskStepper(void *pvParameters) {
  pinMode(AMINUS, OUTPUT);
  pinMode(APLUS, OUTPUT);
  pinMode(BPLUS, OUTPUT);
  pinMode(BMINUS, OUTPUT);

  int speed = 5;

  while (1) {
    if (conveyorRunning) {
      xQueueReceive(speedQueue, &speed, 0);

      for (int i = 0; i < 4; i++) {
        digitalWrite(AMINUS, seq[i][0]);
        digitalWrite(APLUS, seq[i][1]);
        digitalWrite(BPLUS, seq[i][2]);
        digitalWrite(BMINUS, seq[i][3]);
        vTaskDelay(speed);
      }
    } else {
      vTaskDelay(50);
    }
  }
}

// ===================================================================
// TASK: Servo Sorting Gate
// ===================================================================
void TaskServoGate(void *pvParameters) {
  gateServo.attach(SERVO_PIN);

  while (1) {
    int count;
    if (xQueueReceive(countQueue, &count, 0)) {
      if (count % 5 == 0 && count != 0) {
        digitalWrite(LED_SORT, HIGH);
        gateServo.write(90);
        vTaskDelay(700 / portTICK_PERIOD_MS);
        gateServo.write(0);
        digitalWrite(LED_SORT, LOW);
      }
    }
    vTaskDelay(20);
  }
}

// ===================================================================
// TASK: OLED Display
// ===================================================================
void TaskOLED(void *pvParameters) {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  while (1) {
    if (xSemaphoreTake(oledMutex, portMAX_DELAY)) {

      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(WHITE);

      display.setCursor(0, 0);
      display.print("Conveyor: ");
      display.println(conveyorRunning ? "RUN" : "STOP");

      display.setCursor(0, 20);
      display.print("Counter: ");
      display.println(encoderCount);

      display.setCursor(0, 40);
      display.print("Speed: ");
      int sp;
      if (xQueueReceive(speedQueue, &sp, 0)) {}
      display.println(sp);

      display.display();

      xSemaphoreGive(oledMutex);
    }
    vTaskDelay(300 / portTICK_PERIOD_MS);
  }
}

// ===================================================================
// TASK: Start / Stop Button
// ===================================================================
void TaskButton(void *pvParameters) {
  pinMode(BTN_START, INPUT_PULLUP);
  pinMode(BTN_STOP, INPUT_PULLUP);

  while (1) {
    if (digitalRead(BTN_START) == LOW) {
      conveyorRunning = true;
      digitalWrite(LED_RUN, HIGH);
      digitalWrite(LED_STOP, LOW);
      vTaskDelay(300);
    }

    if (digitalRead(BTN_STOP) == LOW) {
      conveyorRunning = false;
      digitalWrite(LED_RUN, LOW);
      digitalWrite(LED_STOP, HIGH);
      vTaskDelay(300);
    }
    vTaskDelay(50);
  }
}

// ===================================================================
// TASK: Encoder → Send Queue
// ===================================================================
void TaskEncoder(void *pvParameters) {
  int lastSent = 0;

  while (1) {
    if (encoderCount != lastSent) {
      lastSent = encoderCount;

      int temp = encoderCount;
      xQueueSend(countQueue, &temp, 0);
    }
    vTaskDelay(20);
  }
}

// ===================================================================
// SETUP
// ===================================================================
void setup() {
  Serial.begin(115200);

  pinMode(LED_RUN, OUTPUT);
  pinMode(LED_SORT, OUTPUT);
  pinMode(LED_STOP, OUTPUT);

  digitalWrite(LED_STOP, HIGH);

  // Encoder pins
  pinMode(CLK, INPUT_PULLUP);
  pinMode(DT, INPUT_PULLUP);
  pinMode(SW, INPUT_PULLUP);

  // Queues & mutex
  speedQueue = xQueueCreate(10, sizeof(int));
  countQueue = xQueueCreate(10, sizeof(int));
  oledMutex = xSemaphoreCreateMutex();

  Wire.begin(8, 9);

  // Interrupt Encoder
  attachInterrupt(digitalPinToInterrupt(CLK), encoderISR, FALLING);

  // FreeRTOS Tasks
  xTaskCreatePinnedToCore(TaskPot,       "Pot",     3000, NULL, 2, NULL, 0);
  xTaskCreatePinnedToCore(TaskStepper,   "Stepper", 4000, NULL, 3, NULL, 0);

  xTaskCreatePinnedToCore(TaskServoGate, "Servo",   4000, NULL, 2, NULL, 1);
  xTaskCreatePinnedToCore(TaskOLED,      "OLED",    5000, NULL, 2, NULL, 1);
  xTaskCreatePinnedToCore(TaskButton,    "Button",  2000, NULL, 3, NULL, 1);
  xTaskCreatePinnedToCore(TaskEncoder,   "Encoder", 2000, NULL, 1, NULL, 1);
}

void loop() {
  // Loop tidak dipakai (RTOS)
}
