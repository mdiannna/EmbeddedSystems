#ifndef LED_H_
#define LED_H_

// builtin pin is 13 - LED_BUILTIN
#define RED_LED_PIN 2
#define GREEN_LED_PIN 3

#define LED_ON 1
#define LED_OFF 0

void LEDs_Init();

int Is_RED_LED_On();
int Is_GREEN_LED_On();

void Turn_LED_On(int led_pin);
void Turn_LED_Off(int led_pin);


#endif /* LED_H_ */
