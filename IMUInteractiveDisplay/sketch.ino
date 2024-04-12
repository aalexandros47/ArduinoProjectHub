// Import necessary libraries
#include <Adafruit_SSD1306.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

// Define OLED screen dimensions
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// Initialize SSD1306 display object
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Initialize MPU6050 sensor object
Adafruit_MPU6050 mpu;

// Define car symbol to be displayed on screen
const unsigned char PROGMEM carSymbol[] = {
  0b00000000,
  0b00000000,
  0b00001110,
  0b00010001,
  0b00010001,
  0b00010001,
  0b00010001,
  0b00011111,
  0b00000000,
  0b00011111,
  0b00010001,
  0b00010001,
  0b00010001,
  0b00010001,
  0b00001110,
  0b00000000,
};

// Define size of car symbol (8x8 pixels)
const uint8_t symbolSize = 8;

// Define initial position of car symbol (center of screen)
int symbolX = (SCREEN_WIDTH - symbolSize) / 2;
int symbolY = (SCREEN_HEIGHT - symbolSize) / 2;

// Define variables for acceleration and speed values
float accelX, accelY;
float speedX = 0, speedY = 0;
float iAccelX, iAccelY;

bool flag = 0; // flag to keep status of first acceleration after reset

// Define maximum speed limit
float maxSpeed = 3;

sensors_event_t event;

// Setup function
void setup() {
  // Begin serial communication
  Serial.begin(9600);
  
  // Initialize OLED display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  // Initialize MPU6050 sensor and check connection
  while (!mpu.begin()) {
    Serial.println("MPU6050 not connected!");
    delay(1000);
  }
  mpu.getAccelerometerSensor()->getEvent(&event);
  iAccelX = event.acceleration.x; // initial x acceleration after start/reset
  iAccelY = event.acceleration.y;  // initial y acceleration after start/reset
}

// Loop function
void loop() {
  // Clear display buffer
  display.clearDisplay();

  // Get acceleration values from MPU6050 sensor
  mpu.getAccelerometerSensor()->getEvent(&event);
  accelX = event.acceleration.x;
  accelY = event.acceleration.y;
  
  // if acceleration is not equal to initial acceleration, make first acceleration flag true
  if( (accelX != iAccelX) || (accelY != iAccelY) )
  {
    flag = 1;
  }
  if(flag == 1) // Update symbol if first acceleration flag is true, otherwise it will stay at centre of screen
  {
  // Update speed values based on acceleration values
  speedX += accelX / 100.0;
  speedY += accelY / 100.0;

  // Limit speed values to maximum speed limit
  speedX = constrain(speedX, -maxSpeed, maxSpeed);
  speedY = constrain(speedY, -maxSpeed, maxSpeed);

  // Update symbol position based on speed values
  symbolX += round(speedX);
  symbolY += -round(speedY);

  // Keep symbol within the OLED display boundary
  if (symbolX < 0) {
    symbolX = 0;
    speedX = 0;
  } else if (symbolX > SCREEN_WIDTH - symbolSize) {
    symbolX = SCREEN_WIDTH - symbolSize;
    speedX = 0;
  }
  if (symbolY < 0) {
    symbolY = 0;
    speedY = 0;
  } else if (symbolY > SCREEN_HEIGHT - symbolSize) {
    symbolY = SCREEN_HEIGHT - symbolSize;
    speedY = 0;
  }
  }

  // draw car symbol at new position
  display.drawBitmap(symbolX, symbolY, carSymbol, symbolSize, symbolSize, SSD1306_WHITE);

  // print coordinates of symbol to serial monitor
  Serial.print("X: ");
  Serial.print(symbolX-60);
  Serial.print(", Y: ");
  Serial.println(-(symbolY-28));

  display.display(); // display buffer
  delay(20); // delay to control speed
}