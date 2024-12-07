/*
Project:  ESP-NOW Sender
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

// REPLACE WITH YOUR RECEIVER MAC Address
uint8_t broadcastAddress[] = {0x34, 0x85, 0x18, 0x7B, 0xF1, 0x14};
esp_now_peer_info_t peerInfo;

// Pins for three buttons
const byte buttonPin1 = 2; //D2
const byte buttonPin2 = 4; //D4
const byte buttonPin3 = 5; //D5

byte lastButtonState1 = LOW;
byte lastButtonState2 = LOW;
byte lastButtonState3 = LOW;
byte buttonState1 = LOW;
byte buttonState2 = LOW;
byte buttonState3 = LOW;

const byte debounceTime = 30;
unsigned long lastButtonTimeChange = 0;

// Define data structure with three inputs
typedef struct struct_message {
  byte a;
  byte b;
  byte c;
} struct_message;

struct_message myData;

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void setup() {
  Serial.begin(115200);

  // Initialize buttons as input with pull-up resistors
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);

  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_send_cb(OnDataSent);
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false; 

  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
}

void loop() {
  if (millis() - lastButtonTimeChange > debounceTime) {
    // Read button states
    buttonState1 = digitalRead(buttonPin1);
    buttonState2 = digitalRead(buttonPin2);
    buttonState3 = digitalRead(buttonPin3);

    // Check if button 1 state has changed
    if (buttonState1 != lastButtonState1) {
      lastButtonTimeChange = millis();
      lastButtonState1 = buttonState1;
      if (buttonState1 == LOW) {
        Serial.printf("Button 1 pressed!\n");
        myData.a = !buttonState1; // Toggle value for a
        esp_now_send(broadcastAddress, (uint8_t *)&myData, sizeof(myData));
      } else {
        Serial.printf("Button 1 released!\n");
        myData.a = !buttonState1; // Toggle value for a
        esp_now_send(broadcastAddress, (uint8_t *)&myData, sizeof(myData));
      }
    }

    // Check if button 2 state has changed
    if (buttonState2 != lastButtonState2) {
      lastButtonTimeChange = millis();
      lastButtonState2 = buttonState2;
      if (buttonState2 == LOW) {
        Serial.printf("Button 2 pressed!\n");
        myData.b = !buttonState2; // Toggle value for b
        esp_now_send(broadcastAddress, (uint8_t *)&myData, sizeof(myData));
      } else {
        Serial.printf("Button 2 released!\n");
        myData.b = !buttonState2; // Toggle value for b
        esp_now_send(broadcastAddress, (uint8_t *)&myData, sizeof(myData));
      }
    }

    // Check if button 3 state has changed
    if (buttonState3 != lastButtonState3) {
      lastButtonTimeChange = millis();
      lastButtonState3 = buttonState3;
      if (buttonState3 == LOW) {
        Serial.printf("Button 3 pressed!\n");
        myData.c = !buttonState3; // Toggle value for c
        esp_now_send(broadcastAddress, (uint8_t *)&myData, sizeof(myData));
      } else {
        Serial.printf("Button 3 released!\n");
        myData.c = !buttonState3; // Toggle value for c
        esp_now_send(broadcastAddress, (uint8_t *)&myData, sizeof(myData));
      }
    }
  }
}
