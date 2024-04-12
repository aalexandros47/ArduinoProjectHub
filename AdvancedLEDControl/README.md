# Advanced LED Control

This Arduino sketch enables complex control over a set of LEDs and an 8x8 LED matrix, using push buttons and a dip switch for diverse functionalities. It incorporates toggling, speed adjustment, brightness control, and character display and movement on the LED matrix.

## Components Required:
- 1 Arduino board (Uno, Mega, etc.)
- 1 Breadboard
- 3 LEDs
- 4 Push buttons
- 1 Dip switch
- 1 8x8 LED matrix
- Resistors (220 ohms for LEDs, 10K ohms for buttons)
- Jumper wires
- 1 Potentiometer (optional, for brightness control)

## Circuit Setup:
1. Connect the LEDs to different digital pins on the Arduino via 220-ohm resistors.
2. Attach each push button to the Arduino with 10K-ohm pull-down resistors.
3. Connect the 8x8 LED matrix to appropriate digital and analog pins for controlling rows and columns.
4. Integrate the dip switch to select characters to be displayed on the matrix.

## Features and Controls:
- **Button 1**: Toggles the first LED on and off.
- **Button 2**: Increases the blinking speed of the second LED.
- **Button 3**: Decreases the blinking speed of the second LED.
- **Button 4**: Toggles the brightness of the third LED between high and low levels.
- **Dip Switch**: Selects which character (0-9, A-F) to display on the 8x8 LED matrix.
- **Additional Button for LED Matrix**:
  - **Single Press**: Moves the displayed character from left to right across the matrix.
  - **Hold and Release**: Changes the movement speed of the character (slow, medium, fast).

## Arduino Sketch Explanation:
The code includes setup for digital and analog pins, interrupt-driven button handling to manage debouncing, and PWM control for LED brightness. The dip switch input is read to determine which character to display, and the additional button manages character movement and speed settings.

## Installation:
1. Download the file.
2. Open it with the Arduino IDE.
3. Connect your Arduino setup to your computer via USB.
4. Upload the sketch to the Arduino board.

## Future Enhancements:
- Implement an LCD display for real-time feedback on speed and brightness settings.
- Add network capabilities to control the LEDs remotely.

Enjoy!
