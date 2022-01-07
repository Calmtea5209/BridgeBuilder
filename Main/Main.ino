#include "function.h"

void setup() {
    Serial.begin(115200);
    WiFi_Setup();
    FirebaseSetup();
    MotorSetup();
}

void loop() {
    Move();
    BridgeWork();
    ReceiveFromFirebase();
}
