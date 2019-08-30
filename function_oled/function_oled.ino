#include "U8glib.h"
#include <PWM.h>
#include <AD9833.h>

#define pinFsync 10 //10번핀이 싱크

AD9833 gen(pinFsync);  //함수 정의 

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE); //SDA : A4 , SCL : A5

const int roll=A0;

void setup()
{
  Serial.begin(9600);
  gen.Begin();
  gen.EnableOutput(true);

  pinMode(roll,INPUT);
}

void loop()
{
  u8g.firstPage();
  
  do
  {
    int freq=analogRead(roll);
    Serial.print(freq);
    Serial.print("\n");

    u8g.setFont(u8g_font_unifont);
    u8g.setPrintPos(0,30);
    u8g.print(freq);

    gen.ApplySignal(SINE_WAVE,REG1,freq);
  }while( u8g.nextPage() );
  
  delay(500);
}
