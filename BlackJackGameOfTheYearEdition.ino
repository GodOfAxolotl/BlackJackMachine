#include <LiquidCrystal.h>
//#include <SPI.h> // BUS System
#include "DHT.h" //DHT Bibliothek laden für das TEMP Modul
#include "RTClib.h"
//#include <Wire.h> // Wire Bibliothek einbinden
#include <LiquidCrystal_I2C.h> // Vorher hinzugefügte LiquidCrystal_I2C Bibliothek einbinden

RTC_DS1307 RTC;
LiquidCrystal_I2C lcd(0x27, 20, 4); //LCD 20*4, Adresse 0x27

#define DHTPIN 8 //Der Sensor wird an PIN 2 angeschlossen    
#define DHTTYPE DHT11    // Es handelt sich um den DHT11 Sensor

DHT dht(DHTPIN, DHTTYPE); //Der Sensor wird ab jetzt mit „dth“ angesprochen

//******************** HARDWARE ***************************

#define buzzerPin 9
#define ledPin1 10
#define ledPin2  11
#define readerPin A0

#define DS1307_ADDRESS 0x68 //Die Ardesse der RTC
byte zero = 0x00; //wird benötigt, um einen Fehler in der RTC zu umgehen

//******************* SENOS *********************

bool b = true;
boolean bootupNotDone = true;
boolean gameStarted = false;
bool startAnimationNotExecuted = true;
bool firstValueSettingNotExecuted = true;
String menuBand[] = {"Black Jack", "Slot Machine", "Roulette", "Yahtzee", "High/Low","Clock", "Options"};
int menuOptions = 7;
int menuPos = 0;
bool option[] = {false, false, false, false, false, false, false, false};
bool bcklght = true;
char key;
bool showBootup = true;
bool showTmp = true;

//********************* BLACKJACK *****************************

int temp;

#define win "Player Wins!  +1"
#define loose "House Wins!  -1"
#define tie "Tie...   +0"

bool playedSound = false;
int8_t house = 0;
int8_t player = 0;
int8_t wins = 0;
const unsigned long playerSeed = 43646346;
const unsigned long houseSeed = 975362748;
short lastHouseCard;
short activeCard = 0;
bool over = false;
boolean winn = false;
boolean tiee = false;
boolean lost = false;
boolean switchi = false;
int index = 0;

//******************** SLOT MACHINE *************************

char slot1[] = {'1', '2', '3', 'A', 'B', 'C', '$', '1', '2', '3', '2', '3', '1', 'A', 'B', 'C', '7', '$', '$'};
char slot2[] = {'A', 'B', 'C', '1', '7', '1', '$', '2', '3', 'C', 'B', 'A', '$', '1', '2', '3', '3', '2', '1'};
char slot3[] = {'7', '1', '2', '3', '$', '3', '2', '1', '$', 'A', 'B', 'C', '$', 'C', 'A', '3', 'B', '1', '2'};

short slot1Pos = 0;
short slot2Pos = 0;
short slot3Pos = 0;

bool slot1Rot = true;
bool slot2Rot = true;
bool slot3Rot = true;

int credit = 100;
int bet = 2;
int pay = 0;

bool winEsteemated = false;

//******************** ROULETTE ****************************

int8_t roulette[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30};
short rouletteSize = 30;
short spd = 100;
short rouIndex = 0;

bool rouletteStopping = false;
bool rouletteStopped = false;

int guessNumber = 0;
int combo = 0;



//********************* YAHTZEE ******************************

int8_t cards[] = {'1', '2', '3', '4', '5', '6'};


short cardTypes = 8;

char handHouse[] = {'o', 'o', 'o', 'o', 'o'};
char handPlayer[] = {'x', 'x', 'x', 'x', 'x'};

bool handTrade[] = {false, false, false, false, false};

bool revealed = false;

int8_t idx = 0;

int cursorPos = 8;

int pokerCredit = 100;
int8_t pokerBet = 1;
int pokerPay = 0;

//******************** HIGHER LOWER ************************

int8_t currentCard = 0;
int8_t previousCard = 0;

bool higher = false;

int guessCount = 0;


//******************** CLOCK *******************************

char daysOfTheWeek[7][3] = { "Mon", "Tue", "Wdn", "Thr", "Frd", "Std", "Sun"};
const bool timeReadOnly = true;
int8_t clockMenu = 0;
int8_t hourupg;
int8_t minupg;
int yearupg;
int8_t monthupg;
int8_t dayupg;
float humidity;
float temperature;


//******************** CODE ****************************
