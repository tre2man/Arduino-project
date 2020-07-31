#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <time.h>

const char* ssid     = "ppp";
const char* password = "0000003940";
String SERVER = "192.168.43.87";
String host = "/insert_data.php?";

//와이파이 서버 설정
WiFiServer server(80);
WiFiClient client;
HTTPClient http;

//~초마다 실행하기 위한 변수 시간 주의
unsigned long previousMillis = 0;
const long interval = 1000;
//const long interval = 3600000;

//각 칸에 맞는 변수만 골라서 사용함.
static int Analog = A0; 
static int Digital0 = D0; 
static int Digital1 = D1; 
static int Digital2 = D2; 
static int Digital3 = D3; 
static int Digital4 = D4; 
static int Digital5 = D5; 
static int Digital6 = D6; 
static int Digital7 = D7; 

//전역변수, 데이터 저장
int AnalogData = 0;
int digitalData0 = 0;
int digitalData1 = 0;
int digitalData2 = 0;
int digitalData3 = 0;
int digitalData4 = 0;
int digitalData5 = 0;
int digitalData6 = 0;
int digitalData7 = 0;

//시간 저장하는 변수
String date,times;
int timezone = 3; 
int dst = 0; 

int faketime = 0;

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("\nConnecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  //각 핀에 맞게 입력핀 설정
  pinMode(Analog,INPUT);
  pinMode(Digital0,INPUT);
  pinMode(Digital1,INPUT);
  pinMode(Digital2,INPUT);
  pinMode(Digital3,INPUT);
  pinMode(Digital4,INPUT);
  pinMode(Digital5,INPUT);
  pinMode(Digital6,INPUT);
  //pinMode(Digital7,INPUT);

  //시간 알기 위한 소스
  configTime(3 * 3600, 0, "pool.ntp.org", "time.nist.gov"); 
  Serial.println("\nWaiting for time");
  while (!time(nullptr)) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("");
}

void loop() {  
  
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    
    AnalogData = analogRead(A0);
    digitalData0 = digitalRead(D0);
    digitalData1 = digitalRead(D1);
    digitalData2 = digitalRead(D2);
    digitalData3 = digitalRead(D3);
    digitalData4 = digitalRead(D4);
    digitalData5 = digitalRead(D5);
    digitalData6 = digitalRead(D6);
    //digitalData7 = digitalRead(D7);

    Serial.print("LivingRoom Status : ");
    Serial.println(digitalData0);
    Serial.print("Room1 Status : ");
    Serial.println(digitalData1);
    Serial.print("Room2 Status : ");
    Serial.println(digitalData2);ㄴ
    Serial.print("Bathroom Status : ");
    Serial.println(digitalData3);
    Serial.print("Toilet Status : ");
    Serial.println(digitalData4);
    Serial.print("Water Status : ");
    Serial.println(digitalData5);
    Serial.print("PIR Status : ");
    Serial.println(digitalData6);
    Serial.print("Gas Status : ");
    Serial.println(AnalogData);

    time_t now = time(nullptr); 
    struct tm * timeinfo;
    timeinfo = localtime(&now);

    String Syear = String((timeinfo->tm_year)-100, DEC);
    String Smonth = String((timeinfo->tm_mon)+1, DEC);
    String Sday = String((timeinfo->tm_mday), DEC);
    String Shour = String((timeinfo->tm_hour), DEC);
    String Smin = String((timeinfo->tm_min), DEC);
    String Ssec = String((timeinfo->tm_sec), DEC);

    if((timeinfo->tm_mon)+1<10) Smonth =  "0" + String((timeinfo->tm_mon)+1);
    if((timeinfo->tm_mday)<10) Sday =  "0" + String(timeinfo->tm_mday);
    if((timeinfo->tm_hour)<10) Shour =  "0" + String(timeinfo->tm_hour);
    if((timeinfo->tm_min)<10) Smin =  "0" + String(timeinfo->tm_min);
    if((timeinfo->tm_sec)<10) Ssec =  "0" + String(timeinfo->tm_sec);

    date = Syear + "-" + Smonth + "-" + Sday; 
    //times = Shour;
    times = Shour + Smin;
  
    upload();
  }
}

//수집한 데이터를 업로드 하는 코드
void upload() {

  WiFiClient client;

  if (client.connect(SERVER, 80))
  {
    client.print(String("GET ") + 
    host + "LivingRoom=" + String(digitalData0) + "&Room1=" + String(digitalData1) + "&Room2=" + String(digitalData2) + "&Bathroom=" + String(digitalData3) + "&Toilet=" + String(digitalData4) + "&Water=" + String(digitalData5) + "&PIR=" + String(digitalData1)  + "&Gas=" + String(digitalData1) + "&date=" + String(date) + "&time=" + String(times) +
    " HTTP/1.1\r\n" + "Host: " + SERVER + "\r\n" + "Connection: close\r\n\r\n");

    Serial.println(String("GET ") + 
   host + "LivingRoom=" + String(digitalData0) + "&Room1=" + String(digitalData1) + "&Room2=" + String(digitalData2) + "&Bathroom=" + String(digitalData3) + "&Toilet=" + String(digitalData4) + "&Water=" + String(digitalData5) + "&PIR=" + String(digitalData1)  + "&Gas=" + String(digitalData1) + "&date=" + String(date) + "&time=" + String(times) +
    " HTTP/1.1\r\n" + "Host: " + SERVER + "\r\n" + "Connection: close\r\n\r\n");
  }
}
