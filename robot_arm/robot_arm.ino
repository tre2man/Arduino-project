#include <Servo.h>

//바닥, 팔꿈치, 손목 , 손 4개의 저항 및 모터

const int floor_in=A0;
const int elbow_in=A1;
const int wrist_in=A2;
const int hand_in=A3;

const int floor_moter=4;
const int elbow_moter=5;
const int wrist_moter=6;
const int hand_moter=7;

Servo servo_floor;
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
  int f=map(analogRead(floor_in),0,1023,0,359); //맵핑을 통해 서보모터의 떨림을 방지한다.
  int e=map(analogRead(elbow_in),0,1023,0,359);
  int w=map(analogRead(wrist_in),0,1023,0,359);
  int h=map(analogRead(hand_in),0,1023,0,359);
  
  servo_floor.write(f);
  servo_elbow.write(e);
  servo_wrist.write(w);
  servo_hand.write(h);

  Serial.print(f);
  Serial.print("\n");
}
