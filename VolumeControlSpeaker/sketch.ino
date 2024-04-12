int potPin = A0;    // Analog input pin for potentiometer
int buzzerPin = 9;  // PWM capable digital output pin for buzzer/speaker

void setup() {
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  // Read potentiometer value and map to PWM duty cycle range
  int potValue = analogRead(potPin);
  // 150 for upper limit of duty cycle is for simulatio, change it to 255 for hardware
  int dutyCycle = map(potValue, 0, 1023, 0, 150);

  // Play tone with mapped duty cycle
  analogWrite(buzzerPin, dutyCycle);
}