#include "myi2c.h"


void InitI2C() {
	Wire.begin(); 
}

void SendI2C(int value) {
	Wire.beginTransmission(9); // transmit to device #9
	Wire.write(value);              // sends x 
	Wire.endTransmission();
}
