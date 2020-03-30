// serial plotter:
// https://randomnerdtutorials.com/arduino-serial-plotter-new-tool/

// #include "temperature.h"
// #include <Arduino.h>
// #include <Wire.h>
/*
  SFE_BMP180.h
  Bosch BMP180 pressure sensor library for the Arduino microcontroller
  Mike Grusin, SparkFun Electronics

  Uses floating-point equations from the Weather Station Data Logger project
  http://wmrx00.sourceforge.net/
  http://wmrx00.sourceforge.net/Arduino/BMP085-Calcs.pdf

  Forked from BMP085 library by M.Grusin

  version 1.0 2013/09/20 initial version
  Verison 1.1.2 - Updated for Arduino 1.6.4 5/2015

  Our example code uses the "beerware" license. You can do anything
  you like with this code. No really, anything. If you find it useful,
  buy me a (root) beer someday.
*/

#ifndef SFE_BMP180_h
#define SFE_BMP180_h

// #if defined(ARDUINO) && ARDUINO >= 100
// #include "Arduino.h"
// #else
// #include "WProgram.h"
// #endif

class SFE_BMP180
{
  public:
    SFE_BMP180(); // base type

    char begin();
      // call pressure.begin() to initialize BMP180 before use
      // returns 1 if success, 0 if failure (bad component or I2C bus shorted?)

    char startTemperature(void);
      // command BMP180 to start a temperature measurement
      // returns (number of ms to wait) for success, 0 for fail

    char getTemperature(double &T);
      // return temperature measurement from previous startTemperature command
      // places returned value in T variable (deg C)
      // returns 1 for success, 0 for fail

    char startPressure(char oversampling);
      // command BMP180 to start a pressure measurement
      // oversampling: 0 - 3 for oversampling value
      // returns (number of ms to wait) for success, 0 for fail

    char getPressure(double &P, double &T);
      // return absolute pressure measurement from previous startPressure command
      // note: requires previous temperature measurement in variable T
      // places returned value in P variable (mbar)
      // returns 1 for success, 0 for fail

    double sealevel(double P, double A);
      // convert absolute pressure to sea-level pressure (as used in weather data)
      // P: absolute pressure (mbar)
      // A: current altitude (meters)
      // returns sealevel pressure in mbar

    double altitude(double P, double P0);
      // convert absolute pressure to altitude (given baseline pressure; sea-level, runway, etc.)
      // P: absolute pressure (mbar)
      // P0: fixed baseline pressure (mbar)
      // returns signed altitude in meters

    char getError(void);
      // If any library command fails, you can retrieve an extended
      // error code using this command. Errors are from the wire library:
      // 0 = Success
      // 1 = Data too long to fit in transmit buffer
      // 2 = Received NACK on transmit of address
      // 3 = Received NACK on transmit of data
      // 4 = Other error

  private:

    char readInt(char address, int16_t &value);
      // read an signed int (16 bits) from a BMP180 register
      // address: BMP180 register address
      // value: external signed int for returned value (16 bits)
      // returns 1 for success, 0 for fail, with result in value

    char readUInt(char address, uint16_t &value);
      // read an unsigned int (16 bits) from a BMP180 register
      // address: BMP180 register address
      // value: external unsigned int for returned value (16 bits)
      // returns 1 for success, 0 for fail, with result in value

    char readBytes(unsigned char *values, char length);
      // read a number of bytes from a BMP180 register
      // values: array of char with register address in first location [0]
      // length: number of bytes to read back
      // returns 1 for success, 0 for fail, with read bytes in values[] array

    char writeBytes(unsigned char *values, char length);
      // write a number of bytes to a BMP180 register (and consecutive subsequent registers)
      // values: array of char with register address in first location [0]
      // length: number of bytes to write
      // returns 1 for success, 0 for fail

    int16_t AC1,AC2,AC3,VB1,VB2,MB,MC,MD;
    uint16_t AC4,AC5,AC6;
    double c5,c6,mc,md,x0,x1,x2,y0,y1,y2,p0,p1,p2;
    char _error;
};

#define BMP180_ADDR 0x77 // 7-bit address

#define BMP180_REG_CONTROL 0xF4
#define BMP180_REG_RESULT 0xF6

#define BMP180_COMMAND_TEMPERATURE 0x2E
#define BMP180_COMMAND_PRESSURE0 0x34
#define BMP180_COMMAND_PRESSURE1 0x74
#define BMP180_COMMAND_PRESSURE2 0xB4
#define BMP180_COMMAND_PRESSURE3 0xF4

