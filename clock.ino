void oclock()
{

  // check if you press the SET button and increase the clockMenu index
  if (key == '#')
  {
    clockMenu = clockMenu + 1;
  }
  // in which subroutine should we go?
  if (clockMenu == 0)
  {
    DisplayDateTime(); // void DisplayDateTime

  }
  if (clockMenu == 1)
  {
    DisplaySetHour();
  }
  if (clockMenu == 2)
  {
    DisplaySetMinute();
  }
  if (clockMenu == 3)
  {
    DisplaySetYear();
  }
  if (clockMenu == 4)
  {
    DisplaySetMonth();
  }
  if (clockMenu == 5)
  {
    DisplaySetDay();
  }
  if (clockMenu == 6)
  {
    StoreAgg();
    delay(500);
    clockMenu = 0;
  }
  delay(100);
}

void DisplayTime() {
  DateTime now = RTC.now();
  getRoomValue();
  if (showTmp) {
    lcd.setCursor(3, 0);
    if (now.hour() <= 9)
    {
      lcd.print("0");
    }
    lcd.print(now.hour(), DEC);
    hourupg = now.hour();
    lcd.print(":");
    if (now.minute() <= 9)
    {
      lcd.print("0");
    }
    lcd.print(now.minute(), DEC);
    minupg = now.minute();
    lcd.print(":");
    if (now.second() <= 9)
    {
      lcd.print("0");
    }
    lcd.print(now.second(), DEC);

    lcd.setCursor(12, 0);
    lcd.print(temperature, 1);
    lcd.print("C");
  } else {
    lcd.setCursor(6, 0);
    if (now.hour() <= 9)
    {
      lcd.print("0");
    }
    lcd.print(now.hour(), DEC);
    hourupg = now.hour();
    lcd.print(":");
    if (now.minute() <= 9)
    {
      lcd.print("0");
    }
    lcd.print(now.minute(), DEC);
    minupg = now.minute();
    lcd.print(":");
    if (now.second() <= 9)
    {
      lcd.print("0");
    }
    lcd.print(now.second(), DEC);

  }

}

void getRoomValue() {
  humidity = dht.readHumidity(); //die Luftfeuchtigkeit auslesen und unter „humidity“ speichern
  temperature = dht.readTemperature();//die Temperatur auslesen und unter „temperatur“ speichern
}

void DisplayDateTime ()
{
  // We show the current date and time
  DateTime now = RTC.now();
  getRoomValue();
  lcd.setCursor(2, 2);
  lcd.print("Hour: ");
  if (now.hour() <= 9)
  {
    lcd.print("0");
  }
  lcd.print(now.hour(), DEC);
  hourupg = now.hour();
  lcd.print(":");
  if (now.minute() <= 9)
  {
    lcd.print("0");
  }
  lcd.print(now.minute(), DEC);
  minupg = now.minute();
  lcd.print(":");
  if (now.second() <= 9)
  {
    lcd.print("0");
  }
  lcd.print(now.second(), DEC);

  lcd.setCursor(2, 1);
  lcd.print("Date: ");
  if (now.day() <= 9)
  {
    lcd.print("0");
  }
  lcd.print(now.day(), DEC);
  dayupg = now.day();
  lcd.print("/");
  if (now.month() <= 9)
  {
    lcd.print("0");
  }
  lcd.print(now.month(), DEC);
  monthupg = now.month();
  lcd.print("/");
  lcd.print(now.year(), DEC);
  yearupg = now.year();

  lcd.setCursor(2, 3);
  lcd.print("Temp: ");
  lcd.setCursor(8, 3);
  lcd.print(temperature, 1);
  lcd.print("C");
  lcd.setCursor(14, 3);
  lcd.print(humidity, 1);
  lcd.print("%");

}

void DisplaySetHour()
{
  // time setting
  lcd.clear();
  DateTime now = RTC.now();
  if (key == 'A')
  {
    if (hourupg == 23)
    {
      hourupg = 0;
    }
    else
    {
      hourupg = hourupg + 1;
    }
  }
  if (key == 'B')
  {
    if (hourupg == 0)
    {
      hourupg = 23;
    }
    else
    {
      hourupg = hourupg - 1;
    }
  }
  lcd.setCursor(0, 0);
  lcd.print("Set time:");
  lcd.setCursor(0, 1);
  lcd.print(hourupg, DEC);
  delay(20);
}

void DisplaySetMinute()
{
  // Setting the minutes
  lcd.clear();
  if (key == 'A')
  {
    if (minupg == 59)
    {
      minupg = 0;
    }
    else
    {
      minupg = minupg + 1;
    }
  }
  if (key == 'B')
  {
    if (minupg == 0)
    {
      minupg = 59;
    }
    else
    {
      minupg = minupg - 1;
    }
  }
  lcd.setCursor(0, 0);
  lcd.print("Set Minutes:");
  lcd.setCursor(0, 1);
  lcd.print(minupg, DEC);
  delay(20);
}

void DisplaySetYear()
{
  // setting the year
  lcd.clear();
  if (key == 'A')
  {
    yearupg = yearupg + 1;
  }
  if (key == 'B')
  {
    yearupg = yearupg - 1;
  }
  lcd.setCursor(0, 0);
  lcd.print("Set Year:");
  lcd.setCursor(0, 1);
  lcd.print(yearupg, DEC);
  delay(20);
}

void DisplaySetMonth()
{
  // Setting the month
  lcd.clear();
  if (key == 'A')
  {
    if (monthupg == 12)
    {
      monthupg = 1;
    }
    else
    {
      monthupg = monthupg + 1;
    }
  }
  if (key == 'B')
  {
    if (monthupg == 1)
    {
      monthupg = 12;
    }
    else
    {
      monthupg = monthupg - 1;
    }
  }
  lcd.setCursor(0, 0);
  lcd.print("Set Month:");
  lcd.setCursor(0, 1);
  lcd.print(monthupg, DEC);
  delay(20);
}

void DisplaySetDay()
{
  // Setting the day
  lcd.clear();
  if (key == 'A')
  {
    if (dayupg == 31)
    {
      dayupg = 1;
    }
    else
    {
      dayupg = dayupg + 1;
    }
  }
  if (key == 'B')
  {
    if (dayupg == 1)
    {
      dayupg = 31;
    }
    else
    {
      dayupg = dayupg - 1;
    }
  }
  lcd.setCursor(0, 0);
  lcd.print("Set Day:");
  lcd.setCursor(0, 1);
  lcd.print(dayupg, DEC);
  delay(20);
}

void StoreAgg()
{
  // Variable saving
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SAVING IN");
  lcd.setCursor(0, 1);
  lcd.print("PROGRESS");
  RTC.adjust(DateTime(yearupg, monthupg, dayupg, hourupg, minupg, 0));
  delay(400);
  lcd.clear();
}
