# Project-ESP32-S3-akhir

| Komponen      | GPIO | Task                 |
| ------------- | ---- | -------------------- |
| Stepper A−    | 37   | TaskStepper (Core 0) |
| Stepper B+    | 38   | TaskStepper (Core 0) |
| Stepper A+    | 39   | TaskStepper (Core 0) |
| Stepper B−    | 40   | TaskStepper (Core 0) |
| Servo         | 42   | TaskGate (Core 1)    |
| OLED SDA      | 8    | TaskOLED (Core 1)    |
| OLED SCL      | 9    | TaskOLED (Core 1)    |
| Encoder CLK   | 10   | interruptEncoder     |
| Encoder DT    | 11   | interruptEncoder     |
| Potensiometer | 5    | TaskPot (Core 1)     |
| Button Start  | 18   | TaskButtonStart      |
| Button Stop   | 19   | TaskButtonStop       |
| LED RUN       | 3    | TaskIndicator        |
| LED SORT      | 7    | TaskIndicator        |
| LED STOP      | 15   | TaskIndicator        |
| Buzzer        | 4    | TaskAlarm            |
