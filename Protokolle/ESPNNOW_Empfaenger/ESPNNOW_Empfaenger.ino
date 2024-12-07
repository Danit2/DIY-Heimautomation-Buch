/*
Project:  ESP-NOW Empfänger
Author:   Thomas Edlinger for www.edistechlab.com
Date:     Created 06.03.2024
Version:  V1.0
IDE:      Arduino IDE 2.3.2

Required Board (Tools -> Board -> Boards Manager...)
 - Board: Arduino ESP32 Boards - by Arduino   V2.0.13

Required libraries (sketch -> include library -> manage libraries)
 - 
*/

#include <esp_now.h>
#include <WiFi.h>

// Pins for nine LEDs
const byte LEDPins[] = {2, 4, 5, 12, 13, 14, 15, 16, 17};  // Array with LED pins

// Define data structure with 9 inputs (for 9 LEDs)
typedef struct struct_message {
  byte a;
  byte b;
  byte c;
  byte d;
  byte e;
  byte f;
  byte g;
  byte h;
  byte i;
} struct_message;

struct_message myData;

void setup() {
  Serial.begin(115200);

  // Set LED pins as OUTPUT
  for (int i = 0; i < 9; i++) {
    pinMode(LEDPins[i], OUTPUT);
  }

  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_recv_cb(OnDataRecv);
}

// Callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.println("Received Data:");

  // Display received data in serial monitor for debugging
  Serial.printf("a: %d, b: %d, c: %d, d: %d, e: %d, f: %d, g: %d, h: %d, i: %d\n", 
    myData.a, myData.b, myData.c, myData.d, myData.e, myData.f, myData.g, myData.h, myData.i);

  // Control LEDs based on received data
  digitalWrite(LEDPins[0], myData.a == 1 ? HIGH : LOW);
  digitalWrite(LEDPins[1], myData.b == 1 ? HIGH : LOW);
  digitalWrite(LEDPins[2], myData.c == 1 ? HIGH : LOW);
  digitalWrite(LEDPins[3], myData.d == 1 ? HIGH : LOW);
  digitalWrite(LEDPins[4], myData.e == 1 ? HIGH : LOW);
  digitalWrite(LEDPins[5], myData.f == 1 ? HIGH : LOW);
  digitalWrite(LEDPins[6], myData.g == 1 ? HIGH : LOW);
  digitalWrite(LEDPins[7], myData.h == 1 ? HIGH : LOW);
  digitalWrite(LEDPins[8], myData.i == 1 ? HIGH : LOW);
}

void loop() {
  // No specific loop functionality, as LEDs are controlled by received data
}
