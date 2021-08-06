void highorLow() {

  if (startAnimationNotExecuted) {
    lcd.clear();
    lcd.setCursor(2, 1);
    lcd.print("- Higher/Lower -");
    delay(1500);
    lcd.clear();

    currentCard = getCard();
    previousCard = getCard();
    guessCount = 0;
    startAnimationNotExecuted = false;
  }

  if (firstValueSettingNotExecuted) {
    lcd.clear();
    currentCard = getCard();
    previousCard = getCard();
    guessCount = 0;
    firstValueSettingNotExecuted = false;
  }


  lcd.setCursor(2, 3);
  lcd.print("Higher    Lower");

  lcd.setCursor(1, 0);
  lcd.print("Score    : ");
  lcd.print(guessCount);
  lcd.setCursor(1, 1);
  lcd.print("Pre. Card: ");
  lcd.print(previousCard);
  lcd.setCursor(1, 2);
  lcd.print("Cur. Card: ");
  lcd.print(currentCard);

  if (b) {
    switch (key) {
      case 'A':
        auditiveFeedback();
        higher = false;
        checkCard();
        b = false;

        break;
      case '#':
        auditiveFeedback();
        b = false;

        break;
      case 'B':
        auditiveFeedback();
        higher = true;
        checkCard();
        b = false;

        break;
      case 'D':
        b = false;
        break;
    }
  } else if (!b && key == ' ') {
    b = true;
    delay(20);
  }
}

void checkCard() {
  lcd.clear();
  previousCard = currentCard;
  while (previousCard == currentCard) {
    currentCard = getCard();
  }

  if (higher) {
    if (currentCard > previousCard) {
      guessCount++;
      winSound();
      lcd.setCursor(15, 1);
      lcd.print("Right");
    } else {
      guessCount--;
      lcd.setCursor(15, 1);
      lcd.print("False");
      looseSound();
    }
  } else {
    if (currentCard < previousCard) {
      guessCount++;
      lcd.setCursor(15, 1);
      lcd.print("Right");
      winSound();
    } else {
      guessCount--;
      lcd.setCursor(15, 1);
      lcd.print("False");
      looseSound();
    }
  }

}

int getCard() {
  randomSeed(playerSeed + millis() * analogRead(A3));
  return random(1, 100);
}
