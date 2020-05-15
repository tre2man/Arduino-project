/*
 * Created by K. Suwatchai (Mobizt)
 * 
 * Email: k_suwatchai@hotmail.com
 * 
 * Github: https://github.com/mobizt
 * 
 * Copyright (c) 2019 mobizt
 *
*/



//Example shows how to connect to Firebase RTDB and perform basic operation for set, get, push and update data to database

//Required WiFiNINA Library for Arduino from https://github.com/arduino-libraries/WiFiNINA

//nano 33 iot board

#include "Firebase_Arduino_WiFiNINA.h"

#define FIREBASE_HOST "tai-cap.firebaseio.com"
#define FIREBASE_AUTH "IcWMWBG1cx0Co1ytrvDrYHhNXUG6hiFGxNXLl7R9"
#define WIFI_SSID "wlan20"
#define WIFI_PASSWORD "0000003940"
#define data1 A0
#define data2 A1
#define data3 A2

//Define Firebase data object
FirebaseData firebaseData;

String path = "/IOT33_TEST";
String jsonStr;

void setup()
{

  pinMode(data1,INPUT);
  pinMode(data2,INPUT);
  pinMode(data3,INPUT);
  Serial.begin(115200);
  delay(100);
  Serial.println();

  Serial.print("Connecting to Wi-Fi");
  int status = WL_IDLE_STATUS;
  while (status != WL_CONNECTED)
  {
    status = WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print(".");
    delay(300); 
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  //와이파이 실행 완료

  //Provide the autntication data
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH, WIFI_SSID, WIFI_PASSWORD);
  Firebase.reconnectWiFi(true);

  //파이어베이스 연결 완료
}

void loop()
{
  
  int a1=analogRead(data1);
  int a2=analogRead(data2);
  int a3=analogRead(data3);

  Serial.print(a1);
  Serial.print(" ");
  Serial.print(a2);
  Serial.print(" ");
  Serial.println(a3);
  
  jsonStr = "{\"AnalogData1" "\":" + String(a1) + "}" ;
  //Firebase.pushJSON(firebaseData, path , jsonStr);
  Firebase.updateNode(firebaseData, path , jsonStr);
  
  jsonStr = "{\"AnalogData2" "\":" + String(a2) + "}" ;
  Firebase.updateNode(firebaseData, path , jsonStr);
  
  jsonStr = "{\"AnalogData3" "\":" + String(a3) + "}" ;
  Firebase.updateNode(firebaseData, path , jsonStr);
  

  delay(1);
  
}
