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
    if(freq<10) freq=10;
    Serial.print(freq);
    Serial.print("\n");

    u8g.drawFrame(1,1,126,62);
    u8g.drawStr(25,15,"SINE WAVE");

    u8g.setFont(u8g_font_unifont);
    u8g.setPrintPos(40,40);
    u8g.print(freq);
    u8g.drawStr(75,40,"Hz");

    gen.ApplySignal(TRIANGLE_WAVE,REG1,freq);
  }while( u8g.nextPage() );
  
  delay(1500);
  //SINE_WAVE, TRIANGLE_WAVE, SQUARE_WAVE, and HALF_SQUARE_WAVE
}
