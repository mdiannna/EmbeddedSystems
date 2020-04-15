
#include <Wire.h>
#include <stdio.h>
#include <Arduino.h>
#include "lcd.h"
#include <LiquidCrystal_I2C.h>

//initialize the liquid crystal library
//the first parameter is the I2C address
//the second parameter is how many rows are on your screen
//the third parameter is how many columns are on your screen

// For real hardware:
LiquidCrystal_I2C lcd(0x27, 16, 2);

void lcdOn() {
  lcd.backlight();
}

void lcdOff() {
  lcd.noBacklight();
}


void LcdInit() {
  //initialize lcd screen
  lcd.init();
  // turn on the screen
  lcdOn();
}

void PutCharLCD(char c) {
  lcd.print(c);
}

void WriteLCD(char * s) {
	lcd.print(s);
}


void WriteLCD(int s) {
	lcd.print(s);
}


void WriteLCD(float s) {
	lcd.print(s);
}

void LCD_SetCursor(int i, int j) {
	lcd.setCursor(i,j);
}