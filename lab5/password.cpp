#include "password.h"
#include "mykeypad.h"
#include <stdlib.h>
#include <stdio.h>
#include <Arduino.h>

char * CORRECT_PASSWORD = "1234#";
char * password;
int passwordIndex;

int PasswordIsCorrect(char * password) {
  return strcmp(CORRECT_PASSWORD, password);
}

void PasswordInit() {
	password = (char *) malloc (32);
	passwordIndex = 0;
}


void ResetPassword() {
	// Serial.println("PASSWORD RESET");
	password = "";
	passwordIndex = 0;
}

//char* ReadPassword() {
//  char * buf = (char *) malloc (32);
//  int i = 0;
//
//  char c = '+';
//  while(c!='#') {
//    c = '+';
//    while(c=='+') {
//      char keypressed = kpd.getKey();
//      if (keypressed != NO_KEY) {    
//        c = keypressed;
//        printf("%c", c);
//        buf[i]= c;
//        i++;
//      }   
//    }
//
//  }
//  return buf;
//}
//
