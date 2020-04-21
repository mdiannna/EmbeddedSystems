#include <stdio.h>
#include <Arduino.h>

int MyPutCh(char ch, FILE *t) {
	Serial.print(ch);
}

int MyGetCh(FILE *t) {
	while(!Serial.available());
	char ch = Serial.read();
	return ch;
}

void SerialInit() {
	Serial.begin(9600);
	fdevopen( &MyPutCh, &MyGetCh);
}

void setup() {
	SerialInit();
}

void loop() {
	char * text = (char *) malloc (64); // 8 chars - sizeof char = 8 bits
	printf("Type something\n");
	scanf("%s", text);
	printf("You typed:%s\n", text);
	int number;
	printf("Type integer\n");
	scanf("%d", &number);
	printf("You typed:%d\n", number);
	delay(500);
}