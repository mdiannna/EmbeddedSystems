#define NORTH_PIN         1
#define EAST_PIN          2
#define EAST_RED_PIN      3
#define EAST_YELLOW_PIN   4
#define EAST_GREEN_PIN    5
#define NORTH_RED_PIN     6
#define NORTH_YELLOW_PIN  7
#define NORTH_GREEN_PIN   8
#define goN    0   // 0b00
#define waitN  1   // 0b01
#define goE    2  // 0b00
#define waitE  3   // 0b01


struct State {
	unsigned long Out;
	unsigned long Time;
	unsigned long Next[4];
};


typedef const struct State STyp;

STyp FSM[4] = {
	{0b100001, 3000, {goN, waitN, goN,   waitN}},
	{0b100010, 500,  {goE, goE,   goE,   goE}},
	{0b001100, 3000, {goE, goE,   waitE, waitE}},
	{0b010100, 500,  {goN, goN,   goN,   goN}}
};

int FSM_State = goN;

void setup() {
	pinMode(NORTH_PIN, INPUT);
	pinMode(EAST_PIN, INPUT);

	pinMode(EAST_RED_PIN, INPUT);
	pinMode(EAST_YELLOW_PIN, INPUT);
	pinMode(EAST_GREEN_PIN, INPUT);

	pinMode(NORTH_RED_PIN, INPUT);
	pinMode(NORTH_YELLOW_PIN, INPUT);
	pinMode(NORTH_GREEN_PIN, INPUT);

	FSM_State = goN;
}

int GetInput(void) {
	int northButton = digitalRead(NORTH_PIN);
	int eastButton = digitalRead(EAST_PIN);
	if(northButton && eastButton) {
		return 0b11;
	} 
	//else
	if(northButton) {
		return 0b10;
	} 
	// else
	if(eastButton) {
		return 0b01;
	} 
	// else
	return 0b00;
}

void SetOutput(int out) {
	int ledState;
	
	ledState = (out & (1 << 5)) ? HIGH : LOW;
	digitalWrite(EAST_RED_PIN, ledState);

	ledState = (out & (1 << 4)) ? HIGH : LOW;
	digitalWrite(EAST_YELLOW_PIN, ledState);

	ledState = (out & (1 << 3)) ? HIGH : LOW;
	digitalWrite(EAST_GREEN_PIN, ledState);

	ledState = (out & (1 << 2)) ? HIGH : LOW;
	digitalWrite(NORTH_RED_PIN, ledState);

	ledState = (out & (1 << 1)) ? HIGH : LOW;
	digitalWrite(NORTH_YELLOW_PIN, ledState);

	ledState = (out & (1 << 0)) ? HIGH : LOW;
	digitalWrite(NORTH_GREEN_PIN, ledState);
}

void loop() {
	// 1. Output based on current state
	int output = FSM[FSM_State].Out;
	SetOutput(output);

	// 2. Wait for time relevant to state
	delay(FSM[FSM_State].Time * 10);

	// 3. Get input
	int input = GetInput();

	// 4. Change state based on input and current state
	FSM_State = FSM[FSM_State].Next[input];



}
