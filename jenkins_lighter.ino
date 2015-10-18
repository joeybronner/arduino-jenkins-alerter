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

/*
 * Oter methods
 */

void green() {
  ledOn(grePin);
  ledOff(redPin);
  ledOff(yelPin);  
}

void yellow() {
  ledOff(grePin);
  ledOn(yelPin);
  ledOff(redPin);
}

void red() {
  ledOff(grePin);
  ledOff(yelPin);
  ledOn(redPin);
}

/*
 * Swhitch ON a led.
 */
void ledOn(int pin) {
  digitalWrite(pin, HIGH);
}

/*
 * Switch OFF a led.
 */
void ledOff(int pin) {
  digitalWrite(pin, LOW);
}

/*
 * Led initialization.
 * Called on program launching if no signal (success, failure, building, etc...)
 * is received.
 */
void ledInitialization() {
  // Leds initialization
  pinMode(grePin, OUTPUT); // Green
  pinMode(yelPin, OUTPUT); // Yellow
  pinMode(redPin, OUTPUT); // Red
}

void ledWaiting() {
  green();
  delay(1000);
  yellow();
  delay(1000);
  red();
  delay(1000);
}

/*
 * Screen state for initialization.
 * Displays job & branch.
 */
void screenInitialization() {
  lcd.begin(16,2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("smartbi-orig/mas");
}

/*
 * Swrren state after initialization.
 * Waiting for a signal from jenkins
 */
 void screenWaiting() {
  // Print Wainting symbol
  for (int i=0 ; i<=16 ; i++) {
    lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.setCursor(i, 1);
    lcd.print(">>>");
    delay(100);
  }
 }

/*
 * Writes a message on the LiquidCrystal I2C.
 */
void writeScreen(int line, int startPosition, String msg, boolean clearScreen) {
  // Clear screen if needed
  if (clearScreen) {
    lcd.clear();
  }

  // Write message on screen
  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.setCursor(startPosition, line);
  lcd.print(msg);
} 
