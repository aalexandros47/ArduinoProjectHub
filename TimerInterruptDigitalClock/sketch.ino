#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Digital Clock Variables. Change them to get set time as required
volatile int seconds = 0;
volatile int minutes = 0;
volatile int hours = 0;
volatile bool isAnalogClock = false;
volatile bool buttonPressed = false;

// Button Interrupt
#define BUTTON_PIN 2
volatile bool buttonState = false;

void buttonISR() {
  buttonState = true;
}

// Timer Interrupt
volatile bool timerFlag = false;

ISR(TIMER1_COMPA_vect) {
  timerFlag = true;
}

void setup() {
  // Initialize OLED Display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();

  // Initialize Timer Interrupt
  cli(); // disable interrupts
  TCCR1A = 0; // set entire TCCR1A register to 0
  TCCR1B = 0; // same for TCCR1B
  TCNT1 = 0; // initialize counter value to 0
  OCR1A = 15624; // = (16*10^6) / (256*1) - 1 (must be <65536)
  TCCR1B |= (1 << WGM12); // turn on CTC mode
  TCCR1B |= (1 << CS12) | (1 << CS10); // set prescaler to 1024
  TIMSK1 |= (1 << OCIE1A); // enable timer compare interrupt
  sei(); // enable interrupts

  // Initialize Button Interrupt
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonISR, FALLING);
}

void loop() {
  if (buttonState) {
    buttonPressed = true;
    buttonState = false;
  }

  if (timerFlag) {
    timerFlag = false;

    // Increment Time
    seconds++;
    if (seconds == 60) {
      seconds = 0;
      minutes++;
      if (minutes == 60) {
        minutes = 0;
        hours++;
        if (hours == 24) {
          hours = 0;
        }
      }
    }
  }

  display.clearDisplay();

  if (isAnalogClock) {
    // Draw Analog Clock
   /* int hours = lastSecond / 3600;
    int minutes = (lastSecond / 60) % 60;
    int seconds = lastSecond % 60;*/
    int hourAngle = map(hours % 12, 0, 12, 0, 360);
    int minuteAngle = map(minutes, 0, 60, 0, 360);
    int secondAngle = map(seconds, 0, 60, 0, 360);
    display.clearDisplay();
    display.drawCircle(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SCREEN_HEIGHT / 2 - 2, WHITE);
    display.fillCircle(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 2, WHITE);
    display.drawLine(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 
                      SCREEN_WIDTH / 2 + (SCREEN_HEIGHT / 2 - 4) * cos((hourAngle - 90) * DEG_TO_RAD),
                      SCREEN_HEIGHT / 2 + (SCREEN_HEIGHT / 2 - 4) * sin((hourAngle - 90) * DEG_TO_RAD),
                      WHITE);
    display.drawLine(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 
                      SCREEN_WIDTH / 2 + (SCREEN_HEIGHT / 2 - 2) * cos((minuteAngle - 90) * DEG_TO_RAD),
                      SCREEN_HEIGHT / 2 + (SCREEN_HEIGHT / 2 - 2) * sin((minuteAngle - 90) * DEG_TO_RAD),
                      WHITE);
    display.drawLine(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 
                      SCREEN_WIDTH / 2 + (SCREEN_HEIGHT / 2 - 1) * cos((secondAngle - 90) * DEG_TO_RAD),
                      SCREEN_HEIGHT / 2 + (SCREEN_HEIGHT / 2 - 1) * sin((secondAngle - 90) * DEG_TO_RAD),
                      WHITE);
    display.display();
  } else {
    // Draw Digital Clock
    display.setCursor(0, 0);
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.print(hours);
    display.print(":");
    if (minutes < 10) {
      display.print("0");
    }
    display.print(minutes);
    display.print(":");
    if (seconds < 10) {
      display.print("0");
    }
    display.print(seconds);
  }

  display.display();
  delay(1000);

  if (buttonPressed) {
    isAnalogClock = !isAnalogClock;
    buttonPressed = false;
  }
}