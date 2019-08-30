#include <PWM.h>
#include <LiquidCrystal.h>
#include "U8glib.h"

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE); //SDA : A4 , SCL : A5

const int roll=A1; //가변저항 변수 
const int pulse=3;

int lcd_key     = 0; //버튼을 읽어온 값 변환 후 저장하는 변수
int adc_key_in  = 0; //버튼을 읽어온 값 저장하는 변수
int nowselect=1; //1 펄스 2 사인 3 트라이앵글
int freq=1; //1 Hz  2 KHz

int32_t frequency; //frequency (in Hz)
 
#define btnRIGHT  1
#define btnUP     2
#define btnDOWN   3
#define btnLEFT   4
#define btnSELECT 5
#define btnNONE   6
 
int read_LCD_buttons()  //버튼 입력받는 함수 
{               
    adc_key_in = analogRead(0);
    //Serial.print(freq);
    //Serial.print("\n");
    if(adc_key_in<1000)
    {
      if (adc_key_in < 50)   return btnRIGHT;  
      else if (adc_key_in < 195)  return btnUP; 
      else if (adc_key_in < 380)  return btnDOWN; 
      else if (adc_key_in < 555)  return btnLEFT; 
      else if (adc_key_in < 790)  return btnSELECT;   
    }
    else
    {
      //Serial.print("not input");
      //Serial.print(adc_key_in);
      //Serial.print("\n");
      return 8;  //값이 입력되지 않았을 경우 상관없는 값 반환
    }
}

int PULSE()  //펄스파 
{
  while(1)
  {
   lcd.setCursor(0,0); 
   lcd.print("Mode is PULSE   ");
   
   roll_(nowselect); 
   lcd_key = read_LCD_buttons();
    
   if(lcd_key==btnUP) freq=2;
   if(lcd_key==btnDOWN) freq=1;
   if(lcd_key==btnLEFT) break;

   lcd.setCursor(0,1);
   if(freq==1) lcd.print("Output Hz: "); 
   if(freq==2) lcd.print("Output KHz:");
  }
}

int SINE()  //사인파 
{
  while(1)
  {
   lcd.setCursor(0,0); 
   lcd.print("Mode is SINE    ");
   
   roll_(nowselect); 
   lcd_key = read_LCD_buttons();
    
   if(lcd_key==btnUP) freq=2;
   if(lcd_key==btnDOWN) freq=1;
   if(lcd_key==btnLEFT) break;

   lcd.setCursor(0,1);
   if(freq==1) lcd.print("Output Hz: "); 
   if(freq==2) lcd.print("Output KHz:");
  }
}

int TRI()  //삼각파 
{
 while(1)
  {
   lcd.setCursor(0,0); 
   lcd.print("Mode is TRIANGLE");
   
   roll_(nowselect); 
   lcd_key = read_LCD_buttons();
    
   if(lcd_key==btnUP) freq=2;
   if(lcd_key==btnDOWN) freq=1;
   if(lcd_key==btnLEFT) break;

   lcd.setCursor(0,1);
   if(freq==1) lcd.print("Output Hz: "); 
   if(freq==2) lcd.print("Output KHz:");
  }
} 

float roll_(int mode) //가변 저항의 저항값 읽어온 후 파형 출력하는 함수
{
   float button=analogRead(roll); 
   int temp,output;
   
   if(button<100)
   {
    temp=button;
    output=temp/10+1;
   }
   else
   {
    button=((button-100)/923)*990+10;
    temp=button;
    output=temp/10*10;
   }
   
   lcd.setCursor(11,1);
   lcd.print(output);
   lcd.print("  "); 

   /*
   if(freq=1)  //Hz
   {
    if(mode==1) //펄스파 출력 
    {
     digitalWrite(pulse,HIGH);
     pwmWrite(pulse,output);
     break;
    }
    if(mode==2)
    {
     break;
    }
   if(mode==3)
    {
     break;
    }
   }
   
   if(freq=2) //KHz
   {
    if(mode==1) //펄스파 출력 
    {
     digitalWrite(pulse,HIGH);
     pwmWrite(pulse,output);
     break;
    }
    if(mode==2)
    {
     
    }
   if(mode==3)
    {
     
    }
   }
   */
}


int mainmenu() //메인 메뉴 함수 
{
   lcd.setCursor(0,0);            
   lcd.print("select-> ");  //메인 메뉴 화면 구성하기 
   lcd.setCursor(0,1);
   lcd.print("                ");

   lcd_key = read_LCD_buttons();   // read the buttons
   if(lcd_key==btnUP&&nowselect!=3) nowselect++;
   if(lcd_key==btnDOWN&&nowselect!=1) nowselect--;
   if(lcd_key==btnRIGHT)
   {
    if(nowselect==1) PULSE();
    if(nowselect==2) SINE();
    if(nowselect==3) TRI();
   }
  
  lcd.setCursor(9,0);
  if(nowselect==1)lcd.print("1.PULSE"); 
  if(nowselect==2)lcd.print("2.SINE ");
  if(nowselect==3)lcd.print("3.TRI  ");

  delay(150);
}

 
void setup()
{
   lcd.begin(16, 2);               // lcd 라이브러리 시작 
   lcd.setCursor(0,0);             // 초기화면 세팅 
   lcd.print("select-> 1.PULSE");  
   
   //Serial.begin(9600);
   pinMode(roll,INPUT);  //가변저항 값 입력받기 위한 세팅 

   bool success = SetPinFrequencySafe(pulse, frequency);
   if(success) 
   {
    pinMode(pulse, OUTPUT);
    digitalWrite(pulse, HIGH);    
   }

}
 
void loop()
{
   //Serial.print("new loop\n");   
   mainmenu();
}
