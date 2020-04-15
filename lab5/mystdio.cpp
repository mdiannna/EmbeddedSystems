#include <Arduino.h>
#include <stdio.h>
#include "lcd.h"
#include "mykeypad.h"


int MyPutChar( char c, FILE *t) {
	Serial.write( c );
	// PutCharLCD(c);
}

char MyGetChar( FILE *stream) {
	return GetCharKeypad();
}


void MystdioInit() {
	// Varianta 1
	fdevopen( &MyPutChar, 0);
	fdevopen( &MyGetChar, 1);
	// Varianta 2
  	// fdevopen( &MyPutCh, &MyGetCh);
}

// Varianta 2

// int MyPutCh(char ch, FILE *t) {
//   Serial.print(ch);
// }


// int MyGetCh(FILE *t) {
//   while(!Serial.available());
//   char ch = Serial.read();
//   return ch;
// }
