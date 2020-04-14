
#ifndef PASSWORD_H_
#define PASSWORD_H_

extern char* password;
extern int passwordIndex;

void PasswordInit();
int PasswordIsCorrect(char * password);
void ResetPassword();

#endif
