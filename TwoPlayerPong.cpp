#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <Wire.h>


//OLED Display setup
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels


#define PADLEN_P1 18 // length of player 1 pad
int padY_P1 = 0; // y coordinate of top pixel of player 1 pad
#define padSpeed_P1 2// drift speed of player 1 pad

#define PADLEN_P2 18 // length of player 2 pad
int padY_P2 = 0; // y coordinate of top pixel of player 2 pad
#define padSpeed_P2 2 // drift speed of player 2 pad


#define WINNING_SCORE 5


#define PLAYER1_JOYSTICK A0 // joystick pin for p1
#define PLAYER2_JOYSTICK A3 // joystick pin for p2
int jRead_P1;
int jRead_P2;


//####################### UNCOMMENT IF I2C #############################
#define OLED_SCL A5
#define OLED_SDA A4
#define OLED_RESET     -1
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


// // ######################## UNCOMMENT IF SPI #############################
// #define OLED_MOSI   9
// #define OLED_CLK   10
// #define OLED_DC    11
// #define OLED_CS    12
// #define OLED_RESET 13
// Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
//   OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);


// coordinates and speed of ball
int xdir = 2; // speed in x
int ydir = 2; // speed in y
int i = 10; // x coordinate
int j = 15; // y coordinate


// player 1 score
int score1 = 0;
// player 2 score
int score2 = 0;

//###########################################################################
//###########################################################################

void setup() {
  Serial.begin(9600);

  // display.begin(SSD1306_SWITCHCAPVCC); // UNCOMMENT IF SPI
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS); // UNCOMMENT IF I2C

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
  display.clearDisplay();
  jRead_P1 = analogRead(PLAYER1_JOYSTICK);
  jRead_P2 = analogRead(PLAYER2_JOYSTICK);

  // moving pad for P1
  if (jRead_P1 < 400 && padY_P1 > 0) {
    padY_P1 = padY_P1 - padSpeed_P1;
  }
  if (jRead_P1 > 600 && padY_P1 < 64 - PADLEN_P1) {
    padY_P1 = padY_P1 + padSpeed_P1;
  }


  // moving pad for P2
  if (jRead_P2 < 400 && padY_P2 > 0) {
    padY_P2 = padY_P2 - padSpeed_P2;
  }
  if (jRead_P2 > 600 && padY_P2 < 64 - PADLEN_P2) {
    padY_P2 = padY_P2 + padSpeed_P2;
  }


  // bouncing ball off of walls 
  if (j <= 0 || j >= 64) {
    ydir = -ydir;
  }


  // bouncing ball off of player 1 pad
  if (i <= 1 && j >= padY_P1 && j <= padY_P1 + PADLEN_P1) {
    xdir = random(3) + 1; // randomize speed and direction of ball when bouncing off of pad
  }
  else if ( i <= 0 ) {
    delay(500);
    display.clearDisplay();
    score2 = score2 + 1;
    i = 90;
    j = 32;
    xdir = -1;
    displayScore(score1, score2);
  }


  // bouncing ball off of player 2 pad
  if (i >= 127 && j >= padY_P2 && j <= padY_P2 + PADLEN_P2) {
    xdir = random(3) + 1; // randomize speed and direction of ball when bouncing off of pad
    xdir = -xdir;
  }
  else if ( i >= 128 ) {
    delay(1000);
    display.clearDisplay();
    score1 = score1 + 1;
    i = 38;
    j = 32;
    xdir = 1;
    displayScore(score1, score2);
  }

  if ( score1 == WINNING_SCORE || score2 == WINNING_SCORE ){
    display.clearDisplay();
    display.setCursor(10, 20);
    display.setTextColor(1);
    display.setTextSize(2);
    display.println("GAME OVER");
    display.setTextSize(1);
    display.println("");
    if ( score1 == WINNING_SCORE ) {
      display.println("     Player 1 won");
    }
    else if ( score2 == WINNING_SCORE ) {
      display.println("     Player 2 won");
    }
    display.display();
    delay(2500);
    return 0;
  }

  i = i + xdir;
  j = j + ydir;
  // Serial.println(score1);
  display.clearDisplay();
  display.drawPixel(i, j, 1);
  display.drawFastVLine(0, padY_P1, PADLEN_P1, 1);
  display.drawFastVLine(127, padY_P2, PADLEN_P2, 1);
  display.display();
}

void displayScore(int x1, int x2) {
  display.clearDisplay();
  display.setCursor(27, 24);
  display.setTextColor(1);
  display.setTextSize(2);
  display.print(x1);
  display.setCursor(91, 24);
  display.print(x2);
  display.drawRect(0, 0, 128, 64, 1);
  display.drawFastVLine(64, 0, 64, 1);
  display.display();
  delay(2000);
}
