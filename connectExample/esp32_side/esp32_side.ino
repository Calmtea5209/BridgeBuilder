#define RXD 5
#define TXD 18

HardwareSerial megaSerial(2);

void setup() {
  megaSerial.begin(9600, SERIAL_8N1, RXD, TXD);
}
void loop() {
  for(char i = 'a'; i <= 'z'; i++) {
    megaSerial.print(i);
  }
}
