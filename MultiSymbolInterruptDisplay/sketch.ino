#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define BUTTON_PIN 2
volatile bool button_pressed = false;
volatile int current_bitmap = 0;

const unsigned char bitmap1[] PROGMEM = {0x00, 0x3C, 0x42, 0x81, 0xA5, 0x81, 0x81, 0x42, 0x3C, 0x00};
const unsigned char bitmap2[] PROGMEM = {0x00, 0x1E, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x1E, 0x00};
const unsigned char bitmap3[] PROGMEM = {0x00, 0x00, 0x18, 0x24, 0x24, 0x18, 0x00, 0x00, 0x00, 0x00};

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
    display.drawBitmap(0, 0, get_current_bitmap(), 10, 10, 1);
    display.display();
  }
}

void button_interrupt() {
  current_bitmap = (current_bitmap + 1) % 3;
  button_pressed = true;
}

const unsigned char* get_current_bitmap() {
  switch (current_bitmap) {
    case 0:
      return bitmap1;
    case 1:
      return bitmap2;
    case 2:
      return bitmap3;
    default:
      return bitmap1;
  }
}