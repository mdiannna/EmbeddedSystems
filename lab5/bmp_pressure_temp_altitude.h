
#ifndef BMP_PRESSURE_TEMP_ALTITUDE_h
#define BMP_PRESSURE_TEMP_ALTITUDE_h

#include "BMP180.h"
#define ALTITUDE 130.0 // Altitude near Technical University of Moldova


void InitBMPSensor();
double GetTemperature();
double GetPressure();
double GetSeaLevelPressure();

#endif
