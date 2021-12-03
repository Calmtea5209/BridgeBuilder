//https://github.com/mobizt/Firebase-ESP32
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

void setup()
{

  Serial.begin(115200);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

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
}

void loop() {
  /* 14. Check the ready state of Firebase before calling other functions that related to data transfer */
  if (Firebase.ready()) {
    /* 15. Try to set int data to Firebase */
    //The set function returns bool for the status of operation
    //fbdo requires for sending the data and pass as the pointer
    if (Firebase.setString(fbdo, "/Security_System_firebase/opentimehour", "69")) {
      //Success
      Serial.println("Set String data success");
    } else {
      //Failed?, get the error reason from fbdo

      Serial.print("Error in setString, ");
      Serial.println(fbdo.errorReason());
    }

    /* 16. Try to get int data from Firebase */
    //The get function returns bool for the status of operation
    //fbdo requires for receiving the data
    if (Firebase.getString(fbdo, "/BridgeBuilder/Up")) {
      //Success
      Serial.print("Get int data success, int = ");
      Serial.println(fbdo.stringData());
    } else {
      //Failed?, get the error reason from fbdo

      Serial.print("Error in getInt, ");
      Serial.println(fbdo.errorReason());
    }
  }
}
