int ledBarPins[10] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11}; // Assign LED bar pins to an array
int ldrPin = A0; // Assign LDR pin to A0
int luxThresholds[10] = {9, 22, 47, 115, 226, 453, 671, 904, 989, 1010}; // Assign lux thresholds for each LED

void setup() {
  for (int i = 0; i < 10; i++) {
    pinMode(ledBarPins[i], OUTPUT); // Set LED bar pins to output
  }
}

void loop() {
  int light = analogRead(ldrPin); // Read light level from LDR
  
  for (int i = 0; i < 10; i++) {
    if (light >= luxThresholds[i]) {
      digitalWrite(ledBarPins[i], HIGH); // Turn on LED if light level is above threshold
    }
    else {
      digitalWrite(ledBarPins[i], LOW); // Turn off LED if light level is below threshold
    }
  }
}