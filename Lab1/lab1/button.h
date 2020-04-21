
#ifndef BUTTON_H_
#define BUTTN_H_

//////////////////////////
// Button
/////////////////////////
//button.h
#define BUTTON_PIN 10
#define BUTTON_PRESSED 1
#define BUTTON_RELEASED 0

void ButtonInit();
int IsButtonPressed();
int IsButtonReleased();

#endif
