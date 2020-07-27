#include <LiquidCrystal_I2C.h>
#include <Wire.h>


LiquidCrystal_I2C lcd(0x3F, 16, 2);

//i2c주소는 직접 찾아야함 2개니까 다른 주소를 가지고 있는 2개 쓰면 될듯
//https://kocoafab.cc/tutorial/view/727

void setup() {
  lcd.init();
  lcd.backlight();
}


void loop() { 
  lcd.setCursor(0,0);
  lcd.print("Namwoo Hyeonsik");
  delay(1000);
  lcd.clear();
}
