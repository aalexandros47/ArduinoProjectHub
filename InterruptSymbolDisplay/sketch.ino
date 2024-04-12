#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define BUTTON_PIN 2
volatile bool button_pressed = false;

const unsigned char bitmap1[] PROGMEM = {0x00, 0x3C, 0x42, 0x81, 0xA5, 0x81, 0x81, 0x42, 0x3C, 0x00};

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), button_interrupt, FALLING);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay(); // clear the OLED display
  display.display();
}

void loop() {
  if (button_pressed) {
    button_pressed = false;
    display.clearDisplay();
    display.drawBitmap(0, 0, bitmap1, 10, 10, 1);
    display.display();
  }
}

void button_interrupt() {
  button_pressed = true;
}