#include <Arduino.h>
#include "photoresistor.h"
#include "mystdio.h"
#include "led.h"
#include "analoglibrary.h"

void setup() {
	SerialInit();
	PhotoresistorInit();
	LED_Init();
	printf("Initialization done\n");
}

void loop() {

	int lightLevel = ReadLightLevel();
	float voltage = ADCtoVoltage(lightLevel);


	printf("Light level: %d\n\r", lightLevel);
	printf("Voltage: %.2f\n\r", voltage);
	Serial.println(voltage);

	delay(1000);
	LED_On();
	delay(1000);
	LED_Off();
	delay(1000);
}