#endif

/*
  SFE_BMP180.cpp
  Bosch BMP180 pressure sensor library for the Arduino microcontroller
  Mike Grusin, SparkFun Electronics

  Uses floating-point equations from the Weather Station Data Logger project
  http://wmrx00.sourceforge.net/
  http://wmrx00.sourceforge.net/Arduino/BMP085-Calcs.pdf

  Forked from BMP085 library by M.Grusin

  version 1.0 2013/09/20 initial version
  Verison 1.1.2 - Updated for Arduino 1.6.4 5/2015

  Our example code uses the "beerware" license. You can do anything
  you like with this code. No really, anything. If you find it useful,
  buy me a (root) beer someday.
*/

// #include "SFE_BMP180.h"
// #include <Arduino.h>
// #include <Wire.h>
#include <stdio.h>
#include <math.h>


SFE_BMP180::SFE_BMP180()
// Base library type
{
}


char SFE_BMP180::begin()
// Initialize library for subsequent pressure measurements
{
  double c3,c4,b1;

  // Start up the Arduino's "wire" (I2C) library:

  Wire.begin();

  // The BMP180 includes factory calibration data stored on the device.
  // Each device has different numbers, these must be retrieved and
  // used in the calculations when taking pressure measurements.

  // Retrieve calibration data from device:

  if (readInt(0xAA,AC1) &&
    readInt(0xAC,AC2) &&
    readInt(0xAE,AC3) &&
    readUInt(0xB0,AC4) &&
    readUInt(0xB2,AC5) &&
    readUInt(0xB4,AC6) &&
    readInt(0xB6,VB1) &&
    readInt(0xB8,VB2) &&
    readInt(0xBA,MB) &&
    readInt(0xBC,MC) &&
    readInt(0xBE,MD))
  {

    // All reads completed successfully!

    // If you need to check your math using known numbers,
    // you can uncomment one of these examples.
    // (The correct results are commented in the below functions.)

    // Example from Bosch datasheet
    // AC1 = 408; AC2 = -72; AC3 = -14383; AC4 = 32741; AC5 = 32757; AC6 = 23153;
    // B1 = 6190; B2 = 4; MB = -32768; MC = -8711; MD = 2868;

    // Example from http://wmrx00.sourceforge.net/Arduino/BMP180-Calcs.pdf
    // AC1 = 7911; AC2 = -934; AC3 = -14306; AC4 = 31567; AC5 = 25671; AC6 = 18974;
    // VB1 = 5498; VB2 = 46; MB = -32768; MC = -11075; MD = 2432;

    /*
    Serial.print("AC1: "); Serial.println(AC1);
    Serial.print("AC2: "); Serial.println(AC2);
    Serial.print("AC3: "); Serial.println(AC3);
    Serial.print("AC4: "); Serial.println(AC4);
    Serial.print("AC5: "); Serial.println(AC5);
    Serial.print("AC6: "); Serial.println(AC6);
    Serial.print("VB1: "); Serial.println(VB1);
    Serial.print("VB2: "); Serial.println(VB2);
    Serial.print("MB: "); Serial.println(MB);
    Serial.print("MC: "); Serial.println(MC);
    Serial.print("MD: "); Serial.println(MD);
    */

    // Compute floating-point polynominals:

    c3 = 160.0 * pow(2,-15) * AC3;
    c4 = pow(10,-3) * pow(2,-15) * AC4;
    b1 = pow(160,2) * pow(2,-30) * VB1;
    c5 = (pow(2,-15) / 160) * AC5;
    c6 = AC6;
    mc = (pow(2,11) / pow(160,2)) * MC;
    md = MD / 160.0;
    x0 = AC1;
    x1 = 160.0 * pow(2,-13) * AC2;
    x2 = pow(160,2) * pow(2,-25) * VB2;
    y0 = c4 * pow(2,15);
    y1 = c4 * c3;
    y2 = c4 * b1;
    p0 = (3791.0 - 8.0) / 1600.0;
    p1 = 1.0 - 7357.0 * pow(2,-20);
    p2 = 3038.0 * 100.0 * pow(2,-36);

    /*
    Serial.println();
    Serial.print("c3: "); Serial.println(c3);
    Serial.print("c4: "); Serial.println(c4);
    Serial.print("c5: "); Serial.println(c5);
    Serial.print("c6: "); Serial.println(c6);
    Serial.print("b1: "); Serial.println(b1);
    Serial.print("mc: "); Serial.println(mc);
    Serial.print("md: "); Serial.println(md);
    Serial.print("x0: "); Serial.println(x0);
    Serial.print("x1: "); Serial.println(x1);
    Serial.print("x2: "); Serial.println(x2);
    Serial.print("y0: "); Serial.println(y0);
    Serial.print("y1: "); Serial.println(y1);
    Serial.print("y2: "); Serial.println(y2);
    Serial.print("p0: "); Serial.println(p0);
    Serial.print("p1: "); Serial.println(p1);
    Serial.print("p2: "); Serial.println(p2);
    */

    // Success!
    return(1);
  }
  else
  {
    // Error reading calibration data; bad component or connection?
    return(0);
  }
}


