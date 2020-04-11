#include "hello.h"

#define RED_LED_PIN 9
#define GREEN_LED_PIN 8
#define BLUE_LED_PIN 13


// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(BLUE_LED_PIN, OUTPUT);
  HelloInit();
}

void LED_On(int pin) {
  digitalWrite(pin, HIGH);   // turn the LED on (HIGH is the voltage level)
}

void LED_Off(int pin) {
  digitalWrite(pin, LOW);    // turn the LED off by making the voltage LOW
}

// the loop function runs over and over again forever
void loop() {
  Hello();
  LED_On( RED_LED_PIN);
  LED_On(GREEN_LED_PIN);
  LED_On(BLUE_LED_PIN);
  delay(1000);                       // wait for a second
  LED_Off( RED_LED_PIN);
  LED_Off(GREEN_LED_PIN);
  LED_Off(BLUE_LED_PIN);
  delay(1000);                       // wait for a second
}
