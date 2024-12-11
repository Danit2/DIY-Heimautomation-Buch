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
  byte g1;
  byte y1;
  byte r1;
  byte g2;
  byte y2;
  byte r3;
  byte g3;
  byte y3;
  byte r3;
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
  Serial.printf("g1: %d, y1: %d, r1: %d, g2: %d, y2: %d, r2: %d, g3: %d, y3: %d, r3: %d\n", 
    myData.g1, myData.y1, myData.r1, myData.g2, myData.y2, myData.r2, myData.g3, myData.y3, myData.r3);

  // Control LEDs based on received data
  digitalWrite(LEDPins[0], myData.g1 == 1 ? HIGH : LOW);
  digitalWrite(LEDPins[1], myData.y1 == 1 ? HIGH : LOW);
  digitalWrite(LEDPins[2], myData.r1 == 1 ? HIGH : LOW);
  digitalWrite(LEDPins[3], myData.g2 == 1 ? HIGH : LOW);
  digitalWrite(LEDPins[4], myData.y2 == 1 ? HIGH : LOW);
  digitalWrite(LEDPins[5], myData.r2 == 1 ? HIGH : LOW);
  digitalWrite(LEDPins[6], myData.g3 == 1 ? HIGH : LOW);
  digitalWrite(LEDPins[7], myData.y3 == 1 ? HIGH : LOW);
  digitalWrite(LEDPins[8], myData.r3 == 1 ? HIGH : LOW);
}

void loop() {
  // No specific loop functionality, as LEDs are controlled by received data
}
