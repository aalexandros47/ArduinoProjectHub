// input devices
const int greenBtn = 2;
const int redBtn = 3;
const int yellowBtn = 18;
const int blueBtn = 19;

// output devices
const int buzzer = 8;
const int redLed = 9;
const int blueLed = 10;

// globals
volatile byte buzzerStatus = LOW;
volatile byte blueLedStatus = LOW;
volatile byte redLedStatus = LOW;

unsigned long previousMillis = 0;
int blinkDelay = 1000;
int shift = 25;

int lowToHigh = 0;
int highToLow = 0;
int DC = 0;
int LED_MAX = 255;

void setup() {

  pinMode(greenBtn, INPUT_PULLUP);
  pinMode(redBtn, INPUT_PULLUP);
  pinMode(yellowBtn, INPUT_PULLUP);
  pinMode(blueBtn, INPUT_PULLUP);

  pinMode(buzzer, OUTPUT);
  pinMode(blueLed, OUTPUT);
  pinMode(redLed, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(greenBtn), toggleBuzzer, FALLING);
  attachInterrupt(digitalPinToInterrupt(redBtn), decreaseBlinkDelay, FALLING);
  attachInterrupt(digitalPinToInterrupt(yellowBtn), increaseBlinkDelay, FALLING);
  attachInterrupt(digitalPinToInterrupt(blueBtn), toggleBlueLed, FALLING);

  Serial.begin(9600);
}

void loop() {

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= blinkDelay) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (redLedStatus == LOW) {
      redLedStatus = HIGH;
    } else {
      redLedStatus = LOW;
    }

    // set the LED with the ledState of the variable:
    digitalWrite(redLed, redLedStatus);
  }


  if (lowToHigh == 1){
    DC+=25;
    if (DC>=LED_MAX){
      DC = LED_MAX;
      lowToHigh = 0;
    }
  }

  if (highToLow){
    DC-=25;
    if (DC<=0){
      DC=0;
      highToLow=0;
    }
  }

  analogWrite(blueLed, DC);

  // uncomment to see buzzer status, blue LED status and blink delay
  Serial.print("buzzer is: ");
  Serial.print(buzzerStatus? "ON":"OFF");
  Serial.print(" \t Blue LED DC is: ");
  Serial.print(DC);
  Serial.print(" \t Blink delay is: ");
  Serial.print(blinkDelay);
  Serial.println(" ms");

}


void toggleBuzzer() {
  buzzerStatus = !buzzerStatus;
  digitalWrite(buzzer, buzzerStatus); 
}

void toggleBlueLed() {

  if (lowToHigh == 0 && highToLow == 0) {
      lowToHigh = 1;
  } else if (lowToHigh == 1 && highToLow == 0) {
      lowToHigh = 0;
      highToLow = 1;
  } else if (lowToHigh == 0 && highToLow == 1) {
      lowToHigh = 1;
      highToLow = 0;
  }

}

void decreaseBlinkDelay() {
  blinkDelay = blinkDelay - shift;

  if (blinkDelay < 200) {
    blinkDelay = 200;
  }
  delay(500);
}

void increaseBlinkDelay() {
  blinkDelay = blinkDelay + shift;

  if (blinkDelay > 2000) {
    blinkDelay = 2000;
  }
  delay(500);
}