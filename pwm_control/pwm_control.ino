const int CDS=A0;
const int FAN=6;
//For PNP transistor, output signal is reversed.

void setup() {
  
  Serial.begin(9600);
  
  pinMode(CDS,INPUT);
  pinMode(FAN,OUTPUT);
}

void loop() {
  int CDS=analogRead(CDS);
  analogWrite(FAN,0);
  
  if(CDS>=300)
  {
    analogWrite(FAN,0);
  }
  else
  {
    analogWrite(FAN,255);  
  }
  Serial.println(CDS);
}
