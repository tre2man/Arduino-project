#include <LiquidCrystal.h>
 
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);           // select the pins used on the LCD panel

int roll=A1;

float roll_()
{
  float button=analogRead(roll);
  lcd.setCursor(0,0);
  lcd.print(button/1023*100,0);
  lcd.print("  ");
}

void setup() {
  pinMode(A1,INPUT);
  lcd.begin(16, 2);               // start the library
  Serial.begin(9600);
}

void loop() {
  while(1)
  {
     roll_();
  }
}
