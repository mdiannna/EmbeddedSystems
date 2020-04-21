//////////////////////////////////
// LCD
/////////////////////////////////
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <stdio.h>

void lcdOn();
void lcdOff();
void LcdInit();
void PutCharLCD(char c);

///////////////////////////////
// Password
////////////////////////////////

int PasswordIsCorrect(char * password);
char* ReadPassword();