
#ifndef KEYPAD_H_
#define KEYPAD_H_

// const byte Rows= 4; 
#define Rows 4 
// const byte Cols= 3;
#define Cols 3



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


char GetCharKeypad();

#endif