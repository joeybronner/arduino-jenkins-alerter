/*
 * Oter methods
 */

/* Switch ON green led */
void green() {
  ledOn(grePin);
  ledOff(redPin);
  ledOff(yelPin);  
}

/* Switch ON yeklow led */
void yellow() {
  ledOff(grePin);
  ledOn(yelPin);
  ledOff(redPin);
}

/* Switch ON red led */
void red() {
  ledOff(grePin);
  ledOff(yelPin);
  ledOn(redPin);
}

/* Switch ON all leds */
void all() {
  ledOn(grePin);
  ledOn(yelPin);
  ledOn(redPin);
}

/* Switch OFF all leds */
void noOne() {
  ledOff(grePin);
  ledOff(yelPin);
  ledOff(redPin);
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
  delay(200);
  yellow();
  delay(200);
  red();
  delay(200);
  noOne();
}

/*
 * Screen state for initialization.
 * Displays job & branch.
 */
void screenInitialization() {
  lcd.begin(16,2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(projectName);
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
    delay(75);
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
