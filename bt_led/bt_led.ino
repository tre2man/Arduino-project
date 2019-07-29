#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); //블루투스의 Tx, Rx핀을 2번 3번핀으로 설정

const int LED=6;
char bt;

void setup() 
{
  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(LED,OUTPUT);
}

void loop() {
  if (Serial.available()) 
  {    //시리얼모니터에 입력된 데이터가 있다면
    mySerial.write(Serial.read());  //블루투스를 통해 입력된 데이터 전달
  }
  
  if (mySerial.available()) //블루투스로 받은 데이터가 있다면 실행 
  {
    bt=mySerial.read();
    Serial.write(bt);
    
    if(bt=='A')
      digitalWrite(LED,HIGH);
    if(bt=='B')
      digitalWrite(LED,LOW);
  }
}
