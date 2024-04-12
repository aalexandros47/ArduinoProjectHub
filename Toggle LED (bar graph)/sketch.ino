
#define  PB1 2
#define  PB2 3
#define  PB3 4
#define  PB4 5
#define LB1 11 //LED BAR
#define LB2  10
#define LB3 9

#define BLINK_DELAY_STEP 100

int blink_delay=500; //100 ms 
unsigned long last_blink=0;

void setup() {
  // put your setup code here, to run once:
pinMode(PB1, INPUT_PULLUP);
pinMode(PB2, INPUT_PULLUP);
pinMode(PB3, INPUT_PULLUP);
pinMode(PB4, INPUT_PULLUP);

pinMode(LB1, OUTPUT);
pinMode(LB2, OUTPUT);
pinMode(LB3, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(!digitalRead(PB1))
  {
  digitalWrite(LB1,! digitalRead(LB1));
  delay(200);
  }
   if(!digitalRead(PB2))
  {
  blink_delay+=BLINK_DELAY_STEP;
  delay(200);
  }
  if(!digitalRead(PB3))
  {
  blink_delay-=BLINK_DELAY_STEP;
  blink_delay= blink_delay<0?0: blink_delay;
    delay(200);
  }
if(millis()-last_blink>blink_delay)
{
  digitalWrite(LB2,! digitalRead(LB2));
  last_blink=millis();
}
 if(!digitalRead(PB4))
  {
  digitalWrite(LB3,! digitalRead(LB3));
  delay(200);
  }

  

}
