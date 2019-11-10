#include "FastLED.h"

FASTLED_USING_NAMESPACE

// FastLED "100-lines-of-code" demo reel, showing just a few 
// of the kinds of animation patterns you can quickly and easily 
// compose using FastLED.  
//
// This example also shows one easy way to define multiple 
// animations patterns and have them automatically rotate.
//
// -Mark Kriegsman, December 2014

#if FASTLED_VERSION < 3001000
#error "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define DATA_PIN    6
//#define CLK_PIN   4
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS    64
CRGB leds[NUM_LEDS];

#define BRIGHTNESS         30
#define FRAMES_PER_SECOND  120

void setup() {
  delay(3000); // 3 second delay for recovery

  Serial.begin(9600);
  
  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  //FastLED.addLeds<LED_TYPE,DATA_PIN,CLK_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
}


// List of patterns to cycle through.  Each is defined as a separate function below.
typedef void (*SimplePatternList[])();
SimplePatternList gPatterns = { rainbow, rainbowWithGlitter, confetti, sinelon, juggle, bpm };

uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint8_t gHue = 0; // rotating "base color" used by many of the patterns
  
void loop()
{
  // Call the current pattern function once, updating the 'leds' array
  //gPatterns[gCurrentPatternNumber]();
  //sinelon();
  //rainbowWithGlitter();
  //confetti();
  //bpm();
  //juggle();
  rain();
  //sun();

  // send the 'leds' array out to the actual LED strip
  FastLED.show();  
  // insert a delay to keep the framerate modest
  FastLED.delay(1000/FRAMES_PER_SECOND); 

  // do some periodic updates
  EVERY_N_MILLISECONDS( 20 ) { gHue++; } // slowly cycle the "base color" through the rainbow
  EVERY_N_SECONDS( 10 ) { nextPattern(); } // change patterns periodically
}

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

void rain()
{
  static int i=-1;
  static int r1=0;
  static int r2=1;
  static int r3=2;
  static int r4=3;
  static int r5=4;
  static int r6=5;
  static int r7=6;
  static int r8=7;
  
  fadeToBlackBy( leds, NUM_LEDS, 100);

   if(i>0&&i<9)
   {
    leds[r2]=CHSV( 150, 200, 255); 
    r2+=8;
   }
   if(i>3&&i<12)
   {
    leds[r5]=CHSV( 150, 200, 255); 
    r5+=8;
   }
   if(i>6&&i<15)
   {
    leds[r1]=CHSV( 150, 200, 255); 
    r1+=8;
   }
   if(i>9&&i<18)
   {
    leds[r6]=CHSV( 150, 200, 255); 
    r6+=8;
   }
   if(i>12&&i<21)
   {
    leds[r8]=CHSV( 150, 200, 255); 
    r8+=8;
   }
   if(i>15&&i<24)
   {
    leds[r3]=CHSV( 150, 200, 255); 
    r3+=8;
   }
   if(i>18&&i<27)
   {
    leds[r7]=CHSV( 150, 200, 255); 
    r7+=8;
   }
   if(i>21&&i<30)
   {
    leds[r4]=CHSV( 150, 200, 255); 
    r4+=8;
   }
   
   i++;

   if(r1>64) r1=0;
   if(r2>64) r2=1;  
   if(r3>64) r3=2;  
   if(r4>64) r4=3;  
   if(r5>64) r5=4;  
   if(r6>64) r6=5;  
   if(r7>64) r7=6;  
   if(r8>64) r8=7;     
   if(i>31) i=-1;
  
  delay(80);
}

void sun()
{
  static int i=0,color=25; 
  fadeToBlackBy( leds, NUM_LEDS, 10);
  leds[19]=CHSV( color, 200, 255);
  leds[20]=CHSV( color, 200, 255);
  for(int j=26;j<30;j++) leds[j]=CHSV( color, 200, 255);
  for(int j=34;j<38;j++) leds[j]=CHSV( color, 200, 255);
  leds[43]=CHSV( color, 200, 255);
  leds[44]=CHSV( color, 200, 255);
  //19,20,26,27,28,29,34,35,36,37,43,44

  if(i%80==0)
  {
    for(int j=0;j<64;j++)
    {
      if(j!=0&&j!=1&&j!=2&&j!=5&&j!=6&&j!=7&&j!=8&&j!=15&&j!=16&&j!=23&&j!=40&&j!=47&&j!=48&&j!=55&&j!=56&&j!=57&&j!=58&&j!=61&&j!=62&&j!=63)
        leds[j]=CHSV( color, 200, 255);
    }
  }
  i++;
  delay(10);
}

