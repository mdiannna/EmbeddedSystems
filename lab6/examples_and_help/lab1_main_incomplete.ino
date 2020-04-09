  void setup() {
    LED_Init();
    ButtonInit();
    SerialInit();
    LcdInit();
    fdevopen( &MyPutChar, 0);
    fdevopen( &MyGetChar, 1);

    lcd.setCursor(0,1);
    printf("Hello!");
    delay(1000);
  }



  void loop() {
    Green_LED_Off();
    
    lcd.clear();
    lcd.setCursor(0,0);   
    printf("Type password #");

    lcd.setCursor(0,1);
    char * password = (char *) malloc(32);
    password = ReadPassword();

    Serial.print("Password:");
    Serial.write(password);

    lcd.clear();

    if(PasswordIsCorrect(password)==1) {
      lcd.setCursor(0,0);
      printf("Correct");
      lcd.setCursor(0,1);
      printf("password");
      Green_LED_On();
      Red_LED_Off();
      delay(800);

      lcd.setCursor(0,0); 
      printf("Press button");
      lcd.setCursor(0,1);
      printf("for light On/Off\n");
      delay(2000);

      while(!IsButtonPressed());

      if(Is_LED_On()) {
        lcd.clear();
        lcd.setCursor(0,0); 
        printf("LED off!\n" );
        LED_Off();
      } else {
        lcd.clear();
        lcd.setCursor(0,0); 
        printf("LED on!\n");
        LED_On();
      }

      while(!IsButtonReleased());

    } else {
      lcd.setCursor(0,0);
      printf("Wrong");
      lcd.setCursor(0,1);
      printf("password");
      Green_LED_Off();

  Red_LED_On();
    }

    delay(2000);
  }
