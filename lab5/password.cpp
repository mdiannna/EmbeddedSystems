#include "password.h"
#include "mykeypad.h"
#include <stdlib.h>
#include <stdio.h>
#include <Arduino.h>

char * CORRECT_PASSWORD = "1235";

int PasswordIsCorrect(char * password) {
  return strcmp(CORRECT_PASSWORD, password);
}


//TODO: change to non-blocking
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
