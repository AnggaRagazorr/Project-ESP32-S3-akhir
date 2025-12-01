# Project-ESP32-S3-akhir

| No | Nama Komponen        | Pin ESP32-S3                                      | Fungsi                                |
| -- | -------------------- | ------------------------------------------------- | ------------------------------------- |
| 1  | Tombol START         | GPIO 21                                           | Input untuk menyalakan conveyor       |
| 2  | Tombol STOP          | GPIO 19                                           | Input untuk menghentikan conveyor     |
| 3  | Potensiometer Speed  | GPIO 5                                            | Input analog untuk mengatur kecepatan |
| 4  | Rotary Encoder – CLK | GPIO 10                                           | Input interrupt channel A             |
| 5  | Rotary Encoder – DT  | GPIO 11                                           | Input channel B untuk arah            |
| 6  | Servo Gate           | GPIO 42                                           | Output PWM untuk menggerakkan servo   |
| 7  | Stepper B−           | GPIO 37                                           | Output coil B−                        |
| 8  | Stepper B+           | GPIO 38                                           | Output coil B+                        |
| 9  | Stepper A+           | GPIO 39                                           | Output coil A+                        |
| 10 | Stepper A−           | GPIO 40                                           | Output coil A−                        |
| 11 | OLED SDA             | (default SDA, biasanya GPIO 8 atau sesuai wiring) | Jalur data I²C                        |
| 12 | OLED SCL             | (default SCL, biasanya GPIO 9 atau sesuai wiring) | Jalur clock I²C                       |
