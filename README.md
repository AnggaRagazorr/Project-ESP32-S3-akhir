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
1. Multicore

### **Apa itu Multicore?**
Multicore adalah kemampuan mikrokontroler (seperti ESP32-S3) yang memiliki **lebih dari satu core CPU** sehingga dapat menjalankan beberapa task secara **paralel**.  
Dengan multicore, satu task dapat berjalan di Core 0, sementara task lain berjalan di Core 1 tanpa saling menghambat.

### **Contoh pada ESP32-S3**
ESP32-S3 memiliki **2 core (Core 0 dan Core 1)**.  
Task dapat ditempatkan pada core tertentu menggunakan:

```cpp
xTaskCreatePinnedToCore(
    taskFunction,      // Nama fungsi task
    "Task Name",       // Nama task
    4096,              // Stack size
    NULL,              // Parameter
    1,                 // Priority
    NULL,              // Task handle
    0                  // Nomor core: 0 atau 1
);
```
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
