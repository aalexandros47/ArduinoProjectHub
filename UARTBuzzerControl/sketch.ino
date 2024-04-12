// output devices
const int buzzer = 8; // buzzer connected to pin 8 of arduino

// globals
volatile byte buzzerStatus = LOW; // holds the current state of the buzzer


void setup() {
  Serial.begin(9600); // start serial communication with a baud rate of 9600
  pinMode(buzzer, OUTPUT); // set the buzzer pin to output mode
 
  // print instructions for controlling the devices to the serial monitor
  Serial.println("Enter 1 to toggle buzzer");
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
    }
  }
}


