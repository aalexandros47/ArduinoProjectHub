#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const int BUTTON_PIN1 = 2;
const int BUTTON_PIN2 = 3;
const int POT_PIN = A0;
int speed = 2;
int x = 0;
int waveform = 0;
float frequency = 1.0;
int previous_y = 0;

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN1, INPUT_PULLUP);
  pinMode(BUTTON_PIN2, INPUT_PULLUP);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();
}

void loop() {
  // Read button states
  int buttonState1 = digitalRead(BUTTON_PIN1);
  int buttonState2 = digitalRead(BUTTON_PIN2);

  // Change waveform if button 1 is pressed
  if (buttonState1 == LOW) {
    waveform = (waveform + 1) % 4;
    delay(200);
  }

  // Change frequency if potentiometer is turned
  frequency = map(analogRead(POT_PIN), 0, 1023, 1, 5);

  // Change speed if button 2 is pressed
  if (buttonState2 == LOW) {
    speed += 5;
    if (speed > 12) {
      speed = 1;
    }
    delay(200);
  }

  // Clear display buffer
  display.clearDisplay();

  // Draw waveform
  for (int i = 0; i < SCREEN_WIDTH; i++) {
    int y = 0;
    switch (waveform) {
      case 0: // Sine wave
        y = (SCREEN_HEIGHT / 2) + (sin((x + i) * frequency * 0.1) * (SCREEN_HEIGHT / 2));
        break;
      case 1: // Square wave
        y = ((i + x) % (int)(20.0/frequency) < (int)(10.0/frequency)) ? SCREEN_HEIGHT - 1 : 0;
        if(y != previous_y)
        {
          display.drawFastVLine(i, 0, 32, WHITE);
          previous_y = y;
        }
        break;
      case 2: // Triangle wave
        y = abs(((i + x) % (int)(40.0/frequency)) - (int)(20.0/frequency)) * (SCREEN_HEIGHT / (int)(20.0/frequency));
        break;
      case 3: // Sawtooth wave
        y = ((i + x) % (int)(20.0/frequency)) * (SCREEN_HEIGHT / (int)(20.0/frequency));
        if(y == 19)
        {
          display.drawFastVLine(i, 0, 20, WHITE);
        }
        break;
    }
    display.drawPixel(i, y, WHITE); // Move waveforms from left to right
  }

  // Update x position
  x += speed;

  // Update display
  display.display();
}