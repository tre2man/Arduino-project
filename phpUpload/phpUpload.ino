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

//~초마다 실행하기 위한 1시간마다 1번 업로드
unsigned long previousMillis = 0;
//const long interval = 1000;
const long interval = 3600000;

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

//전역변수 이전 데이터 저장
int AnalogDataBefore = 0;
int digitalData0Before = 0;
int digitalData1Before = 0;
int digitalData2Before = 0;
int digitalData3Before = 0;
int digitalData4Before = 0;
int digitalData5Before = 0;
int digitalData6Before = 0;
int digitalData7Before = 0;

//전역변수, 1시간 데이터 저장
int AnalogDataSave = 0;
int digitalData0Save = 0;
int digitalData1Save = 0;
int digitalData2Save = 0;
int digitalData3Save = 0;
int digitalData4Save = 0;
int digitalData5Save = 0;
int digitalData6Save = 0;
int digitalData7Save = 0;

//시간 저장하는 변수
String date,times;
int timezone = 3; 
int dst = 0; 

int faketime = 0;
int first = 1;

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
  pinMode(Digital7,INPUT);

  //시간 알기 위한 소스
  configTime(3 * 3600, 0, "pool.ntp.org", "time.nist.gov"); 
  Serial.println("\n시간 설정 중...10초 소요");
  while (!time(nullptr)) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("");
}

void loop() {  

  //현재 데이터 수집
  int AnalogData = analogRead(A0);
  int digitalData0 = digitalRead(D0);
  int digitalData1 = digitalRead(D1);
  int digitalData2 = digitalRead(D2);
  int digitalData3 = digitalRead(D3);
  int digitalData4 = digitalRead(D4);
  int digitalData5 = digitalRead(D5);
  int digitalData6 = digitalRead(D6);
  int digitalData7 = digitalRead(D7);

  //상태 변화 감지하면 횟수 증가
  if(digitalData0 != digitalData0Before) digitalData0Save++;
  if(digitalData1 != digitalData1Before) digitalData1Save++;
  if(digitalData2 != digitalData2Before) digitalData2Save++;
  if(digitalData3 != digitalData3Before) digitalData3Save++;
  if(digitalData4 != digitalData4Before) digitalData4Save++;
  if(digitalData5 != digitalData5Before) digitalData5Save++;
  if(digitalData6 != digitalData6Before) digitalData6Save++;
  if(digitalData7 != digitalData7Before) digitalData7Save++;
  if(AnalogData > 50)  

  //이전 데이터 입력
  digitalData0Before = digitalData0;
  digitalData1Before = digitalData1;
  digitalData2Before = digitalData2;
  digitalData3Before = digitalData3;
  digitalData4Before = digitalData4;
  digitalData5Before = digitalData5;
  digitalData6Before = digitalData6;
  digitalData7Before = digitalData7;

  Serial.print("LivingRoom Count : ");
  Serial.println(digitalData0);
  Serial.print("Room1 Count : ");
  Serial.println(digitalData1);
  Serial.print("Room2 Count : ");
  Serial.println(digitalData2);
  Serial.print("Bathroom Count : ");
  Serial.println(digitalData3);
  Serial.print("Toilet Count : ");
  Serial.println(digitalData4);
  Serial.print("Water Count : ");
  Serial.println(digitalData5);
  Serial.print("PIR Count : ");
  Serial.println(digitalData6);
  Serial.print("Gas Count : ");
  Serial.println(AnalogData);
  Serial.print("\n");
  
  if (currentMillis - previousMillis >= interval && first == 0) {
    previousMillis = currentMillis;

    Serial.print("LivingRoom Count : ");
    Serial.println(digitalData0Save);
    Serial.print("Room1 Count : ");
    Serial.println(digitalData0Save);
    Serial.print("Room2 Count : ");
    Serial.println(digitalData0Save);
    Serial.print("Bathroom Count : ");
    Serial.println(digitalData0Save);
    Serial.print("Toilet Count : ");
    Serial.println(digitalData0Save);
    Serial.print("Water Count : ");
    Serial.println(digitalData0Save);
    Serial.print("PIR Count : ");
    Serial.println(digitalData0Save);
    Serial.print("Gas Count : ");
    Serial.println(AnalogData);
    Serial.print("\n");

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
    times = Shour;

    Serial.println(date);
    Serial.println(times);
    Serial.print("\n");
  
    //upload();

    //저장해둔 변수 초기화
    digitalData0Save = 0;
    digitalData1Save = 0;
    digitalData2Save = 0;
    digitalData3Save = 0;
    digitalData4Save = 0;
    digitalData5Save = 0;
    digitalData6Save = 0;
    digitalData7Save = 0;
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
