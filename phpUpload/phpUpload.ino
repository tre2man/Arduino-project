//1번과 2번 입력을 7번과 8번 입력으로 이동
//1번과 2번은 I2C 통신을 위한 포트로 돌리기

//시간설정
// T(설정명령) + 년(00~99) + 월(01~12) + 일(01~31) + 시(00~23) + 분(00~59) + 초(00~59) + 요일(1~7, 일1 월2 화3 수4 목5 금6 토7)
// 예: T1605091300002 (2016년 5월 9일 13시 00분 00초 월요일)

//인터넷 연결 실패 방지를 위해 업로드 플래그를 추가

#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Wire.h>
#include <time.h>

#define DS3231_I2C_ADDRESS 0x68

//LCD를 쓰게 된다면?
//LiquidCrystal_I2C lcd1(0x27, 16, 2);
//LiquidCrystal_I2C lcd2(0x26, 16, 2);

const char* ssid     = "ppp";
const char* password = "0000003940";
String SERVER = "192.168.43.87";
String host = "/insert_data.php?";

//와이파이 서버 설정
WiFiServer server(80);
WiFiClient client;
HTTPClient http;

//네트워크 업로드 신호
bool uploadTrue = false;

//각 칸에 맞는 변수만 골라서 사용함.
static int Analog = A0;
static int Digital0 = D0;
//static int Digital1 = D1;
//static int Digital2 = D2;
static int Digital3 = D3;
static int Digital4 = D4;
static int Digital5 = D5;
static int Digital6 = D6;
static int Digital7 = D7;
static int Digital8 = D8;

//전역변수 이전 데이터 저장
int AnalogDataBefore = 0;
int digitalData0Before = 0;
//int digitalData1Before = 0;
//int digitalData2Before = 0;
int digitalData3Before = 0;
int digitalData4Before = 0;
int digitalData5Before = 0;
int digitalData6Before = 0;
int digitalData7Before = 0;
int digitalData8Before = 0;

//전역변수, 1시간 데이터 저장
int AnalogDataSave = 0;
int digitalData0Save = 0;
//int digitalData1Save = 0;
//int digitalData2Save = 0;
int digitalData3Save = 0;
int digitalData4Save = 0;
int digitalData5Save = 0;
int digitalData6Save = 0;
int digitalData7Save = 0;
int digitalData8Save = 0;

//Gas 태그
bool gasCheck = 1;

//시간 저장하는 변수
int Beforehours = 0;
String Sdates,Shours,Smonth,Sdate;
//~초*1000 마다 실행?
const long interval = 60000;
const long realinterval = 1000;
unsigned long preMil = 0;

//RTC 관련 변수
byte seconds, minutes, hours, day, date, month, year;
char weekDay[4];

byte tMSB, tLSB;
float temp3231;


void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("\nConnecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("Connected to WiFi\n\n");

  //각 핀에 맞게 입력핀 설정
  pinMode(Analog,INPUT);
  pinMode(Digital0,INPUT);
  //pinMode(Digital1,INPUT);
  //pinMode(Digital2,INPUT);
  pinMode(Digital3,INPUT);
  pinMode(Digital4,INPUT);
  pinMode(Digital5,INPUT);
  pinMode(Digital6,INPUT);
  pinMode(Digital7,INPUT);
  pinMode(Digital8,INPUT);

  //RTC 초기설정
  Wire.begin(D2, D1);
  get3231Date();

  Serial.print(weekDay);
  Serial.print(", 20");
  Serial.print(year, DEC);
  Serial.print("/");
  Serial.print(month, DEC);
  Serial.print("/");
  Serial.print(date, DEC);
  Serial.print(" - ");
  Serial.print(hours, DEC);
  Serial.print(":");
  Serial.print(minutes, DEC);
  Serial.print(":");
  Serial.println(seconds, DEC);

  Beforehours = hours;

  //LCD 실행
  //lcd1.begin();
  //lcd2.begin();
}

