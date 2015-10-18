//#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>


int incomingByte = 0;
int redPin = 13;
int grePin = 12;
int yelPin = 11;

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

void setup() {

  lcd.begin(16,2);
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Hello");
  lcd.setCursor(0, 1);
  lcd.print("Row:");
  lcd.setCursor(5, 1);
  lcd.print("2");
    
  // Green
  pinMode(grePin, OUTPUT);

  // Yellow
  pinMode(yelPin, OUTPUT);

  // Red
  pinMode(redPin, OUTPUT);

  // Serial port (sets data rate to 9600 bps)
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) { incomingByte = Serial.read(); }
 
  if (incomingByte == 'f') {
    red();
  } else if (incomingByte == 'b') {
    yellow();
  } else if (incomingByte == 's') {
    green();
  } else { ledinit(); }
}

void green() {
  digitalWrite(grePin, HIGH);
  digitalWrite(yelPin, LOW);
  digitalWrite(redPin, LOW);  
}

void yellow() {
  digitalWrite(grePin, LOW);
  digitalWrite(yelPin, HIGH);
  digitalWrite(redPin, LOW);
}

void red() {
  digitalWrite(grePin, LOW);
  digitalWrite(yelPin, LOW);
  digitalWrite(redPin, HIGH);
}

void ledinit() {
  red();
  delay(100);
  yellow();
  delay(100);
  green();
  delay(100);
}



 
