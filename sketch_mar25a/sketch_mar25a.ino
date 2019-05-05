const int relay=3;
const int LIGHT=A0;

void setup(){
  Serial.begin(9600);
  pinMode(relay,OUTPUT);  //relay output
  pinMode(LIGHT,INPUT); //ldr input
}

void loop(){
  int LIGHT=analogRead(LIGHT);

  if(LIGHT<=300)
  {
    digitalWrite(relay,HIGH);
    Serial.println("점등");
  }
  else
  {
    digitalWrite(relay,LOW);
    Serial.println("소등");
  } 
  Serial.println(LIGHT);
  delay(50);
}
