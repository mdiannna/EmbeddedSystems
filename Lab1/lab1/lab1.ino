#include "button.h"
#include "led.h"
#include "mykeypad.h"

//LCD
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <stdio.h>
/////////////////////////////////////////
// Serial init
/////////////////////////////////////////
void SerialInit() {
Serial.begin(9600); // initializing serail monitor
}

//////
//MYSTDIO
///
int MyPutChar( char c, FILE *t) {
  Serial.write( c );
  PutCharLCD(c);
}

char MyGetChar( FILE *stream) {
  return GetCharKeypad();
}

//initialize the liquid crystal library
//the first parameter is the I2C address
//the second parameter is how many rows are on your screen
//the third parameter is how many columns are on your screen
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
// turn on the screenlcdOn();
}

void PutCharLCD(char c) {
  lcd.print(c);
}


/////////////////////////////
// the setup function runs once when you press reset or power the board
void setup() {
	LED_Init();ButtonInit();
	SerialInit();
	LcdInit();
	fdevopen( &MyPutChar, 0);
	fdevopen( &MyGetChar, 1);
	lcd.setCursor(0,1);
	printf("Hello!");
	delay(1000);
}

// the loop function runs over and over again forever
void loop() {
	Green_LED_Off();
	lcd.clear();
	lcd.setCursor(0,0);
	printf("Type password #");
	lcd.setCursor(0,1);
	char * password = (char *) malloc(32);
	password = ReadPassword();
	Serial.print("Password:");
	Serial.write(password);

	lcd.clear();

	if(PasswordIsCorrect(password)==1) {
		lcd.setCursor(0,0);
		printf("Correct");
		lcd.setCursor(0,1);
		printf("password");
		Green_LED_On();
		Red_LED_Off();
		delay(800);
		lcd.setCursor(0,0);
		printf("Press button");
		lcd.setCursor(0,1);
		printf("for light On/Off\n");
		delay(2000);
		while(!IsButtonPressed());
		if(Is_LED_On()) {
			lcd.clear();
			lcd.setCursor(0,0);
			printf("LED off!\n" );
			LED_Off();
		} else {
			lcd.clear();
			lcd.setCursor(0,0);
			printf("LED on!\n");
			LED_On();
		}
		while(!IsButtonReleased());
	} else {
		lcd.setCursor(0,0);
		printf("Wrong");
		lcd.setCursor(0,1);
		printf("password");
		Green_LED_Off();
		Red_LED_On();
	}
	delay(2000);
}
