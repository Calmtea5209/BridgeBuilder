#include <WiFi.h>
const char ssid[] = "MICS_LAB";
const char pass[] = "nlhsmics306";
#define A_1A 36
#define A_1B 39
#define B_1A 34 
#define B_1B 35
#define C_1A 32 
#define C_1B 33
#define D_1A 25 
#define D_1B 26 
void WiFi_Setup(){
  WiFi.disconnect();//Disconnect
  /*delay(100);
  Serial.println("Setup done");

  Serial.println("scan start");
  int n = WiFi.scanNetworks();//Scan network
  Serial.println("scan done");
  if (n == 0) {
      Serial.println("no networks found");
  } else {
      Serial.print(n);
      Serial.println(" networks found");
      for (int i = 0; i < n; ++i) {
          //顯示無線網路SSID, RSSI, 加密
          Serial.print(i + 1);
          Serial.print(": ");
          Serial.print(WiFi.SSID(i));
          Serial.print(" (");
          Serial.print(WiFi.RSSI(i));
          Serial.print(")");
          Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
          delay(10);
      }
  }*/
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid,pass);
  Serial.print("WiFi connecting");
  while(WiFi.status()!= WL_CONNECTED){
    Serial.print(".");
    delay(1000);
  }
  Serial.println();
  Serial.println("WiFi connected");
  delay(1000);
  Serial.println("IP:"+WiFi.localIP().toString()); //Read IP address
}
void MotorSetup(){
  pinMode(A_1A,OUTPUT);
  pinMode(A_1B,OUTPUT);
  pinMode(B_1A,OUTPUT);
  pinMode(B_1B,OUTPUT);
  pinMode(C_1A,OUTPUT);
  pinMode(C_1B,OUTPUT);
  pinMode(D_1A,OUTPUT);
  pinMode(D_1B,OUTPUT);
  digitalWrite(A_1A,LOW);
  digitalWrite(A_1B,LOW);
  digitalWrite(B_1A,LOW);
  digitalWrite(B_1B,LOW);
  digitalWrite(C_1A,LOW);
  digitalWrite(C_1B,LOW);
  digitalWrite(D_1A,LOW);
  digitalWrite(D_1B,LOW);
}
void Forward(){
  digitalWrite(A_1A,HIGH);
  digitalWrite(A_1B,LOW);
  digitalWrite(B_1A,HIGH);
  digitalWrite(B_1B,LOW);
}
void Backward(){
  digitalWrite(A_1A,LOW);
  digitalWrite(A_1B,HIGH);
  digitalWrite(B_1A,LOW);
  digitalWrite(B_1B,HIGH);
}
void TurnRight(){
  digitalWrite(A_1A,HIGH);
  digitalWrite(A_1B,LOW);
  digitalWrite(B_1A,LOW);
  digitalWrite(B_1B,HIGH);
}
void TurnLeft(){
  digitalWrite(A_1A,LOW);
  digitalWrite(A_1B,HIGH);
  digitalWrite(B_1A,HIGH);
  digitalWrite(B_1B,LOW);
}
void Stop(){
  digitalWrite(A_1A,LOW);
  digitalWrite(A_1B,LOW);
  digitalWrite(B_1A,LOW);
  digitalWrite(B_1B,LOW);
}
void Rod_A_Forward(){
  digitalWrite(A_1A,HIGH);
  digitalWrite(A_1B,LOW);
}
void Rod_B_Forward(){
  digitalWrite(B_1A,HIGH);
  digitalWrite(B_1B,LOW);
}
void Rod_A_Backward(){
  digitalWrite(A_1A,LOW);
  digitalWrite(A_1B,HIGH);
}
void Rod_B_Backward(){
  digitalWrite(B_1A,LOW);
  digitalWrite(B_1B,HIGH);
}
