#include <LiquidCrystal.h>
 
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);           // select the pins used on the LCD panel
 
// define some values used by the panel and buttons
const int roll=A1; //가변저항 변수 

int lcd_key     = 0; //버튼을 읽어온 값 변환 후 저장하는 변수
int adc_key_in  = 0; //버튼을 읽어온 값 저장하는 변수
int now=1; //1 펄스 2 사인 3 트라이앵글
int mode=0;
int read_lcd=0;
 
#define btnRIGHT  1
#define btnUP     2
#define btnDOWN   3
#define btnLEFT   4
#define btnSELECT 5
#define btnNONE   6
 
int read_LCD_buttons()
{               
  //while(read_lcd==0)
  //{
    adc_key_in = analogRead(0);
    if(adc_key_in<1000)
    {
      read_lcd=1;
      if (adc_key_in < 50)   return btnRIGHT;  
      else if (adc_key_in < 195)  return btnUP; 
      else if (adc_key_in < 380)  return btnDOWN; 
      else if (adc_key_in < 555)  return btnLEFT; 
      else if (adc_key_in < 790)  return btnSELECT;   
    }
    else
    {
      Serial.print("not input");
      Serial.print(now);
      Serial.print("\n");
      return 7;
    }
  //}
  //read_lcd=0;
  delay(300);
    // my buttons when read are centered at these valies: 0, 144, 329, 504, 741
    // we add approx 50 to those values and check to see if we are close  
}

float mainmenu()
{
   lcd.setCursor(0,0);             // set the LCD cursor   position 
   lcd.print("select-> ");  // print a simple message on the LCD
   lcd.setCursor(0,1);
   lcd.print("                ");
   lcd.setCursor(9,0);

   lcd_key = read_LCD_buttons();   // read the buttons
   if(lcd_key==btnUP&&now!=3) now++;
   if(lcd_key==btnDOWN&&now!=1) now--;
   if(lcd_key==btnRIGHT)
   {
    if(now==1) PULSE();
    if(now==2) SINE();
    if(now==3) TRI();
   }
  
  lcd.setCursor(9,0);
  if(now==1)lcd.print("1.PULSE"); 
  if(now==2)lcd.print("2.SINE ");
  if(now==3)lcd.print("3.TRI  ");

  delay(200);
}


float PULSE()
{
  while(1)
  {
   lcd.setCursor(0,0); 
   lcd.print("Mode is PULSE   ");
   lcd.setCursor(0,1);
   lcd.print("Input Hz"); 

   roll_();
    
   lcd_key = read_LCD_buttons(); 
   if(lcd_key==btnLEFT) break;
  }
}

float SINE()
{
  while(1)
  {
   lcd.setCursor(0,0); 
   lcd.print("Mode is SINE   ");
   lcd.setCursor(0,1);
   lcd.print("Input Hz"); 

   roll_();
    
   lcd_key = read_LCD_buttons(); 
   if(lcd_key==btnLEFT) break;
  }
}

float TRI()
{
 while(1)
 {
   lcd.setCursor(0,0); 
   lcd.print("Mode is TRI   ");
   lcd.setCursor(0,1);
   lcd.print("Input Hz"); 

   roll_();
    
   lcd_key = read_LCD_buttons(); 
   if(lcd_key==btnLEFT) break;
 }
}

float roll_()
{
   float button=analogRead(roll);
   lcd.setCursor(10,1);
   lcd.print(button/1023*100,0);
   lcd.print("  "); 
}

 
void setup()
{
   lcd.begin(16, 2);               // start the library
   lcd.setCursor(0,0);             // set the LCD cursor   position 
   lcd.print("select-> 1.PULSE");  // print a simple message on the LCD
   
   Serial.begin(9600);
   pinMode(A1,INPUT);
}
 
void loop()
{ 
   //lcd.setCursor(9,0);             // move to the begining of the second line
   Serial.print("new loop\n");   
   mainmenu();
}
