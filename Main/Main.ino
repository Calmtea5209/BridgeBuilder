#include "function.h"

void setup() {
    Serial.begin(115200);
    WiFi_Setup();
    FirebaseSetup();
    MotorSetup();
}

void loop() {
    payload = 0;
    Move();
    BridgeWork();
    ReceiveFromFirebase();
}
