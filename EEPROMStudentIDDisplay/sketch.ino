#include <Wire.h>
#include <EEPROM.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

void setup() {
  Wire.begin();        // initialize I2C bus
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // initialize OLED display
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println("Writing to EEPROM...");
  display.display();
  delay(1000);

  // Write data to the first four memory locations of the EEPROM
  EEPROM.write(0, '1');
  EEPROM.write(1, '0');
  EEPROM.write(2, '3');
  EEPROM.write(3, '4');
  EEPROM.write(4, '9');
  EEPROM.write(5, '4');
  EEPROM.write(6, '1');
  EEPROM.write(7, '1');
  EEPROM.write(8, '4');

  display.clearDisplay();
  display.setCursor(0,0);
  display.println("Reading from EEPROM...");
  display.display();
  
  // Read data from the EEPROM and display it on the OLED display
  char readData[10];
  for (int i = 0; i < 9; i++) {
    readData[i] = EEPROM.read(i);
  }
  readData[9] = '\0';   // terminate the string
  display.clearDisplay();
  display.setCursor(0,0);
  display.setTextSize(1);
  display.println("Data from EEPROM:");
  display.setTextSize(1);
  display.setCursor(40,16);
  display.println(readData);
  display.display();
}

void loop() {
  // do nothing
}