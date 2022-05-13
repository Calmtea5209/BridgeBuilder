#include <SoftwareSerial.h>

#define RXD 52
#define TXD 53

SoftwareSerial esp32Serial(RXD, TXD);

void setup() {
  Serial.begin(9600);
  esp32Serial.begin(9600);
}
void loop() {
  if(esp32Serial.available()) {
    char a = esp32Serial.read();
    Serial.println(a);
  }
}
