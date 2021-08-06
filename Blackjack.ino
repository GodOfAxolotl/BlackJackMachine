
void blackJack() {

  if (startAnimationNotExecuted) {
    lcd.clear();
    lcd.setCursor(3, 1);
    lcd.print("- Blackjack -");
    delay(1500);
    lcd.clear();
    lcd.setCursor(2, 1);
    lcd.print("Press A to stay");
    lcd.setCursor(2, 2);
    lcd.print("Press B to take");
    delay(1500);
    lcd.clear();
    lcd.setCursor(2, 1);
    lcd.print("Keep your cards");
    lcd.setCursor(2, 2);
    lcd.print("under 21");
    delay(1500);
    lcd.clear();
    startAnimationNotExecuted = false;
    
  }

  if (firstValueSettingNotExecuted) {
    lcd.clear();
    setter();
    wins = 0;
    firstValueSettingNotExecuted = false;
  }

  if (!over) {
    printBaseText();
  }

  if (b) {
    switch (key) {
      case 'A':
        auditiveFeedback();
        if (over) {
          reset();
          b = false;
          return;
        }
        stay();
        b = false;
        break;
      case '#':
        break;
      case 'B':
        auditiveFeedback();
        if (over) {
          reset();
          b = false;
          return;
        }

        temp = giveCard(1);
        player += temp;
        lcd.setCursor(index, 3);
        lcd.print(temp, DEC);
        index += 3;

        if (player > 21) {
          lcd.clear();
          winn = false;
          tiee = false;
          lost = true;
          over = true;
          wins--;
          printScore(loose);
          b = false;
          return;
        }
        if (house <= 17) {
          lastHouseCard = giveCard(1);
          house += lastHouseCard;
        }
        b = false;
        //lcd.clear();
        break;
      case 'D':
        auditiveFeedback();
        reset();
        b = false;
        break;
    }
  } else if (!b && key == ' ') {
    b = true;
    delay(20);
  }

  if (over) {
    if (winn) {
      printScore(win);
      if (!playedSound) {
        winSound();
        playedSound = true;
      }
    } else if (lost) {
      printScore(loose);
      if (!playedSound) {
        looseSound();
        playedSound = true;
      }
    } else if (tiee) {
      printScore(tie);
    } else {
      lcd.setCursor(0, 0);
      lcd.print("Error");
    }
  }
}

//-------------------------------------------------------------------------------

void reset() {
  lcd.clear();
  noTone(9);
  house = 0;
  player = 0;
  over = false;
  playedSound = false;
  winn = false;
  lost = false;
  tiee = false;
  setter();
}     //zurücksetzen aller wechselnden Laufvariablen

//-------------------------------------------------------------------------------

void setter() {
  index = 0;
  temp = giveCard(1);
  player = temp;
  lcd.setCursor(index, 3);
  lcd.print(temp, DEC);
  index += 3;

  house = giveCard(100);

  temp = giveCard(1);
  player += temp;
  lcd.setCursor(index, 3);
  lcd.print(temp, DEC);
  index += 3;

  lastHouseCard = giveCard(100);
  house += lastHouseCard;           // Spielstart initieren, jeder zieht 2 Karten, die letzte Karte der Bank wird dem Spieler Angezeigt.
}

//-------------------------------------------------------------------------------

void stay() {
  lcd.clear();
  while (house <= 17) {
    house += giveCard(1);
  }

  if (house == player) {                         //Unentschieden bei gleicher Zahl, auszahlung 1:1
    tiee = true;
  } else if (house <= 21 && house >= player) {  //Spieler verliert, wenn die Bank mehr als er enthält, sich jedoch nicht überkauft
    lost = true;
    wins--;
  } else if (player <= 21) {                       //Solange der Spieler sich nicht überkauft, gewinnt er jetzt
    winn = true;
    wins++;
  } else {                                           // Spieler hat sich überkauft, er verliert seinen Einsatz
    //sevseg.setChars(loose);
    lost = true;
    wins--;
  }    //Berrechnung des Gewinners

  over = true;
}

//-------------------------------------------------------------------------------

int giveCard( int mult) {
  delay(1);
  if (mult < 50) {
    randomSeed(houseSeed + millis() * analogRead(A3));
  } else {
    randomSeed(playerSeed + millis() * analogRead(A3));
  }                                                 //Seedverteilung um Haus und Spieler zu differenzieren, da diese sonst die selbe Karte bekommen durch die Systemzeit
  int output = floor(random(1, 12));
  if (output >= 10) {
    output = 10;
  }                                                //Bildkarten sind 10 Wert und durch ihre hohe anzahl wahrscheinlicher
  if (output == 1 && output + 11 <= 21) {
    output = 11;
  }                                                //Ass Sonderregel

  return output;   //Multiplikator um den Spieler neben der Bank anzuzeigen
}

//-------------------------------------------------------------------------------

void printScore(char text[]) {
  lcd.setCursor(0, 0);
  lcd.print(text);
  lcd.setCursor(1, 1);
  lcd.print("H:");
  lcd.setCursor(3, 1);
  lcd.print(house);
  lcd.setCursor(6, 1);
  lcd.print("P:");
  lcd.setCursor(8, 1);
  lcd.print(player);

  lcd.setCursor(3, 3);
  lcd.print("Press A or B");

}

void auditiveFeedback() {
  tone(9, 698);
  delay(20);
  noTone(9);
}

//-------------------------------------------------------------------------------

void printBaseText() {
  lcd.setCursor(0, 0);
  lcd.print("House: ");
  lcd.setCursor(8, 0);
  lcd.print(lastHouseCard, DEC);

  if (lastHouseCard < 10) {
    lcd.setCursor(9, 0);
    lcd.print(" ");
  }

  lcd.setCursor(0, 2);
  lcd.print("Player: ");
  lcd.setCursor(8, 2);
  lcd.print(player, DEC);

  lcd.setCursor(14, 1);
  lcd.print("Win:");
  lcd.setCursor(15, 2);
  lcd.print(wins, DEC);
}



//-------------------------------------------------------------------------------
