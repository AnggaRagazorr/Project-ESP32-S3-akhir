# Project-ESP32-S3-akhir


INPUT
| **Komponen**        | **Fungsi**                          | **Pin ESP32-S3** |
| ------------------- | ----------------------------------- | ---------------- |
| Tombol START        | Menyalakan conveyor                 | Pin 21           |
| Tombol STOP         | Menghentikan conveyor               | Pin 19           |
| Potensiometer Speed | Mengatur kecepatan conveyor         | Pin 5            |
| Encoder CLK         | Membaca langkah encoder (Interrupt) | Pin 10           |
| Encoder DT          | Penentu arah encoder                | Pin 11           |

OUTPUT
| **Komponen**    | **Fungsi**                              | **Pin ESP32-S3** |
| --------------- | --------------------------------------- | ---------------- |
| OLED Display    | Menampilkan status, kecepatan & counter | SDA (8), SCL (9) |
| Servo Gate      | Menggerakkan gate pemisah barang        | Pin 42           |
| Stepper Coil B− | Menggerakkan motor stepper              | Pin 37           |
| Stepper Coil B+ | Menggerakkan motor stepper              | Pin 38           |
| Stepper Coil A+ | Menggerakkan motor stepper              | Pin 39           |
| Stepper Coil A− | Menggerakkan motor stepper              | Pin 40           |
