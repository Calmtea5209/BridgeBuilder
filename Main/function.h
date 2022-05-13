#include <analogWrite.h>

#include <WiFi.h>

#include <FirebaseESP32.h>

//Provide the token generation process info.
#include "addons/TokenHelper.h"

/* 1. Define the WiFi credentials */
#define WIFI_SSID "MICS_LAB"
#define WIFI_PASSWORD "nlhsmics306"

/* 2. Define the API Key */
#define API_KEY "AIzaSyBgWVxIW9gwANRMVaRMvIR9-swS3P9Jq8Q"

/* 3. Define the RTDB URL */
#define DATABASE_URL "https://bridgebuilder-1f47d-default-rtdb.firebaseio.com/" //<databaseName>.firebaseio.com or <databaseName>.<region>.firebasedatabase.app

/* 4. Define the user Email and password that alreadey registerd or added in your project */
#define DATABASE_SECRET "yFry1xgDH4sdihZtkBikL2U812rOdzOoZpXpKBle"

/* 5. Define FirebaseESP8266 data object for data sending and receiving */
FirebaseData fbdo;

/* 6. Define the FirebaseAuth data for authentication data */
FirebaseAuth auth;

/* 7. Define the FirebaseConfig data for config data */
FirebaseConfig config;

#define A_1A 21
#define A_1B 22
#define B_1A 23
#define B_1B 25
#define C_1A 26
#define C_1B 27
#define D_1A 32
#define D_1B 33

int Degree = 0;

String BridgeStatus;
String Direction;

void WiFi_Setup() {
    WiFi.disconnect(); //Disconnect
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("WiFi connecting");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(300);
    }
    Serial.println();
    Serial.println("WiFi connected");
    delay(1000);
    Serial.println("IP:" + WiFi.localIP().toString()); //Read IP address
}

void FirebaseSetup() {
    /* 8. Assign the api key (required) */
    config.api_key = API_KEY;

    /* 10. Assign the RTDB URL (required) */
    config.database_url = DATABASE_URL;

    /* 11. Assign the callback function for the long running token generation task */
    config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h

    //Or use legacy authenticate method
    Firebase.begin(DATABASE_URL, DATABASE_SECRET);

    /* 13. Enable auto reconnect the WiFi when connection lost */
    Firebase.reconnectWiFi(true);

    Serial.println("Firebase Initialized!");
}

void MotorSetup() {
    pinMode(A_1A, OUTPUT);
    pinMode(A_1B, OUTPUT);
    pinMode(B_1A, OUTPUT);
    pinMode(B_1B, OUTPUT);
    pinMode(C_1A, OUTPUT);
    pinMode(C_1B, OUTPUT);
    pinMode(D_1A, OUTPUT);
    pinMode(D_1B, OUTPUT);
    digitalWrite(A_1A, LOW);
    digitalWrite(A_1B, LOW);
    digitalWrite(B_1A, LOW);
    digitalWrite(B_1B, LOW);
    digitalWrite(C_1A, LOW);
    digitalWrite(C_1B, LOW);
    digitalWrite(D_1A, LOW);
    digitalWrite(D_1B, LOW);
}

void ReceiveFromFirebase() {
    if (Firebase.getString(fbdo, "/BridgeBuilder/Direction")) {
        //Success
        Serial.print("Direction: ");
        Serial.println(fbdo.stringData());

        Direction = fbdo.stringData();
    } else {
        //Failed?, get the error reason from fbdo
        Serial.print("Error in getInt, ");
        Serial.println(fbdo.errorReason());
        Direction = "fuck up";
    }

    if (Firebase.getString(fbdo, "/BridgeBuilder/BridgeStatus")) {
        //Success
        Serial.print("BridgeStatus: ");
        Serial.println(fbdo.stringData());

        BridgeStatus = fbdo.stringData();
    } else {
        //Failed?, get the error reason from fbdo
        Serial.print("Error in getInt, ");
        Serial.println(fbdo.errorReason());
        BridgeStatus = "fuck up";
    }
}

void Forward() {
    digitalWrite(A_1A, HIGH);
    digitalWrite(A_1B, LOW);
    digitalWrite(B_1A, HIGH);
    digitalWrite(B_1B, LOW);
}

void Backward() {
    digitalWrite(A_1A, LOW);
    digitalWrite(A_1B, HIGH);
    digitalWrite(B_1A, LOW);
    digitalWrite(B_1B, HIGH);
}

void TurnRight() {
    digitalWrite(A_1A, HIGH);
    digitalWrite(A_1B, LOW);
    digitalWrite(B_1A, LOW);
    digitalWrite(B_1B, HIGH);
}

void TurnLeft() {
    digitalWrite(A_1A, LOW);
    digitalWrite(A_1B, HIGH);
    digitalWrite(B_1A, HIGH);
    digitalWrite(B_1B, LOW);
}

void Stop() {
    digitalWrite(A_1A, LOW);
    digitalWrite(A_1B, LOW);
    digitalWrite(B_1A, LOW);
    digitalWrite(B_1B, LOW);
    digitalWrite(C_1A,LOW);
    digitalWrite(C_1B,LOW);
    digitalWrite(D_1A,LOW);
    digitalWrite(D_1B,LOW);
}

void Rod_A_Forward() {
    digitalWrite(C_1A, HIGH);
    digitalWrite(C_1B, 255);
}

void Rod_B_Forward() {
    digitalWrite(D_1A, HIGH);
    digitalWrite(D_1B, 255);
}

void Rod_A_Backward() {
    digitalWrite(C_1A, LOW);
    digitalWrite(C_1B, 255);
}

void Rod_B_Backward() {
    digitalWrite(D_1A, LOW);
    digitalWrite(D_1B, 255);
}

void Move() {
    if(Direction.length() > 1) {
        Direction = Direction[1];
    }
    if (Direction == "1") {
        Forward();
        Serial.println("Forward");
    } else if (Direction == "2") {
        TurnRight();
        Serial.println("TurnRight");
    } else if (Direction == "3") {
        Backward();
        Serial.println("Backward");
    } else if (Direction == "4") {
        TurnLeft();
        Serial.println("TurnLeft");
    } else {
        Stop();
        Serial.println("Stop");
    }
}

void BridgeWork() {
    if(BridgeStatus.length() > 1) {
        BridgeStatus = BridgeStatus[1];
    }
    if (BridgeStatus == "1") { //Put the bridge down
        if (Firebase.setString(fbdo, "/BridgeBuilder/BridgeStatus", " -1")) {
            //Success
            Serial.println("Set BridgeStatus:-1");
            /*while (true) { //Stop when reach certain degree
                Rod_A_Forward();
                delay(10);
                Degree++;
            }*/
        } else {
            //Failed?, get the error reason from fbdo

            Serial.print("Error in setString, ");
            Serial.println(fbdo.errorReason());
        }
        delay(200);
    } else if (BridgeStatus == "2") { //Take the bridge back
        if (Firebase.setString(fbdo, "/BridgeBuilder/BridgeStatus", "-2")) {
            //Success
            Serial.println("Set String data success");
            /*while(true) {
                Rod_A_Backward();
                delay(10);
                Degree--;
            }*/
        } else {
            //Failed?, get the error reason from fbdo
            Serial.print("Error in setString, ");
            Serial.println(fbdo.errorReason());
        }
        Rod_A_Backward();
        delay(200);
    }
}