char SFE_BMP180::readInt(char address, int16_t &value)
// Read a signed integer (two bytes) from device
// address: register to start reading (plus subsequent register)
// value: external variable to store data (function modifies value)
{
  unsigned char data[2];

  data[0] = address;
  if (readBytes(data,2))
  {
    value = (int16_t)((data[0]<<8)|data[1]);
    //if (*value & 0x8000) *value |= 0xFFFF0000; // sign extend if negative
    return(1);
  }
  value = 0;
  return(0);
}


char SFE_BMP180::readUInt(char address, uint16_t &value)
// Read an unsigned integer (two bytes) from device
// address: register to start reading (plus subsequent register)
// value: external variable to store data (function modifies value)
{
  unsigned char data[2];

  data[0] = address;
  if (readBytes(data,2))
  {
    value = (((uint16_t)data[0]<<8)|(uint16_t)data[1]);
    return(1);
  }
  value = 0;
  return(0);
}


char SFE_BMP180::readBytes(unsigned char *values, char length)
// Read an array of bytes from device
// values: external array to hold data. Put starting register in values[0].
// length: number of bytes to read
{
  char x;

  Wire.beginTransmission(BMP180_ADDR);
  Wire.write(values[0]);
  _error = Wire.endTransmission();
  if (_error == 0)
  {
    Wire.requestFrom(BMP180_ADDR,length);
    while(Wire.available() != length) ; // wait until bytes are ready
    for(x=0;x<length;x++)
    {
      values[x] = Wire.read();
    }
    return(1);
  }
  return(0);
}


char SFE_BMP180::writeBytes(unsigned char *values, char length)
// Write an array of bytes to device
// values: external array of data to write. Put starting register in values[0].
// length: number of bytes to write
{
  char x;

  Wire.beginTransmission(BMP180_ADDR);
  Wire.write(values,length);
  _error = Wire.endTransmission();
  if (_error == 0)
    return(1);
  else
    return(0);
}


char SFE_BMP180::startTemperature(void)
// Begin a temperature reading.
// Will return delay in ms to wait, or 0 if I2C error
{
  unsigned char data[2], result;

  data[0] = BMP180_REG_CONTROL;
  data[1] = BMP180_COMMAND_TEMPERATURE;
  result = writeBytes(data, 2);
  if (result) // good write?
    return(5); // return the delay in ms (rounded up) to wait before retrieving data
  else
    return(0); // or return 0 if there was a problem communicating with the BMP
}


char SFE_BMP180::getTemperature(double &T)
// Retrieve a previously-started temperature reading.
// Requires begin() to be called once prior to retrieve calibration parameters.
// Requires startTemperature() to have been called prior and sufficient time elapsed.
// T: external variable to hold result.
// Returns 1 if successful, 0 if I2C error.
{
  unsigned char data[2];
  char result;
  double tu, a;

  data[0] = BMP180_REG_RESULT;

  result = readBytes(data, 2);
  if (result) // good read, calculate temperature
  {
    tu = (data[0] * 256.0) + data[1];

    //example from Bosch datasheet
    //tu = 27898;

    //example from http://wmrx00.sourceforge.net/Arduino/BMP085-Calcs.pdf
    //tu = 0x69EC;

    a = c5 * (tu - c6);
    T = a + (mc / (a + md));

    /*
    Serial.println();
    Serial.print("tu: "); Serial.println(tu);
    Serial.print("a: "); Serial.println(a);
    Serial.print("T: "); Serial.println(*T);
    */
  }
  return(result);
}


