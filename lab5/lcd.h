
#ifndef LCD_H_
#define LCD_H_
#include <Wire.h> 
void lcdOn();
void lcdOff();
void LcdInit();
void PutCharLCD(char);
void WriteLCD(char *);
void WriteLCD(int);
void WriteLCD(float);
void LCD_SetCursor(int i, int j);
#endif
