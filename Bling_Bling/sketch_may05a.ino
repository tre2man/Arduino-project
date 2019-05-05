//bling bling 
const int led1=6;
const int led2=9;
const int led3=10;
const int led4=11;

int a=0,b=0,c=0,d=0;
int a1=0,b1=0,c1=0,d1=0;

void setup() {
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  pinMode(led4,OUTPUT);

  analogWrite(led1,0);
  analogWrite(led2,0);
  analogWrite(led3,0);
  analogWrite(led4,0);
}

void loop() {
  analogWrite(led1,a);
  analogWrite(led2,b);
  analogWrite(led3,c);
  analogWrite(led4,d);
  
  if(a1==0)
    {
        if(a>250)
          a1=1;
        else
          a+=3;
      }
      else
    {
        if(a<4)
          a1=0;
        else
          a-=3;
      }

  if(b1==0)
    {
        if(b>240)
          b1=1;
        else
          b+=7;
      }
      else
    {
        if(b<10)
          b1=0;
        else
          b-=7;
      }

   if(c1==0)
    {
        if(c>240)
          c1=1;
        else
          c+=9;
      }
      else
    {
        if(c<12)
          c1=0;
        else
          c-=9;
      }

   if(d1==0)
    {
        if(d>230)
          d1=1;
        else
          d+=13;
      }
      else
    {
        if(d<30)
          d1=0;
        else
          d-=13;
      }
  delay(10);
}
