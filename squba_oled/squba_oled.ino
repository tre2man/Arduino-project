#include "U8glib.h"

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);

#define CDS A0
   
void setup() 
{
  pinMode(CDS,INPUT);
}  

void loop() 
{
  float cds=analogRead(CDS);
  if(cds>100) cds=100;
  u8g.firstPage();
  do{
      u8g.drawBox(1,1,cds/100*126,10);
      u8g.setFont(u8g_font_unifont);
      u8g.setPrintPos(0,30);
      u8g.print(cds);
  }while(u8g.nextPage());
}
