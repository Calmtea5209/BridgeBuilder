#include <WiFi.h>
#include <FirebaseESP32.h>
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
/* 1. Define the API Key */
#define API_KEY "AIzaSyBgWVxIW9gwANRMVaRMvIR9-swS3P9Jq8Q"
/* 2. Define the RTDB URL */
#define DATABASE_URL "https://bridgebuilder-1f47d-default-rtdb.firebaseio.com/" //<databaseName>.firebaseio.com or <databaseName>.<region>.firebasedatabase.app
/* 3. Define the user Email and password that alreadey registerd or added in your project */
#define DATABASE_SECRET "yFry1xgDH4sdihZtkBikL2U812rOdzOoZpXpKBle"
/* 4. Define FirebaseESP8266 data object for data sending and receiving */
FirebaseData fbdo;
/* 5. Define the FirebaseAuth data for authentication data */
FirebaseAuth auth;
/* 6. Define the FirebaseConfig data for config data */
FirebaseConfig config;

void WiFi_Setup(){
  WiFi.disconnect();//Disconnect
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
void Move(){
  if (Firebase.getString(fbdo, "/BridgeBuilder/Direction")) {
      //Success
      Serial.print("Direction: ");
      Serial.println(fbdo.stringData());
      if(fbdo.stringData() == "1"){
        Forward();
      }
      else if(fbdo.stringData() == "2"){
        TurnRight();
      }
      else if(fbdo.stringData() == "3"){
        Backward();
      }
      else if(fbdo.stringData() == "4"){
        TurnLeft();
      }
      else{
        Stop();
      }
  }
  else {
      //Failed?, get the error reason from fbdo
      Serial.print("Error in getInt, ");
      Serial.println(fbdo.errorReason());
  }
}
void BridgeWork(){
  if (Firebase.getString(fbdo, "/BridgeBuilder/BridgeStatus")) {
      //Success
      //Serial.print("BridgeStatus: ");
      String s = fbdo.stringData();
      Serial.println(s);
      if(s == "1"){ //Put the bridge down
        if (Firebase.setString(fbdo, "/Security_System_firebase/BridgeStatus", " -1")) {
              //Success
              Serial.println("Set String data success");
        } 
        else {
            //Failed?, get the error reason from fbdo

            Serial.print("Error in setString, ");
            Serial.println(fbdo.errorReason());
        }
        Rod_A_Forward();
        delay(200);
      }
      else if(fbdo.stringData() == "2"){ //Take the bridge back
        if (Firebase.setString(fbdo, "/Security_System_firebase/BridgeStatus", "-2")) {
              //Success
              Serial.println("Set String data success");
        } 
        else {
            //Failed?, get the error reason from fbdo

            Serial.print("Error in setString, ");
            Serial.println(fbdo.errorReason());
        }
        Rod_A_Backward();
        delay(200);
      }
  }
  else {
      //Failed?, get the error reason from fbdo
      Serial.print("Error in getInt, ");
      Serial.println(fbdo.errorReason());
  }
}
