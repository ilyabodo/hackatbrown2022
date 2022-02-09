# Greenhouse Monitor - Hack @ Brown 2022

## Inspiration
We wanted to create a hardware hack, because we both enjoy working with embedded systems and interacting at a low level with hardware.
## What it does
This project is a hardware hack device that will constantly monitor the current air temperature and humidity. If values are within a configurable range, an RGB led will provide a gradient between two colors to visualize how the current temp/humidity fits within your set range.
eg. if max temp = 100, min temp = 0, and current temp = 90, RGB LED will be mostly red.
If the current temperature/humidity is out of range, one of two other LEDs will light up to indicate if the temperature/humidity is too high or too low.
eg. if max temp = 50, min temp = 0, and current temp = 75, red LED will turn on, RGB led will turn off.
Current temperature and humidity data can also be read on the OLED I2C display.
## How we built it
We used an Arduino Uno, a breadboard, 128x64 white I2C OLED display, temperature/humidity sensor, 2 RGB LEDS, and 4 various single colored LEDS. The code was written in C++ using the Arduino IDE and related sensor/display libraries.
## Challenges we ran into
We ran into issues with getting the RGB LEDs to work, since they used a common anode, instead of a common cathode, which took a while to debug and fix.
## Accomplishments that we're proud of
We are proud that we were able to complete this hardware hack despite the blizzard, and make a successful hack despite the lack of access to additional materials and working virtually.
## What we learned
We familiarized ourselves with the I2C protocol and with PWM led controls.
## What's next for Greenhouse Monitor
We would like to include additional sensors, for example: light, soil moisture, and rainfall sensors (which we did not have on hand at the time). We would also like to use a small webserver to allow for remote configuration.
