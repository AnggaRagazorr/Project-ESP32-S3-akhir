#  ESP32-S3 Conveyor System — Stepper, Encoder, Servo, OLED (FreeRTOS Dual-Core)

Project ini merupakan sistem **Conveyor otomatis** berbasis **ESP32-S3** dengan fitur:
- Kontrol **Start / Stop** menggunakan tombol  
- Pengaturan kecepatan dengan **Potensiometer**  
- Pembacaan **Rotary Encoder** (interrupt) untuk menghitung putaran / item  
- Gerakan **Servo Gate** sebagai pemisah barang  
- Motor **Stepper** sebagai penggerak conveyor  
- Tampilan status pada **OLED SSD1306**  
- Berjalan secara paralel menggunakan **FreeRTOS (Dual-Core)**  

Project ini dirancang untuk demonstrasi line sorting sederhana / mini conveyor otomatis.

## IMPLEMENTASI YANG DIGUNAKAN
d. Multicore,Mutex,Queue (Semaphore Tambahan)

____________________________________________________
INPUT
| **Komponen**        | **Fungsi**                          | **Pin ESP32-S3** |
| ------------------- | ----------------------------------- | ---------------- |
| Tombol START        | Menyalakan conveyor                 | Pin 21           |
| Tombol STOP         | Menghentikan conveyor               | Pin 19           |
| Potensiometer Speed | Mengatur kecepatan conveyor         | Pin 5            |
| Encoder CLK         | Membaca langkah encoder (Interrupt) | Pin 10           |
| Encoder DT          | Penentu arah encoder                | Pin 11           |

____________________________________________________
OUTPUT
| **Komponen**    | **Fungsi**                              | **Pin ESP32-S3** |
| --------------- | --------------------------------------- | ---------------- |
| OLED Display    | Menampilkan status, kecepatan & counter | SDA (8), SCL (9) |
| Servo Gate      | Menggerakkan gate pemisah barang        | Pin 42           |
| Stepper Coil B− | Menggerakkan motor stepper              | Pin 37           |
| Stepper Coil B+ | Menggerakkan motor stepper              | Pin 38           |
| Stepper Coil A+ | Menggerakkan motor stepper              | Pin 39           |
| Stepper Coil A− | Menggerakkan motor stepper              | Pin 40           |
