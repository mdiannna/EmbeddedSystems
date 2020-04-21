///////////////////////////////
// Functions for stdio
////////////////////////////////
#include "mystdio.h"
#include "mykeypad.h"
#include "lcd.h"

int MyPutChar( char c, FILE *t) {
	Serial.write( c );
	PutCharLCD(c);
}

char MyGetChar( FILE *stream) {
	return GetCharKeypad();
}
