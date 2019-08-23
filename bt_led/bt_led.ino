#include <SoftwareSerial.h>
#define BT_RX D7
#define BT_TX D8

SoftwareSerial HM10(BT_RX,BT_TX);  // RX핀(7번)은 HM10의 TX에 연결 
                                   // TX핀(8번)은 HM10의 RX에 연결  


String location="";

void setup() 
{  
  Serial.begin(115200);
  HM10.begin(9600);
}
void loop() {
  
   while(HM10.available())  //mySerial에 전송된 값이 있으면
   {
     char myChar = (char)HM10.read();  //mySerial int 값을 char 형식으로 변환
     location+=myChar;   //수신되는 문자를 myString에 모두 붙임 (1바이트씩 전송되는 것을 연결)
     delay(5);           //수신 문자열 끊김 방지    
    }
}

//4719025300 구미
//1168066000 서울 