char SFE_BMP180::startPressure(char oversampling)
// Begin a pressure reading.
// Oversampling: 0 to 3, higher numbers are slower, higher-res outputs.
// Will return delay in ms to wait, or 0 if I2C error.
{
  unsigned char data[2], result, delay;

  data[0] = BMP180_REG_CONTROL;

  switch (oversampling)
  {
    case 0:
      data[1] = BMP180_COMMAND_PRESSURE0;
      delay = 5;
    break;
    case 1:
      data[1] = BMP180_COMMAND_PRESSURE1;
      delay = 8;
    break;
    case 2:
      data[1] = BMP180_COMMAND_PRESSURE2;
      delay = 14;
    break;
    case 3:
      data[1] = BMP180_COMMAND_PRESSURE3;
      delay = 26;
    break;
    default:
      data[1] = BMP180_COMMAND_PRESSURE0;
      delay = 5;
    break;
  }
  result = writeBytes(data, 2);
  if (result) // good write?
    return(delay); // return the delay in ms (rounded up) to wait before retrieving data
  else
    return(0); // or return 0 if there was a problem communicating with the BMP
}


char SFE_BMP180::getPressure(double &P, double &T)
// Retrieve a previously started pressure reading, calculate abolute pressure in mbars.
// Requires begin() to be called once prior to retrieve calibration parameters.
// Requires startPressure() to have been called prior and sufficient time elapsed.
// Requires recent temperature reading to accurately calculate pressure.

// P: external variable to hold pressure.
// T: previously-calculated temperature.
// Returns 1 for success, 0 for I2C error.

// Note that calculated pressure value is absolute mbars, to compensate for altitude call sealevel().
{
  unsigned char data[3];
  char result;
  double pu,s,x,y,z;

  data[0] = BMP180_REG_RESULT;

  result = readBytes(data, 3);
  if (result) // good read, calculate pressure
  {
    pu = (data[0] * 256.0) + data[1] + (data[2]/256.0);

    //example from Bosch datasheet
    //pu = 23843;

    //example from http://wmrx00.sourceforge.net/Arduino/BMP085-Calcs.pdf, pu = 0x982FC0;
    //pu = (0x98 * 256.0) + 0x2F + (0xC0/256.0);

    s = T - 25.0;
    x = (x2 * pow(s,2)) + (x1 * s) + x0;
    y = (y2 * pow(s,2)) + (y1 * s) + y0;
    z = (pu - x) / y;
    P = (p2 * pow(z,2)) + (p1 * z) + p0;

    /*
    Serial.println();
    Serial.print("pu: "); Serial.println(pu);
    Serial.print("T: "); Serial.println(*T);
    Serial.print("s: "); Serial.println(s);
    Serial.print("x: "); Serial.println(x);
    Serial.print("y: "); Serial.println(y);
    Serial.print("z: "); Serial.println(z);
    Serial.print("P: "); Serial.println(*P);
    */
  }
  return(result);
}


double SFE_BMP180::sealevel(double P, double A)
// Given a pressure P (mb) taken at a specific altitude (meters),
// return the equivalent pressure (mb) at sea level.
// This produces pressure readings that can be used for weather measurements.
{
  return(P/pow(1-(A/44330.0),5.255));
}


double SFE_BMP180::altitude(double P, double P0)
// Given a pressure measurement P (mb) and the pressure at a baseline P0 (mb),
// return altitude (meters) above baseline.
{
  return(44330.0*(1-pow(P/P0,1/5.255)));
}


char SFE_BMP180::getError(void)
  // If any library command fails, you can retrieve an extended
  // error code using this command. Errors are from the wire library:
  // 0 = Success
  // 1 = Data too long to fit in transmit buffer
  // 2 = Received NACK on transmit of address
  // 3 = Received NACK on transmit of data
  // 4 = Other error
{
  return(_error);
}

// Sparkfun BMP180 library
// #include "SFE_BMP180.h"


SFE_BMP180 sensor;

void InitTemperatureSensor()
{
  if (sensor.begin())
    Serial.println("Temperature sensor init success");
  else
  {
    Serial.println("Temperature sensr PMB180 init fail\n\n");
    while(1); // Pause forever.
  }
}


