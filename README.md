# Arduino Pong Game
**IIT Indore Electronics Club**

![Screenshot_2025-01-27_144929-transformed](https://github.com/user-attachments/assets/4e8f34a1-3428-48ec-8ef9-8b09416c297e)


## Description
Pong is one of the first ever computer games ever made. We made pong game using Arduino microcontroller, which is displayed on 128 x 64 OLED screen. Game can be played in single player mode as well as two player mode.

## Table of contents
1. [Libraries](#libraries)
2. [Hardware](#hardware)
3. [Framework](#framework)
4. [Project](#project)
5. [Installlation](#installation)

## Libraries
Following libraries were used for making this project:
> * [`Adafruit_GFX.h`](https://learn.adafruit.com/adafruit-gfx-graphics-library) is a library developed by Adafruit to create graphics on LCD and OLED displays and LED matrices.
> * [`Adafruit_SSD1306.h`](https://github.com/adafruit/Adafruit_SSD1306) is used to drive monochrome 128 x 64 and 128 x 32 OLED displays.
> * [`SPI.h`](https://docs.arduino.cc/language-reference/en/functions/communication/SPI/) is used for communication between Arduino and SPI devices. Used only when OLED used SPI protocol, not needed for I2C.
> * [`Wire.h`](https://docs.arduino.cc/language-reference/en/functions/communication/wire/) is used for I2C protocol.

## Hardware
> * 128 x 64 OLED Screen
> * Arduino UNO
> * Joysticks
> * Jumper wires

## Framework
### Single Player Pong
In this mode player 2 joystick is disabled. Ball gets reflected from all boundaries except for the sind on which pad is present (left side). Every time ball hits the pad, its velocity in x direction is randomized between 1 to 3 pixels per iteration. Speed in y direction is constant 2 pixels per iteration. The sign of speed values is reversed whenever ball collides with boundary or pad.
Value of joystick is measured per iteration and pad is moved depending on the value.
### Two Player Pong
There are 2 pads in this mode, each controlled by one joystick. Ball is reflected only from vertical boundaries and both of the pads. Similar to single player mode, x direction speed of ball is randomized whenever it hits either of the pads. Rest is same as single player mode.

## Project
![WhatsApp Image 2025-01-27 at 15 25 53](https://github.com/user-attachments/assets/a34ad7e4-a0e8-4412-9b4a-ad13d268e069)
_Image of the setup_
### Single Player
![WhatsAppVideo2025-01-27at17 27 47-ezgif com-video-to-gif-converter](https://github.com/user-attachments/assets/e81aa0d6-4b2b-4c7e-8936-39eab3d1351f)

### Two Player
![WhatsAppVideo2025-01-27at17 33 02-ezgif com-video-to-gif-converter](https://github.com/user-attachments/assets/03989de1-8d4b-43be-a9de-49b3e1c8396f)

## Installation
```shell
git clone https://github.com/ItsDhananjayDhumal/OLED_Game
cd OLED_Pong
```
The [libraries](#libraries) mentioned above need to be separately downloaded
