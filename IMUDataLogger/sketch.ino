#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_MPU6050.h>
#include <SPI.h>
#include <SD.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define BUTTON_PIN 2
volatile bool buttonState = false;

File dataFile;
const int chipSelect = 53;

Adafruit_MPU6050 mpu;
sensors_event_t a, g, temp;
float temperature = 0;
String timestamp;
String filename = "data.txt";

void setup() {
  Serial.begin(9600);

  // Initialize OLED display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  // Initialize MPU6050 sensor
  if (!mpu.begin()) {
    display.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }

  // Initialize SD card
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.print("Initializing SD card...");
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");

  // Create file and write headers
  if (SD.exists(filename)) {
    SD.remove(filename);
  }
  dataFile = SD.open(filename, FILE_WRITE);
  if (dataFile) {
    dataFile.println("Time, Temp");
  }
  else {
    display.println("Error opening file");
    while (1) {
      delay(10);
    }
  }

  // Initialize button pin
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonISR, FALLING);


  // Display ready message
  display.setCursor(0, 0);
  display.println("Data logger ready");
  display.display();
}

void loop() {
  // Check if button is pressed
  if (buttonState) 
  {
    // Read data from file and display
    if (SD.exists(filename)) {
      dataFile = SD.open(filename);
      while (dataFile.available()) {
        display.clearDisplay();
        display.setCursor(0,0);
        display.println("Time, Temp");
        display.setCursor(0,15);
        display.println(dataFile.readStringUntil('\n'));
        Serial.println(dataFile.readStringUntil('\n'));
      }
      dataFile.close();
      display.display();
    }
    else {
      display.clearDisplay();
      display.println("Error opening file");
      display.display();
    }
    buttonState = false;
  }
  else {
    // Get current timestamp and temperature value
    timestamp = String(millis());
    mpu.getEvent(&a, &g, &temp);
    temperature = temp.temperature;

    // Write data to file
    dataFile = SD.open("data.txt", FILE_WRITE);
    if (dataFile) {
      dataFile.print(timestamp);
      dataFile.print(", ");
      dataFile.print(temperature);
      dataFile.println(" C");
      dataFile.close();
      delay(2000);
    }
    else {
      display.clearDisplay();
      display.println("Error opening file");
      display.display();
    }
  }
}

void buttonISR() {
  buttonState = true;
}
