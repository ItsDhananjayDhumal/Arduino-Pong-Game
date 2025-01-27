# Arduino Pong Game
IIT Indore Electronics Club

<img width="472" alt="image" src="https://github.com/user-attachments/assets/711fdc6c-7bf3-4df9-bde1-89aed6daca08" />

## Description
Pong is one of the first ever computer games ever made. We made pong game using Arduino microcontroller, which is displayed on 128 x 64 OLED screen. Game can be played in single player mode as well as two player mode.

## Table of contents
1. [Libraries](#libraries)
2. [Hardware](#hardware)

## Libraries
Following libraries were used for making this project:
* [`Adafruit_GFX.h`](https://learn.adafruit.com/adafruit-gfx-graphics-library) is a library developed by Adafruit to create graphics on LCD and OLED displays and LED matrices.
* [`Adafruit_SSD1306.h`](https://github.com/adafruit/Adafruit_SSD1306) is used to drive monochrome 128 x 64 and 128 x 32 OLED displays.
* [`SPI.h`](https://docs.arduino.cc/language-reference/en/functions/communication/SPI/) is used for communication between Arduino and SPI devices. Used only when OLED used SPI protocol, not needed for I2C.
* [`Wire.h`](https://docs.arduino.cc/language-reference/en/functions/communication/wire/) is used for I2C protocol.

## Hardware
* 128 x 64 OLED Screen
* Arduino UNO
* Joysticks

## Code Implementation
### Single Player Pong
In this mode player 2 joystick is disabled. Ball gets reflected from all boundaries except for the sind on which pad is present (left side). Every time ball hits the pad, its velocity in x direction is randomized between 1 to 3 pixels per iteration. Speed in y direction is constant 2 pixels per iteration. The sign of speed values is reversed whenever ball collides with boundary or pad.
Value of joystick is measured per iteration and pad is moved depending on the value.
### Two Player Pong
There are 2 pads in this mode, each controlled by one joystick. Rest code is similar to single player pong.
