#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h>
#endif

#define LED_PIN    6
#define Handle     A0
#define Switch     10
#define LED_COUNT  30

bool BeforeState = 0;
bool NowState = 0;

int State;
int Mode = 0;
int Green=0,Red=0,Blue=0;

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();           
  strip.show();  
  strip.setBrightness(50);          

  pinMode(Handle,INPUT);
  pinMode(Switch,INPUT_PULLUP);

  Serial.begin(9600);
}

void loop() {
  strip.begin();
  State = analogRead(Handle);
  State = map(State,0,1023,0,255);
  NowState = digitalRead(Switch);
  
  if(BeforeState==0&&NowState==1){
    Mode++;
    Mode%=4;
    delay(20);
  }

  Serial.print(BeforeState);
  Serial.print(" ");
  Serial.print(NowState);
  Serial.print(" ");
  Serial.println(Mode);

  switch(Mode){
    case 0:
      colorWipe(strip.Color(State,Red,Blue),1);
      break;
    case 1:
      colorWipe(strip.Color(Green,State,Blue),1);
      break;
    case 2:
      colorWipe(strip.Color(Green,Red,State),1);
      break;
    case 3:
      colorWipe(strip.Color(255,255,255),1);
      break;
  }
  
  BeforeState = NowState;
}

void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    strip.setBrightness(State);
  }
}
