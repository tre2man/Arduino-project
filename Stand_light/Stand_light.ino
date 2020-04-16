#include <Adafruit_NeoPixel.h>

#define input A0 //입력저항 포트
#define PIN 9 //네오픽셀 출력 핀번호
#define NUM_LEDS 21 //led 개수

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pinMode(input,INPUT);
  strip.begin();
  strip.show();
}

void loop() {
  int state = analogRead(input);
  for(uint16_t i=0;i<NUM_LEDS;i++){
    strip.setPixelColor(i,255,255,255);
    strip.setBrightness(state);
    strip.show();
  }
}
