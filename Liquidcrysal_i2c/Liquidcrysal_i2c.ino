#include <LiquidCrystal_I2C.h>

#include <Wire.h>

int i = 0;

LiquidCrystal_I2C lcd1(0x27, 16, 2);
LiquidCrystal_I2C lcd2(0x26, 16, 2);

void setup() {
  Serial.begin(115200);
  Wire.begin(D2, D1);
  lcd1.begin();
  lcd2.begin();
}

void loop() { // do nothing here 
  
  lcd1.begin();
  lcd1.home();
  lcd1.print("Namwoo Kim");
  lcd1.setCursor(0,1);
  lcd1.print("Heejin Kim");

  lcd2.begin();
  lcd2.home();
  lcd2.print("Dongseob Shin");
  lcd2.setCursor(0,1);
  lcd2.print("Hyonsik Kim");
}
