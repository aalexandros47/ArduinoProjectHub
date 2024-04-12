// output devices
const int buzzer = 8; // buzzer connected to pin 8 of arduino
const int redLed = 9; // red led connected to pin 9
const int blueLed = 10; // blue led connected to pin 10

// globals
volatile byte buzzerStatus = LOW; // holds the current state of the buzzer
volatile byte blueLedStatus = LOW; // holds the current state of the blue LED
volatile byte redLedStatus = LOW; // holds the current state of the red LED

unsigned long previousMillis = 0; // holds the time when the last blink of the red LED occurred
int blinkDelay = 1000; // the initial delay between blinks of the red LED
int shift = 25; // the amount by which to adjust the blink delay

int lowToHigh = 0; // indicates whether the blue LED should increase in brightness
int highToLow = 0; // indicates whether the blue LED should decrease in brightness
int DC = 0; // the current duty cycle (brightness) of the blue LED
int LED_MAX = 255; // the maximum brightness of the blue LED

void setup() {
  Serial.begin(9600); // start serial communication with a baud rate of 9600
  pinMode(buzzer, OUTPUT); // set the buzzer pin to output mode
  pinMode(blueLed, OUTPUT); // set the blue LED pin to output mode
  pinMode(redLed, OUTPUT); // set the red LED pin to output mode

  // print instructions for controlling the devices to the serial monitor
  Serial.println("Enter 1 to toggle buzzer");
  Serial.println("Enter 2 to increase blink speed");
  Serial.println("Enter 3 to decrease blink speed");
  Serial.println("Enter 4 to toggle blue LED");

  Serial.println(); // print a blank line
}

void loop() {
  if (Serial.available()) { // check if there is any input coming through the serial port
    char input = Serial.read(); // read the input character
    switch (input) {
      case '1':
        buzzerStatus = !buzzerStatus; // toggle the buzzer state
        digitalWrite(buzzer, buzzerStatus); // turn the buzzer on or off
        // print the current state of the buzzer to the serial monitor
        Serial.println(buzzerStatus ? "Buzzer is on" : "Buzzer is off");
        break;
      case '2':
        blinkDelay -= shift; // decrease the blink delay
        if (blinkDelay < 200) { // limit the minimum blink delay to 200 ms
          blinkDelay = 200;
        }
        // print the new blink delay to the serial monitor
        Serial.print("Blink delay is now ");
        Serial.print(blinkDelay);
        Serial.println(" ms");
        break;
      case '3':
        blinkDelay += shift; // increase the blink delay
        if (blinkDelay > 2000) { // limit the maximum blink delay to 2000 ms
          blinkDelay = 2000;
        }
        // print the new blink delay to the serial monitor
        Serial.print("Blink delay is now ");
        Serial.print(blinkDelay);
        Serial.println(" ms");
        break;
      case '4':
        // toggle the blue LED brightness direction flag
        if (lowToHigh == 0 && highToLow == 0) {
          lowToHigh = 1;
          Serial.println("Blue LED is now increasing in brightness");
        } else if (lowToHigh == 1 && highToLow == 0) {
          lowToHigh = 0;
          highToLow = 1;
          Serial.println("Blue LED is now decreasing in brightness");
        } else if (lowToHigh == 0 && highToLow == 1) {
          lowToHigh = 1;
          highToLow = 0;
          Serial.println("Blue LED is now increasing in brightness");
        }
        break;
      default:
        break;
    }
  }

  unsigned long currentMillis = millis(); // get the current time

  if (currentMillis - previousMillis >= blinkDelay) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (redLedStatus == LOW) {
      redLedStatus = HIGH;
    } else {
      redLedStatus = LOW;
    }

    // set the LED with the ledState of the variable:
    digitalWrite(redLed, redLedStatus);
  }

  if (lowToHigh == 1){ // if blue LED brighness is going low to high
    DC += 25; // increase PWM value (brightness)
    delay(100);
    if (DC >= LED_MAX){ // if brighness is maximum
      DC = LED_MAX; // Keep it at maximum
    }
  }

  if (highToLow){ // if blue LED brighness is going high to low
    DC -= 25; //decrease PWM value (brightness)
    delay(100);
    if (DC <= 0){ // if brighness is minimum (zero)
      DC = 0; // Keep it at zero
    }
  }
  analogWrite(blueLed, DC); // Write PWM value to PWM pin
}


