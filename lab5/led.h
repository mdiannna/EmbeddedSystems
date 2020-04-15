#ifndef LED_H_
#define LED_H_

// builtin pin is 13 - LED_BUILTIN
#define RED_LED_PIN 9
#define GREEN_LED_PIN 8
#define BLUE_LED_PIN 13
#define RED_LED_PASSWORD_PIN 14
#define GREEN_LED_PASSWORD_PIN 15


#define LED_ON 1
#define LED_OFF 0

// Blue led init
void LED_Init();
void LED_Init(int);
void LEDs_Init();


int Is_RED_LED_On();
int Is_GREEN_LED_On();
int Is_LED_On(); // equivalent to Is_Blue_LED_On()
int Is_BLUE_LED_On();
int Is_RED_LED_Password_On();
int Is_GREEN_LED_Password_On();

void Turn_LED_On(int led_pin);
void Turn_LED_Off(int led_pin);

// Functions for blue LED:
void LED_On();
void LED_Off();


#endif /* LED_H_ */
