#include "function.h"

void setup() {
    Serial.begin(115200);
    WiFi_Setup();
    FirebaseSetup();
    MotorSetup();
}

int it = 0;

void loop() {
    Move();
    BridgeWork();
    delay(10);
    if(it >= 10) {
      ReceiveFromFirebase();
      it = 0;
    }
    it++;
}
