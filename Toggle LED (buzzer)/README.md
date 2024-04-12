# Toggle First LED

This Arduino sketch allows you to toggle the first LED on a bar graph on and off using the first of four push buttons. It's a simple yet effective demonstration of handling digital inputs and outputs with Arduino.

## Components Required:
- 1 Arduino board (Uno, Mega, etc.)
- 1 Breadboard
- 3 LEDs
- 4 Push buttons
- Resistors (220 ohms for LEDs, 10K ohms for buttons)
- Jumper wires

## Circuit Setup:
1. Connect each LED through a 220-ohm resistor to different digital pins on the Arduino.
2. Connect each push button with a 10K-ohm pull-down resistor to another set of digital pins.
3. Ensure the common ground connection for LEDs and push buttons.

## How It Works:
- **Push Button 1**: Controls the first LED. Pressing this button toggles the first LED on the bar graph on and off.
- **LED State**: The first LED's state will change with each button press, switching between on and off.

## Arduino Sketch Explanation:
The code uses basic digital I/O functions:
- It initializes the digital pin connected to the first LED as an output and the pin connected to the first button as an input.
- In the loop, the Arduino reads the button's state. If the button is pressed, the LED's state is toggled from its current state.

## Installation:
1. Download the file.
2. Open it with the Arduino IDE.
3. Connect your Arduino board to your computer via USB.
4. Upload the sketch to the board.

## Enhancements:
- Add debounce logic to the button to prevent false triggering due to button "bounce."
- Implement additional functionality for the other three buttons and LEDs.

Enjoy!!