void loop() {
  //시간데이터 입출력
  watchConsole();
  get3231Date();

  //현재 데이터 수집
  int AnalogData = analogRead(A0);
  int digitalData0 = digitalRead(D0);
  //int digitalData1 = digitalRead(D1);
  //int digitalData2 = digitalRead(D2);
  int digitalData3 = digitalRead(D3);
  int digitalData4 = digitalRead(D4);
  int digitalData5 = digitalRead(D5);
  int digitalData6 = digitalRead(D6);
  int digitalData7 = digitalRead(D7);
  int digitalData8 = digitalRead(D8);

  //상태 변화 감지하면 횟수 증가
  if(digitalData0 != digitalData0Before) digitalData0Save++;
  //if(digitalData1 != digitalData1Before) digitalData1Save++;
  //if(digitalData2 != digitalData2Before) digitalData2Save++;
  if(digitalData3 != digitalData3Before) digitalData3Save++;
  if(digitalData4 != digitalData4Before) digitalData4Save++;
  if(digitalData5 != digitalData5Before) digitalData5Save++;
  if(digitalData6 != digitalData6Before) digitalData6Save++;
  if(digitalData7 != digitalData7Before) digitalData7Save++;
  if(digitalData8 != digitalData8Before) digitalData8Save++;

  //가스센서체크
  if(AnalogData > 500 && gasCheck == true) {
    AnalogDataSave++;
    gasCheck = false;
  }
  if(AnalogData < 500) gasCheck = true;

  //이전 데이터 입력
  digitalData0Before = digitalData0;
  //digitalData1Before = digitalData1;
  //digitalData2Before = digitalData2;
  digitalData3Before = digitalData3;
  digitalData4Before = digitalData4;
  digitalData5Before = digitalData5;
  digitalData6Before = digitalData6;
  digitalData7Before = digitalData7;
  digitalData8Before = digitalData8;

/*
  //1분당 한번씩 결과 표시
  unsigned long currentMil = millis();
  if(currentMil - preMil >= interval){
    preMil = currentMil;

    Serial.print(weekDay);
    Serial.print(", 20");
    Serial.print(year, DEC);
    Serial.print("/");
    Serial.print(month, DEC);
    Serial.print("/");
    Serial.print(date, DEC);
    Serial.print(" - ");
    Serial.print(hours, DEC);
    Serial.print(":");
    Serial.print(minutes, DEC);
    Serial.print(":");
    Serial.println(seconds, DEC);

    Serial.print("LivingRoom Count : ");
    Serial.println(digitalData0Save);
    Serial.print("Room1 Count : ");
    Serial.println(digitalData7Save);
    Serial.print("Room2 Count : ");
    Serial.println(digitalData8Save);
    Serial.print("Bathroom Count : ");
    Serial.println(digitalData3Save);
    Serial.print("Toilet Count : ");
    Serial.println(digitalData4Save);
    Serial.print("Water Count : ");
    Serial.println(digitalData5Save);
    Serial.print("PIR Count : ");
    Serial.println(digitalData6Save);
    Serial.print("Gas Count : ");
    Serial.println(AnalogDataSave);
    Serial.print("\n");
  }
*/

  //1초에 한번씩 시리얼 신호 
  unsigned long currentMil = millis();
  if(currentMil - preMil >= realinterval){
    preMil = currentMil;

    Serial.print(digitalData0Save);
    Serial.print("n");
    Serial.print(digitalData7Save);
    Serial.print("n");
    Serial.print(digitalData8Save);
    Serial.print("n");
    Serial.print(digitalData3Save);
    Serial.print("n");
    Serial.print(digitalData4Save);
    Serial.print("n");
    Serial.print(digitalData5Save);
    Serial.print("n");
    Serial.print(digitalData6Save);
    Serial.print("n");
    Serial.print(AnalogDataSave);
    Serial.print("p");
    Serial.print(weekDay);
    Serial.print(", 20");
    Serial.print(year, DEC);
    Serial.print("/");
    Serial.print(month, DEC);
    Serial.print("/");
    Serial.print(date, DEC);
    Serial.print(" - ");
    Serial.print(hours, DEC);
    Serial.print(":");
    Serial.print(minutes, DEC);
    Serial.print(":");
    Serial.println(seconds, DEC);
  }

 /*
  //LCD에 현재 상태 출력하는 곳
  lcd1.begin();
  lcd1.clear();
  lcd1.home();
  lcd1.print("LivingRoom : ");
  lcd1.print(digitalData0Save);
  lcd1.setCursor(0,1);
  lcd1.print("Bathroom : ");
  lcd1.print(digitalData3Save);

  lcd2.begin();
  lcd2.clear();
  lcd2.home();
  lcd2.print("Room1 : ");
  lcd2.print(digitalData7Save);
  lcd2.setCursor(0,1);
  lcd2.print("Room2 : ");
  lcd2.print(digitalData8Save);
  */

  //정각일 경우에 업로드 플래그 true
  if (hours != Beforehours) {
    uploadTrue = true;
    Beforehours = hours;
  }

  //시간당 한 번씩 데이터 업로드, 업로드 실패 시 10초뒤에 다시 시도
  if (uploadTrue) {
    WiFiClient client;

    if (client.connect(SERVER, 80) && uploadTrue) {
      Serial.print("LivingRoom Count : ");
      Serial.println(digitalData0Save);
      Serial.print("Room1 Count : ");
      Serial.println(digitalData7Save);
      Serial.print("Room2 Count : ");
      Serial.println(digitalData8Save);
      Serial.print("Bathroom Count : ");
      Serial.println(digitalData3Save);
      Serial.print("Toilet Count : ");
      Serial.println(digitalData4Save);
      Serial.print("Water Count : ");
      Serial.println(digitalData5Save);
      Serial.print("PIR Count : ");
      Serial.println(digitalData6Save);
      Serial.print("Gas Count : ");
      Serial.println(AnalogDataSave);
      Serial.print("\n");

      if(month < 10) Smonth = "0" + String(month);
      else Smonth = String(month);

      if(date < 10) Sdate = "0" + String(date);
      else Sdate = String(date);

      Sdates = "\"" + String("20") + String(year) + "-" + Smonth + "-" + Sdate + "\"";
      Shours = String(hours);
      Serial.println(Sdates);
      Serial.println(Shours);
      Serial.print("\n");

      client.print(String("GET ") +
      host + "LivingRoom=" + String(digitalData0Save) + "&Room1=" + String(digitalData7Save) + "&Room2=" + String(digitalData8Save) + "&Bathroom=" + String(digitalData3Save) + "&Toilet=" + String(digitalData4Save) + "&Water=" + String(digitalData5Save) + "&PIR=" + String(digitalData6Save)  + "&Gas=" + String(AnalogDataSave) + "&date=" + Sdates + "&time=" + Shours +
      " HTTP/1.1\r\n" + "Host: " + SERVER + "\r\n" + "Connection: close\r\n\r\n");

      Serial.println(String("GET ") +
      host + "LivingRoom=" + String(digitalData0Save) + "&Room1=" + String(digitalData7Save) + "&Room2=" + String(digitalData8Save) + "&Bathroom=" + String(digitalData3Save) + "&Toilet=" + String(digitalData4Save) + "&Water=" + String(digitalData5Save) + "&PIR=" + String(digitalData6Save)  + "&Gas=" + String(AnalogDataSave) + "&date=" + Sdates + "&time=" + Shours +
      " HTTP/1.1\r\n" + "Host: " + SERVER + "\r\n" + "Connection: close\r\n\r\n");

      uploadTrue = false;
    }
    else {
      Serial.println("DB 업로드에 실패했습니다.\n");
    }

    //저장해둔 변수 초기화
    digitalData0Save = 0;
    //digitalData1Save = 0;
    //digitalData2Save = 0;
    digitalData3Save = 0;
    digitalData4Save = 0;
    digitalData5Save = 0;
    digitalData6Save = 0;
    digitalData7Save = 0;
    digitalData8Save = 0;
    AnalogDataSave = 0;

    delay(1000);
  }
}

