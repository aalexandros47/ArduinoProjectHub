#include <Wire.h>
#include <U8g2lib.h>
#include <RTClib.h>
#include <Bounce2.h>
#include <EEPROM.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET -1
U8X8_SSD1306_128X64_NONAME_HW_I2C display(U8X8_PIN_NONE);

RTC_DS3231 rtc;

byte button_pins[] = {9, 5, 6}; // button pins, 4,5 = up/down, 6 = select
#define NUMBUTTONS sizeof(button_pins)
Bounce * buttons = new Bounce[NUMBUTTONS];
#define MENU_SIZE 3
char *menu[MENU_SIZE] = { "12 hour", "24 hour", "Alarm" };
int cursor=0;

const int setupPin = 2;
bool is24HourFormat = false;
bool alarm = false;
bool setup_flag = false;
int FORMAT_ADDRESS = 0;
int ALARM_ADDRESS = 1;

void setup() {
  Serial.begin(9600);
  
  if(!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while(1);
  }
  
  if(rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  display.begin();
    for (int i=0; i<NUMBUTTONS; i++) {
    buttons[i].attach( button_pins[i], INPUT_PULLUP); // setup the bounce instance for the current button
    buttons[i].interval(25); // interval in ms
  }
  pinMode(setupPin, INPUT_PULLUP);
  display.setFont(u8x8_font_pxplusibmcgathin_f);
  is24HourFormat = EEPROM.read(FORMAT_ADDRESS);
  alarm = EEPROM.read(ALARM_ADDRESS);
}

void loop() {
  if(!setup_flag)
  {
  DateTime now = rtc.now();
  
  display.clearDisplay();
  display.setCursor(0,0);
  
  if(is24HourFormat) {
    display.print(now.hour(), DEC);
  } else {
    display.print(now.hour() > 12 ? now.hour() - 12 : now.hour());
  }

  display.print(':');
  if(now.minute() < 10) {
    display.print('0');
  }
  display.print(now.minute());
  display.print(':');
  if(now.second() < 10) {
    display.print('0');
  }
  display.println(now.second());

  display.println(is24HourFormat ? "24H" : "12H");
  display.println();
  if(alarm)
  {
    display.print("Alarm set");
  }
  else
  {
    display.print("Alarm reset");
  }
  display.display();
  delay(1000);
  }
  else if(setup_flag)
  {
    for (int i = 0; i<NUMBUTTONS; i++) {
    buttons[i].update(); // Update the Bounce instance
    if ( buttons[i].fell() ) { // If it fell
      if (i==2) { // select
         display.clearLine(7);
         display.setCursor(0,7);
         display.print(">>");
         display.print(menu[cursor]);
         if(cursor == 0)
         {
          is24HourFormat = false;
          EEPROM.write(FORMAT_ADDRESS, is24HourFormat);
         }
         if(cursor == 1)
         {
           is24HourFormat = true;
           EEPROM.write(FORMAT_ADDRESS, is24HourFormat);
         }
         if(cursor == 2)
         {
           alarm = !alarm;
           EEPROM.write(ALARM_ADDRESS, alarm);
         }
         if(cursor == 2)
         {
         display.print(alarm ? " set" : " reset");
         }
         else
         {
         display.print(" set");
         }
      }
      else {
        // erase previous cursor:
        display.setCursor(0,cursor);
        display.print(' ');
        if (i==0) { // up
          cursor++;
          if (cursor>(MENU_SIZE-1)) cursor=0;
        }
        else { // down
          cursor--;
          if (cursor<0) cursor=(MENU_SIZE-1);
        }
        // show cursor at new line:
        display.setCursor(0,cursor);
        display.print('>');
      }
    } // end if button fell...
  } // end for-loop of button check
   // is24HourFormat = !is24HourFormat;
  }

  if(digitalRead(setupPin) == LOW) {
    setup_flag = !setup_flag;
    showMenu();
    while(digitalRead(setupPin) == LOW) { delay(10); }
  }

}

void showMenu() {
  cursor=0;
  display.clearDisplay();
  // show menu items:
  for (int i = 0; i<MENU_SIZE; i++) {
    display.drawString(2,i,menu[i]);
  }
  display.setCursor(0,0);
  display.print('>');
}
