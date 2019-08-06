#include <LiquidCrystal.h>
 
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);           // select the pins used on the LCD panel

int roll=A1;

float roll_()
{
  float button=analogRead(roll);  시리얼통신 시작 
  lcd.setCursor(0,0);
  lcd.print(button/1023*100,0);  //0부터 1023까지의 수를 0부터 100까지의 수로 변환
  lcd.print("  ");
}

void setup() {
  pinMode(A1,INPUT);
  lcd.begin(16, 2);               // start the library
  Serial.begin(9600);
}

void loop() {
  roll_();
}
