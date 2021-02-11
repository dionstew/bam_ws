File ini merupakan petunjuk dari sistem yang telah dibuat ini.

Nomer pin arduino yang digunakan dan sambungannya terhadap komponen.
Arduino 3   ->  Trigger (HCSR-04)
Arduino 4   ->  Echo    (HCSR-04)
Arduino 5   ->  Signal  (Servo)
Arduino 6   ->  SCK     (Sensor Loadcell) 
Arduino 7   ->  DT      (Sensor Loadcell)

Jika ingin meng-copy paste program ini ke software Arduino IDE, buka alamat codes/src/main.cpp di direktori bam_ws.

Bagian yang di copy dimulai dari baris dibawah perintah "#include <Arduino.h>".
    #include <Arduino.h>
    #include <HX711.h>                     -> salin dari sini
    ...

