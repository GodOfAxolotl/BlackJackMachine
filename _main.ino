void setup() {
  Serial.begin(9600);
  Wire.begin();
  lcd.init();
  lcd.backlight();
  bcklght = true;
  pinMode(buzzerPin, OUTPUT);
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);
  pinMode(readerPin, INPUT_PULLUP);
  RTC.begin();
  dht.begin();
  //RTC.adjust(DateTime(F(__DATE__), F(__TIME__)));

  delay(200);
  bootup();
}



void loop() {

  key = readButtonInput();

  Serial.println(key);

  if (key == '*' && gameStarted) {
    auditiveFeedback();
    lcd.noCursor();
    lcd.clear();
    lcd.setCursor(3, 1);
    lcd.print("-- Main Menu --");
    delay(1500);
    lcd.clear();
    gameStarted = false;

    if (showBootup) {
      startAnimationNotExecuted = true;
    }

    firstValueSettingNotExecuted = true;

    menuPos = 0;
    for ( int i = 0; i < sizeof(option); i++) {
      option[i] = 0;
    }
  }

  if (!gameStarted && b) {
    switch (key) {
      case '*':
        break;
      case 'A':
        auditiveFeedback();
        b = false;
        if (menuPos + 1 < menuOptions) {
          menuPos++;
          lcd.clear();
        } else {
          menuPos = 0;
          lcd.clear();
        }
        break;
      case 'B':
        auditiveFeedback();
        b = false;
        if (menuPos > 0) {
          menuPos--;
          lcd.clear();
        } else {
          menuPos = menuOptions - 1;
          lcd.clear();
        }
        break;
      case '#':
        auditiveFeedback();
        key = ' ';
        b = false;
        lcd.clear();
        gameStarted = true;
        option[menuPos] = true;
        break;
      case 'D':
        auditiveFeedback();
        b = false;
        if (bcklght) {
          lcd.noBacklight();
        } else {
          lcd.backlight();
        }
        bcklght = !bcklght;
        break;
    }
  } else if (!b && key == ' ') {
    b = true;
  }

  if (gameStarted) {
    if (option[0]) {
      blackJack();
    } else if (option[1]) {
      slotMachine();
    } else if (option[2]) {
      rouletteGame();
    } else if (option[3]) {
      poker();
    } else if (option[4]) {
      highorLow();
    } else if (option[5]) {
      oclock();
    } else if (option[6]) {
      options();
    }
  } else {
    DisplayTime();
    lcd.setCursor(5, 1);
    lcd.print(menuBand[menuPos]);
    lcd.setCursor(5, 2);
    lcd.print("<- B # A ->");
  }
}

//-------------------------------------------------------------------------------


char readButtonInput() {

  long value = 0;

  value = analogRead(readerPin);


  Serial.println(value);
  // delay(100);
  if (value <= 180 && value >= 0) {
    return '*';
  } else if (value <= 320 && value >= 190) {
    return 'B';
  } else if (value <= 420 && value >= 321) {
    return '#';
  } else if (value <= 510 && value >= 421) {
    return 'A';
  } else if (value <= 600 && value >= 511) {
    return 'D';
  }

  return ' ';
}

void winSound() {
  tone(9, 987.87);
  delay(100);
  noTone(9);
  tone(9, 1318.51);
  delay(120);
  noTone(9);
  playedSound = true;
}

void looseSound() {
  tone(9, 1318.51);
  delay(100);
  noTone(9);
  tone(9, 987.87);
  delay(120);
  noTone(9);
}

//-------------------------------------------------------------------------------

void bootup() {
  lcd.setCursor(2, 1);
  lcd.print("-- MiniCasino --");
  lcd.setCursor(7, 2);
  lcd.print("SENOS");
  delay(300);
  tone(9, 659);
  delay(120);
  tone(9, 880);
  delay(240);
  noTone(9);
  delay(1700);
  lcd.clear();
  lcd.setCursor(3, 1);
  lcd.print("Choose a game!");
  delay(2000);
  lcd.clear();
  bootupNotDone = false;
  return;
}

//------------------------------------------------------------------------------------

void options() {

  lcd.setCursor(2, 0);
  lcd.print("Tutorial: ");
  if (showBootup) {
    lcd.print(" on");
  } else {
    lcd.print(" off");
  }

  lcd.setCursor(2, 1);
  lcd.print("Backlit:  ");
  if (bcklght) {
    lcd.print(" off");
  } else {
    lcd.print(" on");
  }

  lcd.setCursor(2, 2);
  lcd.print("Temp:    ");
  if (showTmp) {
    lcd.print(" on");
  } else {
    lcd.print(" off");
  }

  if (b) {
    switch (key) {
      case 'B':
        b = false;
        auditiveFeedback();
        showBootup = !showBootup;
        startAnimationNotExecuted = false;
        lcd.clear();

        break;
      case '#':
        b = false;
        auditiveFeedback();
        bcklght = !bcklght;
        if (bcklght) {
          lcd.noBacklight();
        } else {
          lcd.backlight();
        }
        lcd.clear();


        break;
      case 'A':
        b = false;
        auditiveFeedback();
        showTmp = !showTmp;
        lcd.clear();


        break;
      case 'D':
        b = false;
        auditiveFeedback();
        lcd.clear();


    }
  } else if (key == ' ') {
    b = true;
    delay(10);

  }
}
