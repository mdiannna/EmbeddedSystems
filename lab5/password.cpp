#include "password.h"
#include "mykeypad.h"
#include <stdlib.h>
#include <stdio.h>
#include <Arduino.h>

char * CORRECT_PASSWORD = "1234#";


int PasswordIsCorrect(char * pwd) {
  if(strcmp(CORRECT_PASSWORD, pwd)==0) {
  	return 1;
  }
  return 0;
}

void PasswordInit() {
	password = (char *) malloc (5*sizeof(char));
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
