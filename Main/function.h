#include <WiFi.h>
const char ssid[] = "MICS_LAB";
const char pass[] = "nlhsmics306";

void WiFi_Setup(){
  WiFi.disconnect();//斷線（初始化的意思）
  /*delay(100);
  Serial.println("Setup done");

  Serial.println("scan start");
  int n = WiFi.scanNetworks();//掃描網路，並將掃描到的網路數量存入n
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
  Serial.println("IP:"+WiFi.localIP().toString()); //讀取IP位址
}
