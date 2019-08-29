// Generátor funkcí AD9833

// připojení potřebné knihovny
#include <AD9833.h>
// definice propojovacího pinu FSYNC
#define pinFsync 10 //10번핀이 싱크 
// inicializace modulu z knihovny s nastavením pinu FSYNC
AD9833 gen(pinFsync);  //함수 정의 

void setup() {
  // zahájení komunikace po sériové lince
  // rychlostí 9600 baud
  Serial.begin(9600);
  // zahájení komunikace s modulem AD9833
  gen.Begin();
  // zapnutí výstupu s výchozím signálem
  // typu SINUS s frekvencí 1 kHz
  Serial.println("Start programu, sinus 1000 Hz");
  gen.EnableOutput(true);
  delay(4000);
}

void loop() {
  // nastavení trojúhelníkového signálu
  // o frekvenci 2000 Hz do REG1
  // a jeho zapnutí na výstup
  Serial.println("Trojuhelnik 2000 Hz");
  gen.ApplySignal(SINE_WAVE, REG1, 2000);
  delay(4000);
  /*
  // změna frekvence v REG1 na 1000 Hz
  Serial.println("Zmena trojuhelniku na 1000 Hz");
  gen.SetFrequency(REG1, 1000);
  delay(4000);
  // přepnutí zpět na REG0
  Serial.println("Prepnuti zpet na 1000 Hz sinus");
  gen.SetOutputSource(REG0);
  delay(4000);
  // nastavení REG0 na obdélníkový signál
  // o frekvenci 1500 Hz
  Serial.println("Zmena na obdelnik 1500 Hz");
  gen.SetWaveform(REG0, SQUARE_WAVE);
  gen.SetFrequency(REG0, 1500);
  delay(4000);
  // nastavení REG0 na půlobdélníkový signál
  // o frekvenci 1000 Hz
  Serial.println("Zmena na pul-obdelnik 1000 Hz");
  gen.SetWaveform(REG0, HALF_SQUARE_WAVE);
  gen.SetFrequency(REG0, 1000);
  delay(4000);
  // nastavení REG0 na sinusový signál
  // o frekvenci 1000 Hz
  Serial.println("Zmena na sinus 1000 Hz");
  gen.SetWaveform(REG0, SINE_WAVE);
  delay(4000);
  // postupné zvyšování fázového posuvu od 0 do 180 stupňů
  Serial.println("Zvysovani frekvence z 1000 na 4000 Hz");
  for (int i = 0; i < 30; i++) {
    gen.IncrementFrequency(REG0, 100);
    delay(100);
  }
  delay(1000);
  // nastavení fázového posuvu na 180 stupňů
  Serial.println("Nastaveni fazoveho posuvu na 180 stupnu");
  gen.SetPhase(REG1, 180);
  delay(4000);
  // reset modulu pro získání výchozího stavu
  Serial.println("Reset modulu");
  gen.Reset();
  delay(4000);
  */
}
