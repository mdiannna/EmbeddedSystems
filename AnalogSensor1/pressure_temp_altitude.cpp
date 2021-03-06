/*
 * airPressure.cpp
 *
 *  Created on: Feb 26, 2020
 *      Author: mdiannna
 */




/*

This sketch shows how to use the SFE_BMP180 library to read the
Bosch BMP180 barometric pressure sensor.
https://www.sparkfun.com/products/11824

Like most pressure sensors, the BMP180 measures absolute pressure.
This is the actual ambient pressure seen by the device, which will
vary with both altitude and weather.

Before taking a pressure reading you must take a temperature reading.
This is done with startTemperature() and getTemperature().
The result is in degrees C.

Once you have a temperature reading, you can take a pressure reading.
This is done with startPressure() and getPressure().
The result is in millibar (mb) aka hectopascals (hPa).

If you'll be monitoring weather patterns, you will probably want to
remove the effects of altitude. This will produce readings that can
be compared to the published pressure readings from other locations.
To do this, use the sealevel() function. You will need to provide
the known altitude at which the pressure was measured.

If you want to measure altitude, you will need to know the pressure
at a baseline altitude. This can be average sealevel pressure, or
a previous pressure reading at your altitude, in which case
subsequent altitude readings will be + or - the initial baseline.
This is done with the altitude() function.

Hardware connections:

- (GND) to GND
+ (VDD) to 3.3V

(WARNING: do not connect + to 5V or the sensor will be damaged!)

You will also need to connect the I2C pins (SCL and SDA) to your
Arduino.


The SFE_BMP180 library uses floating-point equations developed by the
Weather Station Data Logger project: http://wmrx00.sourceforge.net/

Our example code uses the "beerware" license. You can do anything
you like with this code. No really, anything. If you find it useful,
buy me a beer someday.

*/


#include <Arduino.h>
#include <Wire.h>
#include "pressure_temp_altitude.h"

// Sparkfun BMP180 library
#include "SFE_BMP180.h"


SFE_BMP180 sensor;

//#define ALTITUDE 1655.0 // Altitude of SparkFun's HQ in Boulder, CO. in meters
#define ALTITUDE 130.0 // Altitude near Technical University of Moldova

void InitBMPSensor()
{
  // Initialize the sensor (it is important to get calibration values stored on the device).

  if (sensor.begin())
    Serial.println("BMP180 init success");
  else
  {
    // Oops, something went wrong, this is usually a connection problem,
    // see the comments at the top of this sketch for the proper connections.

    Serial.println("BMP180 init fail\n\n");
    while(1); // Pause forever.
  }
}



double SensorGetTemperature(){
	char status;
	double T;

	status = sensor.startTemperature();
	  if (status != 0)
	  {
	    // Wait for the measurement to complete:
	    delay(status);

	    // Retrieve the completed temperature measurement:
	    // Note that the measurement is stored in the variable T.
	    // Function returns 1 if successful, 0 if failure.

	    status = sensor.getTemperature(T);
	    if (status != 0)
	    {
	      // Print out the measurement:
	      Serial.print("temperature: ");
	      Serial.print(T,2);
	      Serial.print(" deg C, ");
	    }
	    else Serial.println("error retrieving temperature measurement\n");
	  }
	  else Serial.println("error starting temperature measurement\n");


	  return T;
}

double SensorGetPressure(double T) {
	char status;
	double P;

	status = sensor.startPressure(3);
	      if (status != 0)
	      {
	        // Wait for the measurement to complete:
	        delay(status);

	        // Retrieve the completed pressure measurement:
	        // Note that the measurement is stored in the variable P.
	        // Note also that the function requires the previous temperature measurement (T).
	        // (If temperature is stable, you can do one temperature measurement for a number of pressure measurements.)
	        // Function returns 1 if successful, 0 if failure.

	        status = sensor.getPressure(P,T);
	        if (status != 0)
	        {
//	          // Print out the measurement:
//	          Serial.print("absolute pressure: ");
//	          Serial.print(P,2);
//	          Serial.print(" mb, ");
//	          Serial.print(P*0.0295333727,2);
//	          Serial.println(" inHg");

	          // The pressure sensor returns abolute pressure, which varies with altitude.
	          // To remove the effects of altitude, use the sealevel function and your current altitude.
	          // This number is commonly used in weather reports.
	          // Parameters: P = absolute pressure in mb, ALTITUDE = current altitude in m.
	          // Result: p0 = sea-level compensated pressure in mb

//	          p0 = sensor.sealevel(P,ALTITUDE);
//	          Serial.print("relative (sea-level) pressure: ");
//	          Serial.print(p0,2);
//	          Serial.print(" mb, ");
//	          Serial.print(p0*0.0295333727,2);
//	          Serial.println(" inHg");

	          // On the other hand, if you want to determine your altitude from the pressure reading,
	          // use the altitude function along with a baseline pressure (sea-level or other).
	          // Parameters: P = absolute pressure in mb, p0 = baseline pressure in mb.
	          // Result: a = altitude in m.

	        }
	        else Serial.println("error retrieving pressure measurement\n");
	      }
	      else Serial.println("error starting pressure measurement\n");
	      return P;
}

