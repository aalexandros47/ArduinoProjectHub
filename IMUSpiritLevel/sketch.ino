#include <Wire.h>               // include Wire library for I2C communication
#include <Adafruit_GFX.h>       // include Adafruit GFX library for graphics
#include <Adafruit_SSD1306.h>   // include Adafruit SSD1306 library for OLED display
#include <Adafruit_MPU6050.h>   // include Adafruit MPU6050 library for accelerometer
#include <Adafruit_Sensor.h>    // include Adafruit Sensor library for sensor data types

#define SCREEN_WIDTH 128        // define OLED screen width
#define SCREEN_HEIGHT 64        // define OLED screen height
#define OLED_RESET -1           // define OLED reset pin, set to -1 if unused

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);    // create instance of SSD1306 object with specified parameters

Adafruit_MPU6050 mpu;           // create instance of MPU6050 object

void setup() {
  Serial.begin(9600);          // initialize serial communication with 9600 baud rate
  while (!Serial) {            // wait for serial port to connect (needed for native USB port only)
    // do nothing
  }

  if (!mpu.begin()) {          // check if MPU6050 sensor is connected and initialized
    Serial.println("Failed to initialize MPU6050 sensor!");    // print error message to serial monitor
    while (1);                  // halt program execution
  }

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);   // initialize OLED display with specified parameters
  display.clearDisplay();                       // clear OLED display
  display.setTextColor(WHITE);                  // set text color to white
  display.setTextSize(1);                       // set text size to 1
}

void loop() {
  float xAngle, yAngle, zAngle;               // declare variables for storing calculated angles
  sensors_event_t event;                      // declare variable for storing accelerometer event data

  mpu.getAccelerometerSensor()->getEvent(&event);    // read accelerometer event data
  xAngle = atan2(-event.acceleration.x, sqrt(event.acceleration.y * event.acceleration.y + event.acceleration.z * event.acceleration.z));   // calculate X angle using accelerometer data
  yAngle = atan2(event.acceleration.y, sqrt(event.acceleration.x * event.acceleration.x + event.acceleration.z * event.acceleration.z));     // calculate Y angle using accelerometer data

  // calculate angles in degrees
  float xDegrees = xAngle * (180 / M_PI);    // convert X angle to degrees
  float yDegrees = yAngle * (180 / M_PI);    // convert Y angle to degrees

  display.clearDisplay();                     // clear OLED display

  // draw horizontal and vertical lines on OLED display
  display.drawLine(63, 31, 127, 31, WHITE);   // draw horizontal line
  display.drawLine(95, 0, 95, 63, WHITE);     // draw vertical line

  // calculate and draw angle indicators
  int xIndicatorX = map(xDegrees, -90, 90, 63, 127);    // map X angle to OLED display coordinates
  int yIndicatorY = map(yDegrees, -90, 90, 63,0);       // map Y angle to OLED display coordinates
  display.fillCircle(xIndicatorX, 31, 3, WHITE);         // draw X angle indicator
  display.fillCircle(95, yIndicatorY, 3, WHITE);         // draw Y angle indicator

  // display angle values on OLED
  display.setCursor(0, 0);
  display.print("X:");
  display.print(xDegrees);
  display.print(" deg");

  display.setCursor(0, 10);
  display.print("Y:");
  display.print(yDegrees);
  display.print(" deg");

  display.display();
  delay(50);
}