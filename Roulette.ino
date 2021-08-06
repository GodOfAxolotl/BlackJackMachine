void rouletteGame() {
  if (startAnimationNotExecuted) {
    lcd.clear();
    lcd.setCursor(4, 1);
    lcd.print("- Roulette -");
    delay(1500);
    lcd.setCursor(1, 1);
    lcd.print("Bet on a Odd, Even");
    lcd.setCursor(3, 2);
    lcd.print("or 0 and watch");
    delay(1500);
    lcd.clear();
    lcd.setCursor(6, 1);
    lcd.print("Restart");
    lcd.setCursor(4, 2);
    lcd.print("by holding D");
    delay(1500);
    lcd.clear();
    playedSound = false;
    startAnimationNotExecuted = false;
  }

  if (firstValueSettingNotExecuted) {
    lcd.clear();
    rouIndex = getStart();
    guessNumber = 0;
    spd = 100;
    combo = 0;
    rouletteStopping = false;
    rouletteStopped = false;
    playedSound = false;
    firstValueSettingNotExecuted = false;
  }


  if (b) {
    switch (key) {
      case 'A':
        if (!rouletteStopping && !rouletteStopped) {
          auditiveFeedback();
          guessNumber = 1;
          rouletteStopping = true;
          b = false;
          lcd.clear();
        }
        break;
      case '#':
        if (!rouletteStopping && !rouletteStopped) {
          auditiveFeedback();
          rouletteStopping = true;
          b = false;
          lcd.clear();
        }
        break;
      case 'B':
        if (!rouletteStopping && !rouletteStopped) {
          auditiveFeedback();
          guessNumber = 3;
          rouletteStopping = true;
          b = false;
          lcd.clear();
        }
        break;
      case 'D':
        spd = 100;
        playedSound = false;
        rouletteStopping = false;
        rouletteStopped = false;
        guessNumber = 0;
        b = false;
        playedSound = false;
        lcd.clear();
        break;
    }
  } else if (!b && key == ' ') {
    b = true;
    delay(20);
  }

  if (rouletteStopping) {
    randomSeed(millis());
    spd += random(10, 30);

    if (spd > 600 && random(1, 4) == 1) {
      rouletteStopped = true;
      rouletteStopping = false;
      renderAndTick();
      if (!playedSound) {
        tone(9, 987.87);
        delay(30);
        noTone(9);
        delay(600);
        playedSound = true;
      }
      playedSound = false;
    }
  }

  if (rouletteStopped) {
    lcd.setCursor(17, 0);
    lcd.print(roulette[rouIndex + 1]);
    switch (guessNumber) {
      case 1:
        if (roulette[rouIndex + 1] % 2 == 0) {
          if (!playedSound) {
            comboCounter();
            tone(9, 987.87);
            delay(100);
            noTone(9);
            tone(9, 1318.51);
            delay(120);
            noTone(9);
            playedSound = true;
          }
        } else {
          if (!playedSound) {
            comboBreaker();
            tone(9, 1318.51);
            delay(100);
            noTone(9);
            tone(9, 987.87);
            delay(120);
            noTone(9);
            playedSound = true;
          }
        }
        break;
      case 3:
        if (roulette[rouIndex + 1] % 2 == 1) {
          if (!playedSound) {
            comboCounter();
            tone(9, 987.87);
            delay(100);
            noTone(9);
            tone(9, 1318.51);
            delay(120);
            noTone(9);
            playedSound = true;
          }
        } else {
          if (!playedSound) {
            comboBreaker();
            tone(9, 1318.51);
            delay(100);
            noTone(9);
            tone(9, 987.87);
            delay(120);
            noTone(9);
            playedSound = true;
          }
        }
        break;
    }
  }
  if (!rouletteStopped) {
    renderAndTick();
  }
}

void renderAndTick() {
  for (int i = 0; i < 20; i += 3) {

    lcd.setCursor(i, 1);
    if (roulette[rouIndex + i / 3] < 10) {
      lcd.print(" ");
    }
    if (rouIndex + i / 3 < rouletteSize) {
      lcd.print(roulette[rouIndex + i / 3], DEC);
    } else {
      lcd.print(roulette[rouIndex + i / 3 - rouletteSize], DEC);
    }
    if (i < 17) {
      lcd.print("|");
    }
  }
  lcd.setCursor(5, 0);
  lcd.print("Combo: ");
  lcd.print(combo, DEC);

  lcd.setCursor(3, 2);
  lcd.print("^^");

  if (!rouletteStopping) {
    lcd.setCursor(4, 3);
    lcd.print("ODD  ");
    lcd.print("NO  ");
    lcd.print("EVEN");
  }
  if (!rouletteStopped) {
    tone(9, 987.87);
    delay(30);
    noTone(9);
    delay(spd);
    if (rouIndex < rouletteSize - 1) {
      rouIndex++;
    } else {
      rouIndex = 0;
    }
  }
}



int getStart() {
  randomSeed(100 * millis() * analogRead(A3));
  return floor(random(1, 30));
}

void comboCounter() {
  if (combo < 0) {
    lcd.clear();
    combo = 0;
  } else {
    combo++;
  }
}

void comboBreaker() {
  if (combo > 0) {
    lcd.clear();
    combo = 0;
  } else {
    combo--;
  }
}
