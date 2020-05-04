

#include "led.h"
#include "button.h"

struct State {
	unsigned long Out;
	unsigned long Time;
	unsigned long Next[2];
};

typedef const struct State STyp;

STyp FSM[2] = {
	{0,50, {LED_OFF_STATE, LED_ON_STATE}},
	{1,50, {LED_ON_STATE, LED_OFF_STATE}}
};

int FSM_State = LED_OFF_STATE;


void InitialStateInit() {
	FSM_State = LED_OFF_STATE;
}


void setup() {
	InitialStateInit();
  LEDInit();
  ButtonInit();
}


void loop() {
	int output = FSM[FSM_State].Out;

	LEDSetState(output);

	delay(FSM[FSM_State].Time *10);
	int input = ReadButton();
  
	FSM_State = FSM[FSM_State].Next[input];
}