double GetTemperature(){
  char status;
  double T;

  status = sensor.startTemperature();
    if (status != 0)
    {
      // Wait for the measurement to complete:
      delay(status);

      // Retrieve the completed temperature measurement:
      // The measurement is stored in the variable T.
      // Function returns 1 if successful, 0 if failure.

      status = sensor.getTemperature(T);
      if (status != 0)
      {
        // Print out the measurement:
        // Serial.print("temperature: ");
        // Serial.print(T,2);
        // Serial.print(" deg C, ");
      }
      // TODO: printf?
      else Serial.println("error retrieving temperature measurement\n");
    }
    else Serial.println("error starting temperature measurement\n");

    return T;
}





// builtin pin is 13 - LED_BUILTIN
#define RED_LED_PIN 10
#define GREEN_LED_PIN 11

#define LED_ON 1
#define LED_OFF 0

void LEDs_Init();

int Is_RED_LED_On();
int Is_GREEN_LED_On();

void Turn_LED_On(int led_pin);
void Turn_LED_Off(int led_pin);


void ConditionerInit();
void TurnConditionerOn();
void TurnConditionerOff();
int IsConditionerTurnedOn();
int IsConditionerTurnedOff();


void ConditionerInit() {
  LEDs_Init();
}
void TurnConditionerOn() {
  Turn_LED_Off(GREEN_LED_PIN);
  Turn_LED_On(RED_LED_PIN);
}

void TurnConditionerOff() {
  Turn_LED_Off(RED_LED_PIN);
  Turn_LED_On(GREEN_LED_PIN);
}


int IsConditionerTurnedOn() {
  if(Is_RED_LED_On()==1 && Is_GREEN_LED_On()==0) {
    return 1;
  }
  return 0;
}

int IsConditionerTurnedOff() {
  if(Is_RED_LED_On()==0) {
    return 1;
  }
  return 0;
}



void LEDs_Init() {
  pinMode(GREEN_LED_PIN, OUTPUT);//Change to output my pins
  pinMode(RED_LED_PIN, OUTPUT);
  digitalWrite(GREEN_LED_PIN,LED_OFF);//Turn off LED
  digitalWrite(RED_LED_PIN,LED_OFF);//Turn off LED
}

int Is_RED_LED_On() {
  int LEDState = digitalRead(RED_LED_PIN);
  if(LEDState==LED_ON) {
    return 1;
  }
//else
  return 0;
}

int Is_GREEN_LED_On() {
  int LEDState = digitalRead(GREEN_LED_PIN);
  if(LEDState==LED_ON) {
    return 1;
  }
//else
  return 0;
}

void Turn_LED_On(int led_pin) {
  digitalWrite(led_pin,LED_ON);
}

void Turn_LED_Off(int led_pin) {
  digitalWrite(led_pin,LED_OFF);
}


#define TIME_INTERVAL_MS 2000 //Read sensor each 2 seconds
#define MAX_TEMP 26
#define MIN_TEMP 24

long previousMillis = 0;


void SerialInit() {
  Serial.begin(9600);
}

unsigned long CompareTimeInterval(unsigned long currentMillis, unsigned long previousMillis) {
  return currentMillis - previousMillis;
}

int TimeIntervalElapsed(unsigned long currentMillis, unsigned long previousMillis) {
  int interval = CompareTimeInterval(currentMillis, previousMillis);
  if(interval > TIME_INTERVAL_MS) {
    return 1;
  }
  return 0;
}

int TemperatureExceedsMaxTemp(double t) {
  if(t>=MAX_TEMP) {
    return 1;
  }
  return 0;
}

int TemperatureBelowMinTemp(double t) {
  if(t<=MIN_TEMP) {
    return 1;
  }
  return 0;
}


void setup() {
  SerialInit();
  InitTemperatureSensor();
  ConditionerInit();
  Serial.println("Init complete");
}


void loop()
{

  double t = 0.0;

  unsigned long currentMillis = millis(); //time elapsed

  if(TimeIntervalElapsed(currentMillis, previousMillis))
  {
    previousMillis = currentMillis; //"Last time is now"

    t = GetTemperature();

    // Open serial plotter
    Serial.println(t);

    if(TemperatureExceedsMaxTemp(t) && IsConditionerTurnedOff())//if temperature above of 25 degrees
    {
      TurnConditionerOn();
    }
    else if(TemperatureBelowMinTemp(t)&&IsConditionerTurnedOn())//if temperature is under 23 degrees
    {
      TurnConditionerOff();
    }

  }
}