void thunder()
{
  static int i=0;
  fadeToBlackBy( leds, NUM_LEDS, 10);
  if(i%80==0) //thunder 1
  {
    leds[4]=CHSV( color, 200, 255);
    leds[11]=CHSV( color, 200, 255);
    leds[12]=CHSV( color, 200, 255);
    leds[18]=CHSV( color, 200, 255);
    leds[19]=CHSV( color, 200, 255);
    leds[20]=CHSV( color, 200, 255);
    leds[25]=CHSV( color, 200, 255);
    leds[26]=CHSV( color, 200, 255);
    leds[27]=CHSV( color, 200, 255);
    leds[28]=CHSV( color, 200, 255);
    leds[35]=CHSV( color, 200, 255);
    leds[36]=CHSV( color, 200, 255);
    leds[37]=CHSV( color, 200, 255);
    leds[38]=CHSV( color, 200, 255);
    leds[43]=CHSV( color, 200, 255);
    leds[44]=CHSV( color, 200, 255);
    leds[45]=CHSV( color, 200, 255);
    leds[51]=CHSV( color, 200, 255);
    leds[52]=CHSV( color, 200, 255);
    leds[59]=CHSV( color, 200, 255);
  }

  if(i%100==0) //thunder 2
  {
    leds[2]=CHSV( color, 200, 255);
    leds[9]=CHSV( color, 200, 255);
    leds[10]=CHSV( color, 200, 255);
    leds[16]=CHSV( color, 200, 255);
    leds[17]=CHSV( color, 200, 255);
    leds[18]=CHSV( color, 200, 255);
    leds[26]=CHSV( color, 200, 255);
    leds[27]=CHSV( color, 200, 255);
    leds[28]=CHSV( color, 200, 255);
    leds[34]=CHSV( color, 200, 255);
    leds[35]=CHSV( color, 200, 255);
    leds[42]=CHSV( color, 200, 255);
  }

  if(i%200==0)
  {
    
  }
  i++;
  delay(10);
}

void nextPattern()
{
  // add one to the current pattern number, and wrap around at the end
  gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE( gPatterns);
}

void rainbow() 
{
  // FastLED's built-in rainbow generator
  fill_rainbow( leds, NUM_LEDS, gHue, 7);
}

void rainbowWithGlitter() 
{
  // built-in FastLED rainbow, plus some random sparkly glitter
  rainbow();
  addGlitter(80);
}

void addGlitter( fract8 chanceOfGlitter) 
{
  if( random8() < chanceOfGlitter) {
    leds[ random16(NUM_LEDS) ] += CRGB::White;
  }
}

void confetti() 
{
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( leds, NUM_LEDS, 10);
  int pos = random16(NUM_LEDS);
  leds[pos] += CHSV( gHue + random8(64), 200, 255);
}

int poses1[8]={0};
int poses=0;
//int i=0;

/*
void line1(int n)
{
  fadeToBlackBy( leds, NUM_LEDS, 50);
  static int a=0;
  if(i>63) a=0;
  leds[a]=CHSV( 150, 200, 255);
  a+=8;
}
*/

void sinelon()
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds, NUM_LEDS, 20);
  int pos = beatsin16(13,0,NUM_LEDS);
  leds[pos] +=  CHSV( 100, 255, 190);
}

void bpm()
{
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  uint8_t BeatsPerMinute = 62;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
  for( int i = 0; i < NUM_LEDS; i++) { //9948
    leds[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
  }
}

void juggle() {
  // eight colored dots, weaving in and out of sync with each other
  fadeToBlackBy( leds, NUM_LEDS, 200);
  byte dothue = 0;
  for( int i = 0; i < 8; i++) {
    leds[beatsin16(i+7,0,NUM_LEDS)] |= CHSV(dothue, 200, 255);
    dothue += 32;
  }
}
