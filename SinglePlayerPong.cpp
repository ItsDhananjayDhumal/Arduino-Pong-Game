#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <Wire.h>


//OLED Screen setup
#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels


#define JOYSTICK A0  // joystick pin
int jRead;


#define PADLEN 18   // length of pad
int padY = 0;       // y coordinate of top pixel of pad
#define padSpeed 2  // drift speed of pad


//####################### UNCOMMENT IF I2C #################################
#define OLED_SCL A5
#define OLED_SDA A4
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
//###########################################################################

// // ######################## UNCOMMENT IF SPI #############################
// #define OLED_MOSI   9
// #define OLED_CLK   10
// #define OLED_DC    11
// #define OLED_CS    12
// #define OLED_RESET 13
// Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
//   OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);
// // ########################################################################

// coordinates and speed of ball
int xdir = 2;  // speed in x
int ydir = 1;  // speed in y
int i = 10;    // x coordinate
int j = 15;    // y coordinate


// score
int score = 0;


//#######################################################################################
//#######################################################################################

void setup() {
  Serial.begin(9600);
  // display.begin(SSD1306_SWITCHCAPVCC); // UNCOMMENT FOR SPI DISPLAY

  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);  // UNCOMMENT FOR I2C DISPLAY

  // display PONG when code is first run
  display.clearDisplay();
  display.setCursor(19, 20);
  display.setTextColor(1);
  display.setTextSize(4);
  display.print("PONG");
  display.display();
  delay(2000);
  display.clearDisplay();
  display.fillScreen(0);
}

void loop() {
  // taking joystick reading
  jRead = analogRead(JOYSTICK);

  // moving pad
  if (jRead < 400 && padY > 0) {
    padY = padY - padSpeed;
  }
  if (jRead > 600 && padY < 64 - PADLEN) {
    padY = padY + padSpeed;
  }

  // bouncing ball off of walls
  if (i >= 128) {
    xdir = -xdir;
  }
  if (j <= 0 || j >= 64) {
    ydir = -ydir;
  }

  // bouncing ball off of pad
  if (i <= 1 && j >= padY && j <= padY + PADLEN) {
    xdir = random(3) + 1;  // randomize speed and direction of ball when bouncing off of pad
    score = score + 1;     // update score
  }

  // GAME OVER when ball collides with left wall
  else if (i <= 0) {
    delay(1000);
    display.clearDisplay();
    display.setCursor(10, 25);
    display.setTextColor(1);
    display.setTextSize(2);
    display.print("GAME OVER");
    display.setTextSize(1);
    display.print("                                                  Score: ");
    display.print(score);
    display.display();
    delay(2500);
    i = 64;
    j = 32;
    xdir = -xdir;
    score = 0;  // set score back to zero
  }
  i = i + xdir;
  j = j + ydir;
  Serial.println(padY);
  display.clearDisplay();
  display.drawPixel(i, j, 1);
  display.drawFastVLine(0, padY, PADLEN, 1);
  display.display();
}
