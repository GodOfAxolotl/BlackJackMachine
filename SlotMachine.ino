void slotMachine() {

  if (startAnimationNotExecuted) {
    lcd.clear();
    lcd.setCursor(2, 1);
    lcd.print("- Slot Machine -");
    delay(1500);
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Hold the middle keys");
    lcd.setCursor(1, 2);
    lcd.print("to stop the Slots");
    delay(1500);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Use D to restart");
    lcd.setCursor(0, 1);
    lcd.print("A / B for bet");
    lcd.setCursor(0, 2);
    lcd.print("Win with 3 in a Row");
    lcd.setCursor(0, 3);
    lcd.print("(2 for 1,2,3,A,B,C)");
    delay(2000);
    lcd.clear();
    lcd.setCursor(2, 1);
    lcd.print("Use D to restart");
    lcd.setCursor(4, 2);
    lcd.print("A / B for bet");
    delay(1500);
    lcd.clear();
    startAnimationNotExecuted = false;
  }

  if (firstValueSettingNotExecuted) {
    credit = 100;
    bet = 2;
    pay = 0;

    slot1Pos = 0;
    slot2Pos = 0;
    slot3Pos = 0;

    slot1Rot = true;
    slot2Rot = true;
    slot3Rot = true;
    lcd.clear();
    firstValueSettingNotExecuted = false;
  }


  if (!(slot1Rot || slot2Rot || slot3Rot)) {
    fastRender();
  } else {
    render();
  }

  if (slot1Rot) {
    increaseSlot1();
    lcd.setCursor(8, 0);
    lcd.print(slot1[slot1Pos]);
    lcd.print("|");
    lcd.setCursor(8, 1);
    lcd.print(slot1[getSaveSlot1(1)]);
    lcd.print("|");
    lcd.setCursor(8, 2);
    lcd.print(slot1[getSaveSlot1(2)]);
    lcd.print("|");
    tone(9, 1976);
    delay(100);
    noTone(9);
  }
  if (slot2Rot) {
    increaseSlot2();
    lcd.setCursor(10, 0);
    lcd.print(slot2[slot2Pos]);
    lcd.print("|");
    lcd.setCursor(10, 1);
    lcd.print(slot2[getSaveSlot2(1)]);
    lcd.print("|");
    lcd.setCursor(10, 2);
    lcd.print(slot2[getSaveSlot2(2)]);
    lcd.print("|");
    tone(9, 1760);
    delay(100);
    noTone(9);
  }
  if (slot3Rot) {
    increaseSlot3();
    lcd.setCursor(12, 0);
    lcd.print(slot3[slot3Pos]);
    lcd.setCursor(12, 1);
    lcd.print(slot3[getSaveSlot3(1)]);
    lcd.setCursor(12, 2);
    lcd.print(slot3[getSaveSlot3(2)]);
    tone(9, 1568);
    delay(100);
    noTone(9);
  }

  if (b && !(slot1Rot || slot2Rot || slot3Rot)) {
    if (key == 'B') {
      if (bet > 2) {
        bet--;
      } else {
        bet = 9;
      }
      b = false;
    }
    if (key == 'A') {
      if (bet < 9) {
        bet++;
      } else {
        bet = 2;
      }
      b = false;
    }
  } else {

    if (key == 'B') {
      slot1Rot = false;
      b = false;
    }
    if (key == '#') {
      slot2Rot = false;
      b = false;
    }
    if (key == 'A') {
      slot3Rot = false;
      b = false;
    }
  }

  if (b && key == 'D' && (slot1Rot || slot2Rot || slot3Rot)) {
    b = false;
  } else if (b && key == 'D') {
    credit -= bet;
    pay = 0;
    slot1Rot = true;
    slot2Rot = true;
    slot3Rot = true;
    winEsteemated = false;
    lcd.clear();
  }

  if (key == ' ') {
    b = true;
    delay(10);
  }

  if (!slot1Rot && !slot2Rot && !slot3Rot && !winEsteemated) {
    pay = calculateWin();
    credit += pay;
    winEsteemated = true;
  }
}

