#include <ESP8266WiFi.h>
#include <time.h>
#include <SoftwareSerial.h>
#include <SimpleTimer.h>
#define BT_RX D7
#define BT_TX D8

SimpleTimer timer;

SoftwareSerial HM10(BT_RX,BT_TX);  // RX핀(7번)은 HM10의 TX에 연결 
                                   // TX핀(8번)은 HM10의 RX에 연결                                    

const char* ssid = "ecrc";  // AP SSID
const char* password = "ecrc1984"; // AP password

const int httpPort = 80;
String KMA_url = "/wid/queryDFSRSS.jsp?zone=";

const char* SERVER = "www.kma.go.kr";
String location=""; 
int count=0;

void weather();

void setup() 
{
  Serial.begin(115200);
  HM10.begin(9600);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) 
  {
    Serial.print(".");
    delay(1000);
  }
  
  timer.setInterval(2000,weather);
}

void loop() 
{
   timer.run();
   if(HM10.available())  //mySerial에 전송된 값이 있으면
   {
     KMA_url = "/wid/queryDFSRSS.jsp?zone="; //새로 값을 받으면 기존에 있던 url은 초기화 시킨다.
     char myChar = (char)HM10.read();  //mySerial int 값을 char 형식으로 변환
     location+=myChar;   //수신되는 문자를 myString에 모두 붙임 (1바이트씩 전송되는 것을 연결)
     delay(5);           //수신 문자열 끊김 방지
     count++;
   }

   if(count==10) //지역을 판별하는 코드는 10자리 이므로 10자리의 숫자를 받고 난 후에는 전체url에 복사해준다.
   {
    KMA_url+=location;
    location=""; //지역을 판별하는 변수 초기화 
    count=0;
   }
}

void weather()
{
  WiFiClient client;
  
  String a[3];
  int i=0;
  String temp;
  String wfEn;
  String reh;
  String tmp_str;
  
  if (client.connect(SERVER, httpPort)) 
  {
    client.print(String("GET ") + KMA_url + " HTTP/1.1\r\n" +
    "Host: " + SERVER + "\r\n" + 
    "Connection: close\r\n\r\n");

    delay(10);
    while(client.available()){
      String line = client.readStringUntil('\n');

      i= line.indexOf("</temp>");

      if(i>0){
        tmp_str="<temp>";
        temp = line.substring(line.indexOf(tmp_str)+tmp_str.length(),i);
        Serial.println(temp); 

      }

      i= line.indexOf("</wfEn>");

      if(i>0){
        tmp_str="<wfEn>";
        wfEn = line.substring(line.indexOf(tmp_str)+tmp_str.length(),i);
        Serial.println(wfEn);  
      }

      i= line.indexOf("</reh>");

      if(i>0){
        tmp_str="<reh>";
        reh = line.substring(line.indexOf(tmp_str)+tmp_str.length(),i);
        Serial.println(reh);  
        break;
      }
    }
  }

  Serial.println(KMA_url);
  delay(1000);
}

//1159068000
//4377025300