double SensorGetRelativePressure(double P) {
	   // The pressure sensor returns abolute pressure, which varies with altitude.
		          // To remove the effects of altitude, use the sealevel function and your current altitude.
		          // This number is commonly used in weather reports.
		          // Parameters: P = absolute pressure in mb, ALTITUDE = current altitude in m.
		          // Result: p0 = sea-level compensated pressure in mb

	double p0;
		          p0 = sensor.sealevel(P,ALTITUDE);
//		          Serial.print("relative (sea-level) pressure: ");
//		          Serial.print(p0,2);
//		          Serial.print(" mb, ");
//		          Serial.print(p0*0.0295333727,2);
//		          Serial.println(" inHg");
		         return p0;
}

double SensorGetAltitude(double P, double p0){
	double a;
	   // The pressure sensor returns abolute pressure, which varies with altitude.
		          // To remove the effects of altitude, use the sealevel function and your current altitude.
		          // This number is commonly used in weather reports.
		          // Parameters: P = absolute pressure in mb, ALTITUDE = current altitude in m.
		          // Result: p0 = sea-level compensated pressure in mb

	a = sensor.altitude(P,p0);

	return a;
}


//void loopExample()
void TestSensorBMP()
{
  char status;
  double T,P,p0,a;

  // Loop here getting pressure readings every 10 seconds.

  // If you want sea-level-compensated pressure, as used in weather reports,
  // you will need to know the altitude at which your measurements are taken.
  // We're using a constant called ALTITUDE in this sketch:

  Serial.println();
  Serial.print("provided altitude: ");
  Serial.print(ALTITUDE,0);
  Serial.print(" meters, ");

  // If you want to measure altitude, and not pressure, you will instead need
  // to provide a known baseline pressure. This is shown at the end of the sketch.

  // You must first get a temperature measurement to perform a pressure reading.

  // Start a temperature measurement:
  // If request is successful, the number of ms to wait is returned.
  // If request is unsuccessful, 0 is returned.

  	  T = SensorGetTemperature();

      status = sensor.startPressure(3);
      if (status != 0)
      {
        // Wait for the measurement to complete:
        delay(status);

        // Retrieve the completed pressure measurement:
        // Note that the measurement is stored in the variable P.
        // Note also that the function requires the previous temperature measurement (T).
        // (If temperature is stable, you can do one temperature measurement for a number of pressure measurements.)
        // Function returns 1 if successful, 0 if failure.

        status = sensor.getPressure(P,T);
        if (status != 0)
        {
          // Print out the measurement:
          Serial.print("absolute pressure: ");
          Serial.print(P,2);
          Serial.print(" mb, ");
          Serial.print(P*0.0295333727,2);
          Serial.println(" inHg");

          // The pressure sensor returns abolute pressure, which varies with altitude.
          // To remove the effects of altitude, use the sealevel function and your current altitude.
          // This number is commonly used in weather reports.
          // Parameters: P = absolute pressure in mb, ALTITUDE = current altitude in m.
          // Result: p0 = sea-level compensated pressure in mb

          p0 = sensor.sealevel(P,ALTITUDE);
          Serial.print("relative (sea-level) pressure: ");
          Serial.print(p0,2);
          Serial.print(" mb, ");
          Serial.print(p0*0.0295333727,2);
          Serial.println(" inHg");

          // On the other hand, if you want to determine your altitude from the pressure reading,
          // use the altitude function along with a baseline pressure (sea-level or other).
          // Parameters: P = absolute pressure in mb, p0 = baseline pressure in mb.
          // Result: a = altitude in m.

          a = sensor.altitude(P,p0);
          Serial.print("computed altitude: ");
          Serial.print(a,0);
          Serial.print(" meters, ");
          Serial.print(a*3.28084,0);
          Serial.println(" feet");
        }
        else Serial.println("error retrieving pressure measurement\n");
      }
      else Serial.println("error starting pressure measurement\n");


  delay(5000);  // Pause for 5 seconds.
}
