/*
 * led.h
 *
 *  Created on: Feb 22, 2020
 *      Author: mdiannna
 */

#ifndef LED_H_
#define LED_H_

// builtin pin is 13 - LED_BUILTIN
#define LED_PIN 2 // change
#define LED_ON 1
#define LED_OFF 0

void LED_Init();
int Is_LED_On();
void LED_On();
void LED_Off();



#endif /* LED_H_ */
