void poker() {

  if (startAnimationNotExecuted) {
    lcd.clear();
    lcd.setCursor(3, 1);
    lcd.print("-- Yahtzee --");
    delay(1500);
    lcd.clear();
    deal();
    lcd.cursor();
    renderHands(false);
    startAnimationNotExecuted = false;
  }

  if (firstValueSettingNotExecuted) {
    lcd.clear();
    pokerCredit = 100;
    pokerBet = 1;
    pokerPay = 0;
    firstValueSettingNotExecuted = false;
  }


  if (millis() % 200 > 100) {

    lcd.setCursor(0, 2);
    lcd.print("Bet: ");
    lcd.print(pokerBet, DEC);

    lcd.setCursor(0, 3);
    lcd.print("Credit: ");
    lcd.print(pokerCredit, DEC);

    lcd.setCursor(12, 3);
    lcd.print("Win:  ");
    lcd.print(pokerPay, DEC);

    lcd.setCursor(cursorPos, 1);

  }

  lcd.cursor();


  if (b) {
    switch (key) {
      case 'A':

        auditiveFeedback();

        if (!revealed) {
          pokerCredit -= pokerBet;
          int houseWin = evaluate(handHouse);
          int playerWin = evaluate(handPlayer);
          for (int i = 0; i < 5; i++) {
            handTrade[i] = false;
          }

          lcd.clear();
          if (playerWin > houseWin) {
            pokerCredit += pokerBet;
            lcd.setCursor(2, 10);
            lcd.print("You won");
          } else {
            pokerCredit -= pokerBet;
            lcd.setCursor(2, 10);
            lcd.print("You lost...");
          }


          renderHands(true);

          delay(2000);

          lcd.clear();

          lcd.setCursor(0, 0);
          lcd.print("House:  ");
          lcd.print(houseWin, DEC);
          lcd.setCursor(0, 1);
          lcd.print("Player: ");
          lcd.print(playerWin, DEC);

          revealed = true;
        } else {
          pokerCredit += pokerPay;
          deal();
          renderHands(false);
          revealed = false;
        }

        b = false;
        break;
      case '#':
        switch (cursorPos) {
          case 8:
            idx = 0;
            break;
          case 10:
            idx = 1;
            break;
          case 12:
            idx = 2;
            break;
          case 14:
            idx = 3;
            break;
          case 16:
            idx = 4;
            break;
        }
        if (handTrade[idx] == false) {
          auditiveFeedback();
          randomSeed(playerSeed + millis() * analogRead(A3) + idx);
          handPlayer[idx] = cards[random(0, sizeof(cards))];
          handTrade[idx] = true;
          renderHands(false);
        }
        b = false;
        break;
      case 'B':
        auditiveFeedback();
        if (cursorPos < 16) {
          cursorPos++;
          cursorPos++;
        } else {
          cursorPos = 8;
        }
        renderHands(false);
        b = false;
        break;
      case 'D':
        auditiveFeedback();
        if (pokerBet < 9) {
          pokerBet++;
        } else {
          pokerBet = 0;
        }
        b = false;
    }
  } else if (!b && key == ' ') {
    b = true;
    delay(20);
  }


}


void renderHands(bool house) {

  if (house) {
    lcd.setCursor(0, 0);
    lcd.print("House:  ");

    for (int i = 0; i < sizeof(handHouse); i++) {
      lcd.print(handHouse[i]);
      lcd.print(" ");
    }
  } else {
    lcd.setCursor(0, 0);
    lcd.print("House:  ");

    for (int i = 0; i < sizeof(handHouse); i++) {
      lcd.write(255);
      lcd.print(" ");
    }
  }

  lcd.setCursor(0, 1);
  lcd.print("Player: ");

  for (int i = 0; i < sizeof(handPlayer); i++) {
    lcd.print(handPlayer[i]);
    lcd.print(" ");
  }
}

void deal() {
  lcd.clear();
  lcd.setCursor(5, 1);
  lcd.print("dealing...");

  for (int i = 0; i < sizeof(handHouse); i++) {
    randomSeed(houseSeed + millis() * analogRead(A3) + i);
    handHouse[i] = cards[random(0, sizeof(cards))];
  }

  for (int i = 0; i < sizeof(handPlayer); i++) {
    randomSeed(playerSeed + millis() * analogRead(A3) + i);
    handPlayer[i] = cards[random(0, sizeof(cards))];
  }
  delay(1000);
}

int evaluate(char subject[]) {

  int sum = 0;
  for (int i = 0; i < 5; i++) {
    sum += subject[i] - '0';
  }

  return sum;
}
