#include <LiquidCrystal_I2C.h>
#include <Wire.h>

// Global variables
int incomingByte = 0;
int redPin = 13;
int yelPin = 12;
int grePin = 11;

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

// Screen structure
/* __________________
  | XXXXXXXXXXXXXXXX |
  | XXXXXXXXXXXXXXXX |
   __________________ 
*/

/*
 * Setup
 */
void setup() {
  // Screen & leds initialization
  screenInitialization();
  ledInitialization();

  // Listening on serial port (sets data rate to 9600 bps)
  Serial.begin(9600);
}

/*
 * Loop
 */
void loop() {

  if (Serial.available() > 0) { incomingByte = Serial.read(); }

  // TODO: Here, parse incomingByte using a specific char
  // [0] = status (f, b, s, u)
  // [1] = msg
  // [2] = ???
 
  if (incomingByte == 'f') {
    red();
    writeScreen(1, 0, "FAILURE", false);
  } else if (incomingByte == 'b') {
    yellow();
    writeScreen(1, 0, "BUILDING", false);
  } else if (incomingByte == 's') {
    green();
    writeScreen(1, 0, "SUCCESS", false);
  } else if (incomingByte == 'u') {
    yellow();
    writeScreen(1, 0, "UNSTABLE", false);
  } else { 
    screenWaiting();
    ledWaiting();
  }
}
