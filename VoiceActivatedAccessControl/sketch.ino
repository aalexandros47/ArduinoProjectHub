#include <Wire.h> // Include the Wire library for I2C communication
#include <Adafruit_GFX.h> // Include the Adafruit_GFX library for graphics
#include <Adafruit_SSD1306.h> // Include the Adafruit_SSD1306 library for the OLED display

#define OLED_RESET 4 // Define the reset pin for the OLED display
Adafruit_SSD1306 display(OLED_RESET); // Create an instance of the OLED display

const int micPin = A0; // Define the pin number for the microphone input
const int potPin = A1; // Define the pin number for the potentiometer input

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Initialize the OLED display
  Serial.begin(9600);
}

void loop() {
  int micValue = analogRead(micPin); // Read the microphone input
  int potValue = analogRead(potPin); // Read the potentiometer input

  float sensitivity = map(potValue, 0, 1023, 1.0, 10.0); // Map the potentiometer value to a sensitivity value

  float voltage = micValue * (5.0 / 1023.0); // Convert the microphone value to a voltage value
  float db = 20 * log10(voltage / 0.00002); // Convert the voltage value to a decibel (dB) value

  float frequency = 0.0; // Initialize the frequency value to 0 Hz

  // Calculate the frequency only if the sound level is above a certain threshold
  if (db > 49) {
    frequency = pow(10, (db - 49.0) / 10.0) * 0.003; // Calculate the frequency based on the dB value
    frequency *= sensitivity; // Adjust the frequency based on the sensitivity value
  }

  // Print frequency on serial monitor
  Serial.print("Frequency: ");
  Serial.print(frequency);
  Serial.println(" Hz");

  // Display the frequency value on the OLED display
  display.clearDisplay(); // Clear the display
  display.setTextSize(2); // Set the text size to 2
  display.setTextColor(WHITE); // Set the text color to white
  display.setCursor(0,0); // Set the cursor to the top-left corner of the display
  display.print("Frequency:"); // Print the text "Frequency:"
  display.setCursor(0,16); // Set the cursor to the second row of the display
  display.print(frequency); // Print the frequency value
  display.print(" Hz"); // Print the unit "Hz"
  display.display(); // Display the text on the OLED display
  delay(20);
}