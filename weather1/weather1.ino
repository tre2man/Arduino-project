//Board : NodeMcu 0.9 (keystudio Board)
//BT : HM-10 BLE Module (keystudio)

#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include <SimpleTimer.h> //인터럽트를 활용한 멀티태스킹 (타이머)
#include "FastLED.h" //네오픽셀 출력

#define BT_RX D7
#define BT_TX D8

#define DATA_PIN    6
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS    64
CRGB leds[NUM_LEDS];

#define BRIGHTNESS         120 //밝기
#define FRAMES_PER_SECOND  120 //프레임


FASTLED_USING_NAMESPACE //fastled 사용

SimpleTimer timer;  //타이머 선언


SoftwareSerial Bluetooth(BT_RX,BT_TX);  // RX핀(7번)은 HM10의 TX에 연결
                                        // TX핀(8번)은 HM10의 RX에 연결
/*
const char* ssid = "ecrc";  // AP SSID
const char* password = "ecrc1984"; // AP password
*/

/*
const char* ssid = "wlan20";  // AP SSID
const char* password = "0000003940"; // AP password
*/

const char* ssid = "969696";  // AP SSID
const char* password = "239239239"; // AP password


const int httpPort = 80;
String KMA_url = "/wid/queryDFSRSS.jsp?zone=1159068000";

const char* SERVER = "www.kma.go.kr";

void weather();

void setup()
{
  Serial.begin(115200);

  Bluetooth.begin(9600);

  timer.setInterval(2000,weather); //타이머를 주어서 일정시간마다 데이터를 불러올수 있게 한다

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("\nConnecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
}

typedef void(*patternlist[])();  //패턴 함수를 각 배열에 저장하는 새로운 타입, 구조체 생성
patternlist patterns={rain,thunder,sun,cloud,snow}; //구조체 안에 패턴함수를 저장
int CurrentPattern=0;

String location=""; 
String checkLocation="1000000000";

String temp_cpy=""; //온도 
String wfEn_cpy=""; //날씨
String reh_cpy="";  //습도

void loop() 
{
   timer.run();
   while(Bluetooth.available())  //mySerial에 전송된 값이 있으면
   {
     char myChar = (char)Bluetooth.read();  //mySerial int 값을 char 형식으로 변환
     location+=myChar;   //수신되는 문자를 myString에 모두 붙임 (1바이트씩 전송되는 것을 연결)
     delay(5);
   } 
   
   if(!location.equals("")) 
   {
    KMA_url = "/wid/queryDFSRSS.jsp?zone="; //새로 값을 받으면 기존에 있던 url은 초기화 시킨다.
    KMA_url+=location;
    checkLocation=location;
    location="";
   } 

   Serial.println(checkLocation);

   if(checkLocation=="1000000000") //자유 모드일 경우
   {
    patterns[CurrentPattern]();             //현재 나와야 하는 패턴 출력
    EVERY_N_SECONDS(5){next();}             //4초마다 새 패턴을 출력하게하는 함수 출력
   }
   else
   {
    if(wfEn_cpy=="Clear") sun();
    else if(wfEn_cpy=="Mostly Cloudy"||wfEn_cpy=="Cloudy") cloud();
    else if(wfEn_cpy=="Rain"||wfEn_cpy=="Rain/Snow"||wfEn_cpy=="Shower") rain();
    else if(wfEn_cpy=="Snow") snow();
   }
   
   FastLED.show();                           //네오픽셀 출력
   FastLED.delay(1000/FRAMES_PER_SECOND);    //딜레이를 준다
}

void next() //0~4 반복하는 함수
{
  CurrentPattern++;
  CurrentPattern%=5;
  FastLED.clear();
}

void weather() //기상청 서버에서 날씨 받아서 정보 리턴하기
{
  WiFiClient client;

  String a[3];
  int indexNum=0;
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
    while(client.available())
    {
      String line = client.readStringUntil('\n');

      indexNum= line.indexOf("</temp>");

      if(indexNum>0)
      {
        tmp_str="<temp>";
        temp = line.substring(line.indexOf(tmp_str)+tmp_str.length(),indexNum);
        if(temp!="") temp_cpy=temp;
        Serial.println(temp); 

      }

      indexNum= line.indexOf("</wfEn>");

      if(indexNum>0)
      {
        tmp_str="<wfEn>";
        wfEn = line.substring(line.indexOf(tmp_str)+tmp_str.length(),indexNum);
        if(wfEn!="") wfEn_cpy=wfEn;
        Serial.println(wfEn);  
      }

      indexNum= line.indexOf("</reh>");

      if(indexNum>0)
      {
        tmp_str="<reh>";
        reh = line.substring(line.indexOf(tmp_str)+tmp_str.length(),indexNum);
        if(reh!="") reh_cpy=reh;
        Serial.println(reh);  
        break;
      }
    }
  }

  Serial.println(KMA_url);
}

