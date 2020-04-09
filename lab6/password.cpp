#include "password.h"

char * CORRECT_PASSWORD = "1235";

int PasswordIsCorrect(char * password) {
  return strcmp(CORRECT_PASSWORD, password);
}

char* ReadPassword() {
  char * buf = (char *) malloc (32);
  int i = 0;

  char c = '+';
  while(c!='#') {
    c = '+';
    while(c=='+') {
      char keypressed = kpd.getKey();
      if (keypressed != NO_KEY) {    
        c = keypressed;
        printf("%c", c);
        buf[i]= c;
        i++;
      }   
    }

  }
  return buf;
}


