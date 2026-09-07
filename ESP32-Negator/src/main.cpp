#include <Arduino.h>
#include <WiFi.h>
#include <esp_wifi.h>
#include <fake_ssids.h>

// ================== CONFIG ==================
#define BUTTON_PIN 0  // Boot button on standard ESP32 boards (active LOW)
#define LED_PIN    2  // Onboard LED GPIO pin

uint8_t packet[200];
int packetLen = 0;
int ssidLenOffset = 0;
int ssidDataOffset = 0;
int channelOffset = 0;

int currentChannel = 1;
const int numSSIDs = sizeof(fakeSSIDs) / sizeof(fakeSSIDs[0]);

void initBeaconTemplate();
void sendBeacon(const char* ssid);

void setup() {
  Serial.begin(115200);
  delay(1000);
  pinMode(LED_PIN, OUTPUT);

  setCpuFrequencyMhz(240);
  // Clean start
  esp_wifi_stop();
  delay(100);
  WiFi.mode(WIFI_MODE_NULL);
  delay(100);

  WiFi.mode(WIFI_MODE_STA);
  esp_wifi_set_promiscuous(true);
  delay(200);

  initBeaconTemplate();

  uint8_t mac[6];

  unsigned long pressStartTime = 0;
  
  while (true) {
    // The boot button is active-LOW (reads LOW when pressed)
    if (digitalRead(BUTTON_PIN) == LOW) {
      if (pressStartTime == 0) {
        pressStartTime = millis(); // Start the timer on initial press
      } else if (millis() - pressStartTime >= 2000) {
        break; // Exit the setup block's blocking loop
      }
    } else {
      // Reset timer if the button is released prematurely
      pressStartTime = 0;
    }
    
    delay(20); // Prevent watchdog trigger and debounce slightly
  }

  // Turn LED on once the button check passes
  digitalWrite(LED_PIN, HIGH);
}

void loop() {
  for (int i = 0; i < numSSIDs; i++) {
    sendBeacon(fakeSSIDs[i]);
  }
}

void sendBeacon(const char* ssid) {
  esp_wifi_set_channel(currentChannel, WIFI_SECOND_CHAN_NONE);

  // Randomize Source MAC and BSSID at offset 10
    uint8_t mac[6];
    for (int i = 0; i < 6; i++) mac[i] = random(0, 256);
    memcpy(&packet[10], mac, 6);     // Source
    memcpy(&packet[16], mac, 6);     // BSSID

    // Update Channel
    packet[channelOffset] = currentChannel;

    // Update SSID Length and String data
    int ssidLen = strlen(ssid); 
    
    packet[ssidLenOffset] = ssidLen;
    memcpy(&packet[ssidDataOffset], ssid, ssidLen);

    // Compute final size and transmit instantly
    int currentSize = ssidDataOffset + ssidLen + 15; 
    esp_wifi_80211_tx(WIFI_IF_STA, packet, currentSize, false);
  
  //Channel switching logic
  currentChannel++;  
  if (currentChannel > 11) {
    currentChannel = 1;
  }
}

// 2. Run this ONCE in setup() to build the fixed template
void initBeaconTemplate() {
    int offset = 0;
    
    packet[offset++] = 0x80;  // Management, Beacon
    packet[offset++] = 0x00;
    packet[offset++] = 0x00;  // Duration
    packet[offset++] = 0x00;

    // Destination = broadcast
    for (int i = 0; i < 6; i++) packet[offset++] = 0xFF;

    // Skip Source MAC + BSSID (12 bytes total) - patched live
    offset += 12; 

    packet[offset++] = 0x00;  // Sequence control low
    packet[offset++] = 0x00;

    // Timestamp
    for (int i = 0; i < 8; i++) packet[offset++] = 0x00;

    packet[offset++] = 0x64;  // Beacon interval low
    packet[offset++] = 0x00;  // high

    packet[offset++] = 0x01;  // Capability low (open)
    packet[offset++] = 0x04;  // high

    // === SSID IE Placeholder ===
    packet[offset++] = 0x00;  // Element ID: SSID
    ssidLenOffset = offset++; // Save position for length byte
    ssidDataOffset = offset;  // Save position where string starts
    
    offset += 32;             // Reserve max 32 bytes for SSID space

    // Supported Rates (Static)
    packet[offset++] = 0x01;
    packet[offset++] = 0x08;
    const uint8_t rates[8] = {0x82, 0x84, 0x8b, 0x96, 0x12, 0x24, 0x48, 0x6c};
    memcpy(&packet[offset], rates, 8);
    offset += 8;

    // Channel IE Placeholder
    packet[offset++] = 0x03;
    packet[offset++] = 0x01;
    channelOffset = offset;   // Save position to update channel live
    packet[offset++] = 1;     

    // Extended Supported Rates (Static)
    packet[offset++] = 0x32;
    packet[offset++] = 0x04;
    const uint8_t ext_rates[4] = {0x0c, 0x18, 0x30, 0x60};
    memcpy(&packet[offset], ext_rates, 4);
    offset += 4;

    packetLen = offset;       // Baseline length
}