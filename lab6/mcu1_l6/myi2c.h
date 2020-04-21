#ifndef MYI2C_H_
#define MYI2C_H_

#include <Arduino.h>
#include <Wire.h>


void InitI2C();
void SendI2C(int value);

#endif