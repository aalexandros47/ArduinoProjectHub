#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

#define OLED_WIDTH 128
#define OLED_HEIGHT 32

Adafruit_MPU6050 mpu;
Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT, &Wire, -1);

int current_sensor = 0;
bool timer = false;


void setup() {
  Serial.begin(115200);
    // set up Timer1 interrupt to occur every 2 seconds (0.5Hz)
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;
  OCR1A = 31249;   // set compare match register to 2 seconds (16MHz / 1024 / 2 - 1)
  TCCR1B |= (1 << WGM12);  // turn on CTC mode
  TCCR1B |= (1 << CS12) | (1 << CS10);  // set prescaler to 1024 and start the timer
  TIMSK1 |= (1 << OCIE1A);  // enable Timer1 compare interrupt

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }

  pinMode(4, INPUT_PULLUP);

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_2000_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("IMU sensor data");
  display.display();
}

sensors_event_t a, g, temp;

void loop() {

    if(timer == true)
    {
      timer = false;
      mpu.getEvent(&a, &g, &temp);
    switch (current_sensor) {
      case 0: // Accelerometer
        display.clearDisplay();
        display.setCursor(0, 0);
        display.print("Accel X: ");
        display.print(a.acceleration.x);
        display.print(" m/s^2");
        display.setCursor(0, 10);
        display.print("Accel Y: ");
        display.print(a.acceleration.y);
        display.print(" m/s^2");
        display.setCursor(0, 20);
        display.print("Accel Z: ");
        display.print(a.acceleration.z);
        display.print(" m/s^2");
        break;
      case 1: // Gyroscope
        display.clearDisplay();
        display.setCursor(0, 0);
        display.print("Gyro X: ");
        display.print(g.gyro.x);
        display.print(" rad/s");
        display.setCursor(0, 10);
        display.print("Gyro Y: ");
        display.print(g.gyro.y);
        display.print(" rad/s");
        display.setCursor(0, 20);
        display.print("Gyro Z: ");
        display.print(g.gyro.z);
        display.print(" rad/s");
        break;
      case 2: // Temperature
        display.clearDisplay();
        display.setCursor(0, 0);
        display.print("Temp: ");
        display.print(temp.temperature);
        display.print(" degC");
        break;
    }

    display.display();
    }
  

  if (digitalRead(4) == LOW) {
    delay(200);
    current_sensor++;
    if (current_sensor >= 3) {
      current_sensor = 0;
    }
  }

  delay(100);
}


ISR(TIMER1_COMPA_vect) {  // timer1 interrupt service routine
  Serial.println("Reading MPU6050");
  timer = true;
}