#include <Servo.h>

//바닥, 팔꿈치, 손목 , 손 4개의 저항 및 모터

#define floor_in A0 //입력 부분 순서대로 a0 a1 a2 a3 연결
#define elbow_in A1
#define wrist_in A2
#define hand_in A3

#define floor_moter 4 //입력받은 값 모터로 전달 변수 4 5 6 7
#define elbow_moter 5
#define wrist_moter 6
#define hand_moter 7

#define green 12
#define yellow 11
#define red 10

#define record 2
#define play 3

int rfloor[20000]={0};
int relbow[20000]={0};
int rwrist[20000]={0};
int rhand[20000]={0};


Servo servo_floor; //서보모터를 작동시키는 함수 선언
Servo servo_elbow;
Servo servo_wrist;
Servo servo_hand;

int state=-1; //-1이면 평상시 1이면 녹화중 0은 재생

void record(int f,int e,int w,int h)
{
  static int i=0;
  
  rfloor[i]=f;
  relbow[i]=e;
  rwrist[i]=w;
  rhand[i]=h;

  i++;
  if(i>=19999) state=0;
}

void play()
{
  static int i=0;

  servo_floor.write(rfloor[i]); 
  servo_elbow.write(relbow[i]); 
  servo_wrist.write(rwrist[i]);
  servo_hand.write(rhand[i]);

  i++;
  i%=20000;
}

void resetrecord()
{
  for(int i=0;i<20000;i++)
  {
    rfloor[i]=0;
    relbow[i]=0;
    rwrist[i]=0;
    rhand[i]=0;
  }
}

void setup() {
  pinMode(floor_in,INPUT);
  pinMode(elbow_in,INPUT);
  pinMode(wrist_in,INPUT);
  pinMode(hand_in,INPUT);

  pinMode(record,INPUT);  //풀업 저항으로 변경
  pinMode(play,INPUT);  //풀업 저항으로 변경 

  pinMode(red,OUTPUT);
  pinMode(green,OUTPUT);
  pinMode(yellow,OUTPUT);
  
  servo_floor.attach(floor_moter);
  servo_elbow.attach(elbow_moter);
  servo_wrist.attach(wrist_moter);
  servo_hand.attach(hand_moter);
  
  Serial.begin(9600);
}

void loop() {
    
  int f=map(analogRead(floor_in),0,1023,0,160); //맵핑을 통해 0~1023까지의 값을 0~359로 조정
  int e=map(analogRead(elbow_in),0,1023,0,160);
  int w=map(analogRead(wrist_in),0,1023,0,160);
  int h=map(analogRead(hand_in),0,1023,53,111);

  int state1=digitalRead(record); //원하는것 : 액티브 하이 스위치
  int state2=digitalRead(play);

  if(state2==1&&state==-1) state=0;
  else if(state2==1&&state==0) state=-1;
  else if(state1==1) state*=-1; //녹화와 평상시를 왔다갔다
  

  if(state==0)
  {
    play();
  }
  else if(state==1)
  {
    resetrecord();
    record(f,e,w,h);
  }
  else if(state==-1)
  {
     servo_floor.write(f); //입력받은 값을 서보모터로 출력
     servo_elbow.write(e); 
     servo_wrist.write(w);
     servo_hand.write(h);
  }

  Serial.print(f);
  Serial.print(" ");
  Serial.print(e);
  Serial.print(" ");
  Serial.print(w); 
  Serial.print(" ");
  Serial.println(h);

  delay(10); //시간 조절
}