int calculateWin() {
  float temp = 0;

  if (slot1[slot1Pos] == slot2[slot2Pos] && slot2[slot2Pos] == slot3[slot3Pos]) {
    temp += decodeMult(slot1[slot1Pos]);
    if (temp > 10) {
      lcd.setCursor(6, 3);
      lcd.print("JACKPOT!!!");
    }
    auditiveFeedback();
  }

  if (slot1[getSaveSlot1(1)] == slot2[getSaveSlot2(1)] && slot2[getSaveSlot2(1)] == slot3[getSaveSlot3(1)]) {
    temp += decodeMult(slot1[getSaveSlot1(1)]);
    if (temp > 10) {
      lcd.setCursor(6, 3);
      lcd.print("JACKPOT!!!");
    }
    auditiveFeedback();
  }

  if (slot1[getSaveSlot1(2)] == slot2[getSaveSlot2(2)] && slot2[getSaveSlot2(2)] == slot3[getSaveSlot3(2)]) {
    temp += decodeMult(slot1[getSaveSlot1(2)]);
    if (temp > 10) {
      lcd.setCursor(6, 3);
      lcd.print("JACKPOT!!!");
    }
    auditiveFeedback();
  }

  if (slot1[slot1Pos] == slot2[slot2Pos] && slot2[slot2Pos] != slot3[slot3Pos]) {
    if (slot1[slot1Pos] != '$' && slot1[slot1Pos] != '7') {
      temp += decodeMult(slot1[slot1Pos]) / 2;
      auditiveFeedback();
    }
  }

  if (slot1[getSaveSlot1(1)] == slot2[getSaveSlot2(1)] && slot2[getSaveSlot2(1)] != slot3[getSaveSlot3(1)]) {
    if (slot1[getSaveSlot1(1)] != '$' && slot1[getSaveSlot1(1)] != '7') {
      temp += decodeMult(slot1[getSaveSlot1(1)]) / 2;
      auditiveFeedback();
    }
  }

  if (slot1[getSaveSlot1(2)] == slot2[getSaveSlot2(2)] && slot2[getSaveSlot2(2)] != slot3[getSaveSlot3(2)]) {
    if (slot1[getSaveSlot1(2)] != '$' && slot1[getSaveSlot1(2)] != '7') {
      temp += decodeMult(slot1[getSaveSlot1(2)]) / 2;
      auditiveFeedback();
    }
  }

  return floor(bet * temp);
}

float decodeMult(char sign) {
  switch (sign) {
    case '1':
      return 1.5;
      break;
    case '2':
      return 2;
      break;
    case '3':
      return 3;
      break;
    case 'A':
      return 5;
      break;
    case 'B':
      return 8;
      break;
    case 'C':
      return 10;
      break;
    case '$':
      return 15;
      break;
    case '7':
      return 100;
      break;
  }
}


void fastRender() {
  lcd.setCursor(0, 0);
  lcd.print("Credit:");
  lcd.setCursor(2, 1);
  if (credit < 100) {
    lcd.print("0");
  }
  if (credit < 10) {
    lcd.print("0");
  }
  lcd.print(credit, DEC);
  lcd.setCursor(0, 2);
  lcd.print("bet");
  lcd.setCursor(0, 3);
  lcd.print(bet, DEC);
  lcd.setCursor(15, 0);
  lcd.print("Win:");
  lcd.setCursor(15, 1);
  if (pay < 1000) {
    lcd.print("0");
  }
  if (pay < 100) {
    lcd.print("0");
  }
  if (pay < 10) {
    lcd.print("0");
  }
  lcd.print(pay, DEC);
}


void render() {
  lcd.setCursor(0, 0);
  lcd.print("Credit:");
  lcd.setCursor(2, 1);
  if (credit < 100) {
    lcd.print("0");
  }
  if (credit < 10) {
    lcd.print("0");
  }
  lcd.print(credit, DEC);
  lcd.setCursor(0, 2);
  lcd.print("bet");
  lcd.setCursor(0, 3);
  lcd.print(bet, DEC);
  lcd.setCursor(15, 0);
  lcd.print("Win:");
  lcd.setCursor(15, 1);
  if (pay < 1000) {
    lcd.print("0");
  }
  if (pay < 100) {
    lcd.print("0");
  }
  if (pay < 10) {
    lcd.print("0");
  }
  lcd.print(pay, DEC);
}


void increaseSlot1() {
  if (slot1Pos < sizeof(slot1) - 1) {
    slot1Pos++;
  } else {
    slot1Pos = 0;
  }
}

void increaseSlot2() {
  if (slot2Pos < sizeof(slot2) - 1) {
    slot2Pos++;
  } else {
    slot2Pos = 0;
  }
}

void increaseSlot3() {
  if (slot3Pos < sizeof(slot3) - 1) {
    slot3Pos++;
  } else {
    slot3Pos = 0;
  }
}


int getSaveSlot1(int i) {
  if (slot1Pos + i < sizeof(slot1)) {
    return slot1Pos + i;
  } else {
    return slot1Pos + i - sizeof(slot1);
  }
  return 0;
}

int getSaveSlot2(int i) {
  if (slot2Pos + i < sizeof(slot2)) {
    return slot2Pos + i;
  } else {
    return slot2Pos + i - sizeof(slot2);
  }
  return 0;
}

int getSaveSlot3(int i) {
  if (slot3Pos + i < sizeof(slot3)) {
    return slot3Pos + i;
  } else {
    return slot3Pos + i - sizeof(slot3);
  }
  return 0;
}