//구현한 날씨 : 비 맑음 번개  추가)눈 흐림

void rain() //비 효과
{
  int color=150;
  static int i=0;
  static int r1=0;
  static int r2=1;
  static int r3=2;
  static int r4=3;
  static int r5=4;
  static int r6=5;
  static int r7=6;
  static int r8=7;

  fadeToBlackBy( leds, NUM_LEDS, 100);

   if(i>0&&i<9)
   {
    leds[r2]=CHSV( color, 200, 255);
    r2+=8;
   }
   if(i>3&&i<12)
   {
    leds[r5]=CHSV( color, 200, 255);
    r5+=8;
   }
   if(i>6&&i<15)
   {
    leds[r1]=CHSV( color, 200, 255);
    r1+=8;
   }
   if(i>9&&i<18)
   {
    leds[r6]=CHSV( color, 200, 255);
    r6+=8;
   }
   if(i>12&&i<21)
   {
    leds[r8]=CHSV( color, 200, 255);
    r8+=8;
   }
   if(i>15&&i<24)
   {
    leds[r3]=CHSV( color, 200, 255);
    r3+=8;
   }
   if(i>18&&i<27)
   {
    leds[r7]=CHSV( color, 200, 255);
    r7+=8;
   }
   if(i>21&&i<30)
   {
    leds[r4]=CHSV( color, 200, 255);
    r4+=8;
   }

   i++;

   if(r1>64) r1=0;
   if(r2>64) r2=1;
   if(r3>64) r3=2;
   if(r4>64) r4=3;
   if(r5>64) r5=4;
   if(r6>64) r6=5;
   if(r7>64) r7=6;
   if(r8>64) r8=7;
   if(i>31) i=0;

  delay(80);
}

void snow() //눈 효과
{
  int arr[8]={0,9,16,25,32,41,48,57}; //날리면서 내리는 눈
  int color=150; //->흰색으로 수정

  fadeToBlackBy( leds, NUM_LEDS, 200);

  static int i=0;
  static int r1=0;
  static int r2=0;
  static int r3=0;
  static int r4=0;
  static int r5=0;
  static int r6=0;
  static int r7=0;
  static int r8=0;

   if(i>0&&i<9)
   {
    (leds[arr[r2]+1])=CRGB::White;
    r2++;
   }
   if(i>3&&i<12)
   {
    (leds[arr[r5]+4])=CRGB::White;
    r5++;
   }
   if(i>6&&i<15)
   {
    (leds[arr[r1]])=CRGB::White;
    r1++;
   }
   if(i>9&&i<18)
   {
    (leds[arr[r6]+5])=CRGB::White;
    r6++;
   }
   if(i>12&&i<21)
   {
    (leds[arr[r8]+7])=CRGB::White;
    r8++;
   }
   if(i>15&&i<24)
   {
    (leds[arr[r3]+2])=CRGB::White;
    r3++;
   }
   if(i>18&&i<27)
   {
    (leds[arr[r7]+6])=CRGB::White;
    r7++;
   }
   if(i>21&&i<30)
   {
    (leds[arr[r4]+3])=CRGB::White;
    r4++;
   }
   i++;

   if(r1>8) r1=0;
   if(r2>8) r2=0;
   if(r3>8) r3=0;
   if(r4>8) r4=0;
   if(r5>8) r5=0;
   if(r6>8) r6=0;
   if(r7>8) r7=0;
   if(r8>8) r8=0;
   if(i>27) i=0;

  delay(99);
}

