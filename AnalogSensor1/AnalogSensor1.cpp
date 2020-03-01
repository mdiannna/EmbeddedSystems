#include <Arduino.h>
#include "mystdio.h"
#include "led.h"
#include "analoglibrary.h"
#include "lightsensor.h"
#include "pressure_temp_altitude.h"

#define R 10000 //ohm resistance value
#define Vin 5 // input voltage

void setup() {
	SerialInit();
	LightSensorInit();
	LED_Init();
	InitBMPSensor();

	printf("Initialization done\n");
}

void loop() {

	int lightLevel = ReadLightLevel();
	float Vout = ADCtoVoltage(lightLevel);
	int resistance = VoltageToResistance(R, Vin, Vout);

	printf("Light level: %d\n\r", lightLevel);
	printf("Resistance: %d\n\r", resistance);

	printf("Voltage: %.2f\n\r", Vout);
	Serial.println(Vout);

	float lux = ResistanceToLumen(resistance);
	printf("Light intensity(lumen) - physical parameter: %f\n\r", lux);
	Serial.print(lux);

	TestSensorBMP();

	delay(1000);
	LED_On();
	delay(1000);
	LED_Off();
	delay(1000);
}