// 10진수를 2진화 10진수인 BCD 로 변환
byte decToBcd(byte val) {
  return ( (val/10*16) + (val%10) );
}

void watchConsole() {
  if (Serial.available()) {      // Look for char in serial queue and process if found
    if (Serial.read() == 84) {   //If command = "T" Set Date
      set3231Date();
      get3231Date();
      Serial.println(" ");
    }
  }
}

void set3231Date() {
  year    = (byte) ((Serial.read() - 48) *10 +  (Serial.read() - 48));
  month   = (byte) ((Serial.read() - 48) *10 +  (Serial.read() - 48));
  date    = (byte) ((Serial.read() - 48) *10 +  (Serial.read() - 48));
  hours   = (byte) ((Serial.read() - 48) *10 +  (Serial.read() - 48));
  minutes = (byte) ((Serial.read() - 48) *10 +  (Serial.read() - 48));
  seconds = (byte) ((Serial.read() - 48) * 10 + (Serial.read() - 48));
  day     = (byte) (Serial.read() - 48);

  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0x00);
  Wire.write(decToBcd(seconds));
  Wire.write(decToBcd(minutes));
  Wire.write(decToBcd(hours));
  Wire.write(decToBcd(day));
  Wire.write(decToBcd(date));
  Wire.write(decToBcd(month));
  Wire.write(decToBcd(year));
  Wire.endTransmission();
}

//RTC 시간 가져오기
void get3231Date() {
  // send request to receive data starting at register 0
  Wire.beginTransmission(DS3231_I2C_ADDRESS); // 104 is DS3231 device address
  Wire.write(0x00); // start at register 0
  Wire.endTransmission();
  Wire.requestFrom(DS3231_I2C_ADDRESS, 7); // request seven bytes

  if(Wire.available()) {
    seconds = Wire.read(); // get seconds
    minutes = Wire.read(); // get minutes
    hours   = Wire.read();   // get hours
    day     = Wire.read();
    date    = Wire.read();
    month   = Wire.read(); //temp month
    year    = Wire.read();

    seconds = (((seconds & B11110000)>>4)*10 + (seconds & B00001111)); // convert BCD to decimal
    minutes = (((minutes & B11110000)>>4)*10 + (minutes & B00001111)); // convert BCD to decimal
    hours   = (((hours & B00110000)>>4)*10 + (hours & B00001111)); // convert BCD to decimal (assume 24 hour mode)
    day     = (day & B00000111); // 1-7
    date    = (((date & B00110000)>>4)*10 + (date & B00001111)); // 1-31
    month   = (((month & B00010000)>>4)*10 + (month & B00001111)); //msb7 is century overflow
    year    = (((year & B11110000)>>4)*10 + (year & B00001111));
  }
  else {
    //oh noes, no data!
  }

  switch (day) {
    case 1:
      strcpy(weekDay, "Sun");
      break;
    case 2:
      strcpy(weekDay, "Mon");
      break;
    case 3:
      strcpy(weekDay, "Tue");
      break;
    case 4:
      strcpy(weekDay, "Wed");
      break;
    case 5:
      strcpy(weekDay, "Thu");
      break;
    case 6:
      strcpy(weekDay, "Fri");
      break;
    case 7:
      strcpy(weekDay, "Sat");
      break;
  }
}
