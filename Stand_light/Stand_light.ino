#include <Adafruit_NeoPixel.h>
#define input A0; //입력저항 포트

#define Pin 5; //네오픽셀 출력 핀번호
#define NUM_LEDS 6; //led 개수
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pinMode(input,INPUT);
  strip.begin();
  strip.start();
}

void loop() {
  int state = analogRead(input);
  state = map(state,0,1023,0,255);
  for(uint16_t i=0;i<NUM_LEDS;i++){
    strip.setPixelColor(i,strip.Color(127, 127, 127));
    strip.show();
  }
}
