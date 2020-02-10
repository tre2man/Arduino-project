#include <Servo.h>

//바닥, 팔꿈치, 손목 , 손 4개의 저항 및 모터

const int floor_in=A0; //입력 부분 순서대로 a0 a1 a2 a3 연결
const int elbow_in=A1;
const int wrist_in=A2;
const int hand_in=A3;

const int floor_moter=4; //입력받은 값 모터로 전달 변수 4 5 6 7
const int elbow_moter=5;
const int wrist_moter=6;
const int hand_moter=7;

Servo servo_floor; //서보모터를 작동시키는 함수 선언
Servo servo_elbow;
Servo servo_wrist;
Servo servo_hand;

void setup() {
  pinMode(floor_in,INPUT);
  pinMode(elbow_in,INPUT);
  pinMode(wrist_in,INPUT);
  pinMode(hand_in,INPUT);
  
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
   
  servo_floor.write(f); //입력받은 값을 서보모터로 출력
  servo_elbow.write(e); 
  servo_wrist.write(w);
  servo_hand.write(h);

  Serial.print(f);
  Serial.print(" ");
  Serial.print(e);
  Serial.print(" ");
  Serial.print(w); 
  Serial.print(" ");
  Serial.println(h);

  //delay(10); //시간 조절
  
  
  
}
