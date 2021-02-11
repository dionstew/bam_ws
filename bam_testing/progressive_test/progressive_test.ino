#include "HX711.h"
#include <Servo.h>
#define input 8 // pin input untuk menggantikan sensor loadcell pada proses debugging program
#define calibration_factor -2263000.0
// Deklarasi variabel servo
Servo servo;
bool buka, button;

// Deklarasi variabel untuk kendali
float data_berat, data_berat_awal;
int jam, menit, jumlah_ayam, batas_jumlah_pakan;
int x = 0;

// Deklarasi variabel untuk penggunaan fungsi serial
const byte numChars = 32;
char receivedChars[numChars];
boolean newData = false;
int i, data[3];
String servo_in, vol_in, berat_in, pakan_in, msg;

// Deklarasi sensor jarak untuk menghitung volume
// lumbung pakan
#define trigger_pin 3
#define echo_pin 4
long duration;
int data_jarak;
int jumlah_pakan;

// Deklarasi Sensor Loadcell HX711
const int LOADCELL_DOUT_PIN = 7;
const int LOADCELL_SCK_PIN = 6;
HX711 scale;

// Deklarasi penanda data masukan komunikasi
char startMarker = '<';       // Penanda awal
char endMarker = '>';         // Penanda akhir

void setup() {
  // Memulai setup untuk Serial pada baudrate 115200
  Serial.begin(115200);

  // Memulai setup untuk servo
  servo.attach(5);
  servo.write(0);

  // Memulai set up untuk sensor ultrasonik
  pinMode(trigger_pin, OUTPUT);
  pinMode(echo_pin, INPUT);

  // Memulai setting up sensor loadcell HX711
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(calibration_factor);                            // this value is obtained by calibrating the scale with known weights;
  scale.tare();                                       // reset the scale to 0

  // Memulai setup untuk support
  pinMode(input, INPUT_PULLUP);     // untuk debugging (ketika input berat gagal memanipulasi data untuk kendali servo)
  pinMode(LED_BUILTIN, OUTPUT);     // untuk indikator saja menggunakan LED yang terpasang pada pin 13, di set sebagai output
  digitalWrite(LED_BUILTIN, HIGH);  // untuk indikator saja menggunakan LED yang terpasang pada pin 13 dan diset sebagai HIGH/aktif
}

void loop() {

  static boolean recvInProgress = false;
  static byte ndx = 0;
  char rc;
  scale.power_up();

  // x digunakan untuk mengkondisikan pengendalian
  if (x == 0) {
    // Mungkin di bagian serial ini akan perlu direvisi.
    // tantangan selanjutnya adalah ketika pembacaan ultrasonik yang pakai delay, akankah
    // mengganggu susunan variabel serial ?
    while (Serial.available() > 0 && newData == false) {
      rc = Serial.read();
      if (recvInProgress == true) {
        if (rc != endMarker) {
          receivedChars[ndx] = rc;
          ndx++;
          if (ndx >= numChars) {
            ndx = numChars - 1;
          }
        }
        else {
          receivedChars[ndx] = '\0'; // terminate the string
          recvInProgress = false;
          ndx = 0;
          newData = true;
        }
      }
      else if (rc == startMarker) {
        recvInProgress = true;
      };
      if (newData == true) {
        char* b;
        newData = false;

        b = strtok(receivedChars, ",");
        while (b != NULL) {
          data[i] = atoi(b);
          b = strtok(NULL, ",");
          i++;
        }
        i = 0;
        jam = data[0];
        menit = data[1];
        jumlah_ayam = data[2];
        data_berat_awal = baca_berat();
        batas_jumlah_pakan = 10 * jumlah_ayam; // setiap ayam diberikan pakan sebanyak 200 gram. Maka persamaan menjadi y=50*x
        x = x + 1;
      }
    }
  };
  if (x == 1) {
    //-----------------------------------
    if (jam == 7) {
      if (menit == 0) {
        buka = true;
      }
      else {
        buka = false;
      }
    }
    //-----------------------------------
    else if (jam == 17) {
      if (menit == 0) {
        buka = true;
      }
      else {
        buka = false;
      }
    }
    //-----------------------------------
    else {
      buka = false;
    }
    //-----------------------------------
    x = x + 1;
  };
  if (x > 1) {
    // Mengecek kondisi berat pada sensor
    baca_berat();
    float delta_data_berat = data_berat - data_berat_awal;
    if (delta_data_berat > batas_jumlah_pakan) {
      buka = false;
      x = 0;
    }
    else if (digitalRead(input) == LOW) {
      buka = false;
      x = 0;
    }
  };
  // mengecek kondisi variabel buka untuk menggerakkan servo
  if (buka == true) {
    servo.write(90);
    servo_in = "buka";
  }
  else {
    servo.write(0);
    servo_in = "tutup";
  }
  baca_ultrasonik();
  baca_berat();
  Serial.print(x);
  Serial.print("\t");
  Serial.print(jam);
  Serial.print("\t");
  Serial.print(menit);
  Serial.print("\t");
  Serial.print(jumlah_ayam);
  Serial.print("\t");
  Serial.print(batas_jumlah_pakan);
  Serial.print("\t");
  Serial.print(data_berat);
  Serial.print("\t");
  Serial.println(data_jarak);
  //  Serial.print("berat: \t");
  //  Serial.println(data_berat);
  //buat_string();
  //Serial.println(msg);
}

void baca_ultrasonik()
{
  digitalWrite(trigger_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_pin, LOW);
  duration = pulseIn(echo_pin, HIGH);
  data_jarak = (duration / 2) / 29.1;
}

void baca_berat()
{
  data_berat = scale.get_units();
  data_berat = data_berat*1000;
}

void buat_string() {
  berat_in = String(data_berat);
  vol_in = String(jumlah_pakan);
  msg = berat_in + " " + vol_in + " " + servo_in;
}
