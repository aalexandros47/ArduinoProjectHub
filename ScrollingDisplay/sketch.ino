#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET); // create an instance of the Adafruit_SSD1306 class

const char studentName[] PROGMEM = "Arnob Ghosh.";
const char studentID[] PROGMEM = "03494114 ";

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // initialize the OLED display with the specified I2C address
  display.clearDisplay(); // clear the display buffer
  display.setTextSize(2); // set the text size to 2
  display.setTextColor(SSD1306_WHITE); // set the text color to white
  display.setCursor(0, 0); // set the cursor position to the top-left corner of the display
  display.println((const __FlashStringHelper*)studentName); // print the student name to the display
  display.setCursor(0, 16); // set the cursor position to the second row of the display
  display.println((const __FlashStringHelper*)studentID); // print the student ID to the display
  display.display(); // update the display with the contents of the display buffer
  display.startscrollleft(0x00, 0x03); // start scrolling the display from right to left
}

void loop() {
  // nothing to do here, since the display is already scrolling
}