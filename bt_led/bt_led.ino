#include <SoftwareSerial.h>
#define BT_RX D7
#define BT_TX D8

SoftwareSerial BTSerial(BT_RX,BT_TX); //Connect HC-06. Use your (TX, RX) settings

void setup()  
{
  Serial.begin(9600);
  Serial.println("Hello!");

  BTSerial.begin(9600);  // set the data rate for the BT port
}

void loop()
{
  String input="";
  // BT –> Data –> Serial
  if (BTSerial.available()) {
    Serial.write(BTSerial.read());
    String input=BTSerial.read();
    Serial.print(input);
  }
  // Serial –> Data –> BT
  if (Serial.available()) {
    BTSerial.write(Serial.read());
  }
}
