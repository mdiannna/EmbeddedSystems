/*
 * mystdio.cpp
 *
 *  Created on: Feb 22, 2020
 *      Author: mdiannna
 */

#include <stdio.h>
#include <avr/io.h>
#include <Arduino.h>
#include "mystdio.h"

int MyPutChar( char c, FILE *t) {
    Serial.print( c );
    return 0;
}

int MyGetCh(FILE *t) {
  while(!Serial.available());
  char ch = Serial.read();
//  return ch;
  return &ch;
}


void SerialInit() {
  Serial.begin(9600);
  fdevopen( &MyPutChar, &MyGetCh);
  //fdevopen( MyPutChar, MyGetCh);
}

