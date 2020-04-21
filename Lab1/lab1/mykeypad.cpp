/////////////////////////////////////////
//Keypad
/////////////////////////////////////////
#include <Keypad.h>
#include "mykeypad.h"

const byte Rows= 4;
const byte Cols= 3;

// key map as on the key pad:
char keymap[Rows][Cols]=
{
	{'1', '2', '3'},
	{'4', '5', '6'},
	{'7', '8', '9'},
	{'*', '0', '#'}
};

byte rPins[Rows]= {3, 4, 5, 6}; //Rows 0 to 3
byte cPins[Cols]= {7,8,9}; //Columns 0 to 2
Keypad kpd = Keypad(makeKeymap(keymap), rPins, cPins, Rows, Cols);



///////////////////////////////
// Password
////////////////////////////////
char * CORRECT_PASSWORD = "1235";

int PasswordIsCorrect(char * password) {
  return strcmp(CORRECT_PASSWORD, password);
}

char* ReadPassword() {
  char * buf = (char *) malloc (32);
  int i = 0;
  char c = '+';
  while(c!='#') {
    c = '+';
    while(c=='+') {
      char keypressed = kpd.getKey();
      if (keypressed != NO_KEY) {
        c = keypressed;
        printf("%c", c);
        buf[i]= c;i++;
      }
    }
  }
  return buf;
}


char GetCharKeypad() {
	char c = '+';
	while(c=='+') {
		char keypressed = kpd.getKey();
		if (keypressed != NO_KEY)
		{
			c = keypressed;
			return c;
		}
	}
}
