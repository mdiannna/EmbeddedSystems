#include <Arduino.h>

/*  Arduino DC Motor Control - PWM | H-Bridge | L298N  -  Example 01

    by Dejan Nedelkovski, www.HowToMechatronics.com
*/

#define enA 9
#define in1 6
#define in2 7
#define button 4

int rotDirection = 0;
int pressed = false;
int cnt = 0;

void setup() {
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
 // pinMode(button, INPUT);
  // Set initial rotation direction
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA,0);
}

void loop() {
	if(cnt<500) {

		int motorSpeedA = 100;
		 analogWrite(enA, motorSpeedA);
		 delay(20);
	} else if(cnt <1000) {
		  digitalWrite(in2, LOW);
		  digitalWrite(in1, HIGH);

		int motorSpeedA = 100;
				 analogWrite(enA, motorSpeedA);
				 delay(20);

	}
	else {
		 analogWrite(enA, 0);
	}
	cnt++;

}
