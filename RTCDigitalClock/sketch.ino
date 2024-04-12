#include <Wire.h>  // include the Wire library for I2C communication
#include <Adafruit_SSD1306.h>  // include the Adafruit SSD1306 library for OLED display
#include <RTClib.h>  // include the RTClib library for RTC module

RTC_DS3231 rtc;  // create an instance of RTC_DS3231 class for RTC module
Adafruit_SSD1306 display(128, 32, &Wire, -1);  // create an instance of Adafruit_SSD1306 class for OLED display

void setup() {
  Wire.begin();  // start I2C communication
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize OLED display with voltage level converter and I2C address
  rtc.begin();  // initialize RTC module
  
  display.clearDisplay();  // clear the OLED display
  display.setTextColor(WHITE);  // set text color to white
  display.setTextSize(2);  // set text size to 2
  display.setCursor(0,0);  // set cursor position to top-left corner
}

void loop() {
  DateTime now = rtc.now();  // get current date and time from RTC module
  
  display.clearDisplay();  // clear the OLED display
  display.setCursor(0,0);  // set cursor position to top-left corner
  display.print(now.hour(), DEC);  // print hour value
  display.print(':');  // print colon separator
  if (now.minute() < 10) {  // add leading zero if minute value is less than 10
    display.print('0');
  }
  display.print(now.minute(), DEC);  // print minute value
  display.print(':');  // print colon separator
  if (now.second() < 10) {  // add leading zero if second value is less than 10
    display.print('0');
  }
  display.println(now.second(), DEC);  // print second value and move to the next line
  display.display();  // display the content on the OLED display
  
  delay(1000);  // wait for one second before updating the display with new time value
}