void sun() //맑은날 효과
{
  static int i=0;
  fadeToBlackBy( leds, NUM_LEDS, 20);
  int color=64;
  if(i==0)
  {
  leds[10]=CHSV( color, 200, 255);
  leds[11]=CHSV( color, 200, 255);
  leds[12]=CHSV( color, 200, 255);
  leds[13]=CHSV( color, 200, 255);
  leds[17]=CHSV( color, 200, 255);
  leds[18]=CHSV( color, 200, 255);
  leds[19]=CHSV( color, 200, 255);
  leds[20]=CHSV( color, 200, 255);
  leds[21]=CHSV( color, 200, 255);
  leds[22]=CHSV( color, 200, 255);
  leds[25]=CHSV( color, 200, 255);
  leds[26]=CHSV( color, 200, 255);
  leds[29]=CHSV( color, 200, 255);
  leds[30]=CHSV( color, 200, 255);
  leds[33]=CHSV( color, 200, 255);
  leds[34]=CHSV( color, 200, 255);
  leds[37]=CHSV( color, 200, 255);
  leds[38]=CHSV( color, 200, 255);
  leds[41]=CHSV( color, 200, 255);
  leds[42]=CHSV( color, 200, 255);
  leds[43]=CHSV( color, 200, 255);
  leds[44]=CHSV( color, 200, 255);
  leds[45]=CHSV( color, 200, 255);
  leds[46]=CHSV( color, 200, 255);
  leds[50]=CHSV( color, 200, 255);
  leds[51]=CHSV( color, 200, 255);
  leds[52]=CHSV( color, 200, 255);
  leds[53]=CHSV( color, 200, 255);
  }
  i++;
  if(i==70) i=0;
  delay(10);
}


void thunder() //천둥번개 효과
{
  static int i=0;
  int color=50;
  fadeToBlackBy( leds, NUM_LEDS, 30);
  if(i==140) //thunder 1 center
  {
    leds[4]=CHSV( color, 200, 255);
    leds[11]=CHSV( color, 200, 255);
    leds[12]=CHSV( color, 200, 255);
    leds[18]=CHSV( color, 200, 255);
    leds[19]=CHSV( color, 200, 255);
    leds[20]=CHSV( color, 200, 255);
    leds[25]=CHSV( color, 200, 255);
    leds[26]=CHSV( color, 200, 255);
    leds[27]=CHSV( color, 200, 255);
    leds[28]=CHSV( color, 200, 255);
    leds[35]=CHSV( color, 200, 255);
    leds[36]=CHSV( color, 200, 255);
    leds[37]=CHSV( color, 200, 255);
    leds[38]=CHSV( color, 200, 255);
    leds[43]=CHSV( color, 200, 255);
    leds[44]=CHSV( color, 200, 255);
    leds[45]=CHSV( color, 200, 255);
    leds[51]=CHSV( color, 200, 255);
    leds[52]=CHSV( color, 200, 255);
    leds[59]=CHSV( color, 200, 255);
  }

  if(i==0) //thunder 2
  {
    leds[2]=CHSV( color, 200, 255);
    leds[9]=CHSV( color, 200, 255);
    leds[10]=CHSV( color, 200, 255);
    leds[16]=CHSV( color, 200, 255);
    leds[17]=CHSV( color, 200, 255);
    leds[18]=CHSV( color, 200, 255);
    leds[26]=CHSV( color, 200, 255);
    leds[27]=CHSV( color, 200, 255);
    leds[28]=CHSV( color, 200, 255);
    leds[34]=CHSV( color, 200, 255);
    leds[35]=CHSV( color, 200, 255);
    leds[42]=CHSV( color, 200, 255);
  }

  if(i==70) //thunder 3
  {
    leds[29]=CHSV( color, 200, 255);
    leds[36]=CHSV( color, 200, 255);
    leds[37]=CHSV( color, 200, 255);
    leds[43]=CHSV( color, 200, 255);
    leds[44]=CHSV( color, 200, 255);
    leds[45]=CHSV( color, 200, 255);
    leds[46]=CHSV( color, 200, 255);
    leds[47]=CHSV( color, 200, 255);
    leds[53]=CHSV( color, 200, 255);
    leds[54]=CHSV( color, 200, 255);
    leds[61]=CHSV( color, 200, 255);
  }
  i++;
  if(i==210) i=0;
  delay(6);
}

void cloud() //구름 효과
{
  static int i=0;
  int color=150;
  fadeToBlackBy( leds, NUM_LEDS, 10);
  for(int j=18;j<22;j++) leds[j]=CHSV( color, random(200) , 155+random(100));
  for(int j=25;j<31;j++) leds[j]=CHSV( color, random(200) , 155+random(100));
  for(int j=32;j<48;j++) leds[j]=CHSV( color, random(200) , 155+random(100));
  for(int j=49;j<55;j++) leds[j]=CHSV( color, random(200) , 155+random(100));
  delay(50);
}

//1159068000 디폴트
//4377025300 충북 음성군 금왕읍
//4717065000 안동시 옥동
//4215061500 강릉시
//4111369000 수원시
//4831034000 거제시
//4729053000 경산시
//4681025000 강진군
//4579031000 고창군
//5013025300 서귀포
//4425051000 계룡시
