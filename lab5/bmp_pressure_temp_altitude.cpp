#include "bmp_pressure_temp_altitude.h"


/*
BMP180(resolution)

resolution:
BMP180_ULTRALOWPOWER - pressure oversampled 1 time  & power consumption 3μA
BMP180_STANDARD      - pressure oversampled 2 times & power consumption 5μA
BMP180_HIGHRES       - pressure oversampled 4 times & power consumption 7μA
BMP180_ULTRAHIGHRES  - pressure oversampled 8 times & power consumption 12μA, library default
*/
BMP180 myBMP(BMP180_ULTRAHIGHRES);


void InitBMPSensor() {
	while (myBMP.begin() != true)
	{
		Serial.println(F("Bosch BMP180 is not connected or fail to read calibration coefficients"));
		delay(5000);
	}

	Serial.println(F("Bosch BMP180 sensor is OK")); //(F()) saves string to flash & keeps dynamic memory free
}


// get temperature in celsius degrees
double GetTemperature() {
	return myBMP.getTemperature();
}

// get air pressure in Pa
double GetPressure() {
	return myBMP.getPressure();
}

// get sea level pressure by providing current altitude
double GetSeaLevelPressure() {
  double seaLevelPressure = myBMP.getSeaLevelPressure(ALTITUDE); 
	return seaLevelPressure;
}
