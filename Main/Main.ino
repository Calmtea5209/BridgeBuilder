#include "function.h"
void setup() {
  Serial.begin(115200);
  WiFi_Setup();
  MotorSetup();
  Firebase.begin(DATABASE_URL, DATABASE_SECRET);
  Firebase.reconnectWiFi(true);
}
void loop() {
  Move();
  BridgeWork();
  
}
