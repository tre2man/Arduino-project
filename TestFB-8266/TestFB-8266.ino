//
// Copyright 2015 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// FirebaseDemo_ESP8266 is a sample that demo the different functions
// of the FirebaseArduino API.

//Board : NodeMcu (0.9)

#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
//#include <CD74HC4067.h>
// Set these to run example.
#define FIREBASE_HOST "nodemcu-data-ceb31.firebaseio.com"
#define FIREBASE_AUTH "c52WPYw7gy7fy9xfg01TrH7F3BJlE0fuPcBgOdU2"
#define WIFI_SSID "ppp"
#define WIFI_PASSWORD "0000003940"

//CD74HC4067 my_mux(14, 12,13,13);

void setup() {
  Serial.begin(115200); 

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  
  pinMode(A0,INPUT);
  pinMode(D0,INPUT_PULLUP);
}



void loop() {
  /*
  {
    for (int i = 0; i < 4; i++) {
        my_mux.channel(i);
        delay(250);
        Serial.print(analogRead(A0));
        
        Serial.print(" ");
        switch(i) {
          case 0 :
            Firebase.setInt("Poten1",analogRead(A0)); break;
            case 1 :
            Firebase.setInt("Poten2",analogRead(A0)); break;
            case 2 :
            Firebase.setInt("IR",analogRead(A0)); break;
            case 3 :
            Firebase.setInt("Turbi",analogRead(A0)); break;
          }
      
    }
    */
  int Light = analogRead(A0);
  int Switch = digitalRead(D0)*1000;
    
  Firebase.setInt("Light Value",Light);
  Firebase.setInt("Switch Value",Switch);

  Serial.print(Light);
  Serial.print(" ");
  Serial.print(Switch);
  Serial.println();  
}

  
  /*
  // set value
  Firebase.setFloat("number", 42.0);
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(1000);
  
  // update value
  Firebase.setFloat("number", 43.0);
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(1000);

  // get value 
  Serial.print("number: ");
  Serial.println(Firebase.getFloat("number"));
  delay(1000);

  // remove value
  Firebase.remove("number");
  delay(1000);

  // set string value
  Firebase.setString("message", "hello world");
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /message failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(1000);
  
  // set bool value
  Firebase.setBool("truth", false);
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /truth failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(1000);

  // append a new value to /logs
  String name = Firebase.pushInt("logs", n++);
  // handle error
  if (Firebase.failed()) {
      Serial.print("pushing /logs failed:");
      Serial.println(Firebase.error());  
      return;
  }
  Serial.print("pushed: /logs/");
  Serial.println(name);
  delay(1000);
  */
