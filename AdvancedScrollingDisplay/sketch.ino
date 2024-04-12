// libraries
#include "SPI.h" // SPI display
#include "Adafruit_GFX.h" // Adafruit graphics
#include "Adafruit_ILI9341.h" // ILI9341 screen controller

// pin definitions
#define TFT_DC 9
#define TFT_CS 53

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC); // hardware SPI

void setup() {
  tft.begin();
  tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK); // White on black
  tft.setTextWrap(false); // Don't wrap text to next line
  tft.setTextSize(2); // large letters
  tft.setRotation(0); // horizontal display
}

void loop() {
  String line1 = " 103494114    "; // sample text
  String line2 = " Arnob Ghosh    "; // sample text
  String line3 = " ENG20009    "; // sample text
  String line4 = " Engineering Technology Inquiry Project    "; // sample text
  String line5 = " Semester 1    "; // sample text
  String line6 = " 2023    "; // sample text

  const int width = 18; // width of the marquee display (in characters)

  // Loop once through the string
  for (int offset = 0; offset < line4.length(); offset++) {

    // Construct the string to display for this iteration
    String t1 = "";
    String t2 = "";
    String t3 = "";
    String t4 = "";
    String t5 = "";
    String t6 = "";
    for (int i = 0; i < width; i++) {
      t1 += line1.charAt((offset + i) % line1.length());
      t2 += line2.charAt((offset + i) % line2.length());
      t3 += line3.charAt((offset + i) % line3.length());
      t4 += line4.charAt((offset + i+20) % line4.length());
      t5 += line5.charAt((offset + i) % line5.length());
      t6 += line6.charAt((offset + i) % line6.length());
    }

    // Print the strings for this iteration
    tft.setCursor(0, 0); // line 1
    tft.print(t1);

    tft.setCursor(0, tft.height() / 7); // line 2
    tft.print(t2);

    tft.setCursor(0, 2 * tft.height() / 7); // line 3
    tft.print(t3);

    tft.setCursor(0, 3 * tft.height() / 7); // line 4
    tft.print(t4);

    tft.setCursor(0, 4 * tft.height() / 7); // line 5
    tft.print(t5);

    tft.setCursor(0, 5 * tft.height() / 7); // line 6
    tft.print(t6);

    // Short delay so the text doesn't move too fast
    delay(200);
  }
}