
#define LED_PIN 2
#define BUTTON_PIN 8

#define LED_OFF_STATE 0
#define LED_ON_STATE 0


struct State {
	unsigned long Out;
	unsigned long Time;
	unsigned long Next[2];
};

typedef const struct State STyp;

STyp FSM[2] = {
	{0,10, {LED_OFF_STATE, LED_ON_STATE}},
	{1,10, {LED_ON_STATE, LED_OFF_STATE}}
};

int FSM_State = LED_OFF_STATE;

void ButtonInit() {
	pinMode(BUTTON_PIN, INPUT);
}

void LEDInit() {
	pinMode(LED_PIN, OUTPUT);
}

void InitialStateInit() {
	FSM_State = LED_OFF_STATE;
}

void setup() {
	ButtonInit();
	LEDInit();
	InitialStateInit();
}


void loop() {
	int output = FSM[FSM_State].Out;
	digitalWrite(LED_PIN, output);

	delay(FSM[FSM_State].Time *10);

	int input = digitalRead(BUTTON_PIN);

	FSM_State = FSM[FSM_State].Next[input];
}
