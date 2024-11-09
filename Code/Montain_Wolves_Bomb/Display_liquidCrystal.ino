
extern boolean setupFinish;
extern String code;

void printBluetoothConfig();
void printPlayers();
void printTimeGame();
void printTimeBomb();
void printBombCode();
void printSmoke(String);
void printSound(String);
void printLeds(String);
void printGPS(String);
void WaitSat();
void printCoordinate();
void printConfirmConfig();
void bombIsReady();
void availableZone();
void invalidZone();
void insertCode();
void teamIntro();
void printDigit(String);
void printCode(String);
void correctCode();
void wrongCode();
void tryAgain();
void bombExploded();
void bombExplodedToArming();
void youWin();
void bombArmed();
void printClock(int, int);
void restart();
void printBarChar();


uint8_t barChar[8] = {
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  };


void printBluetoothChoice() {
  lcd.setCursor(3,0);
  lcd.print("Bluetooth");
  lcd.setCursor(0,1);
  lcd.print("A - Yes   D - No");
  }

void printBluetoothConfig(){
  lcd.setCursor(3,0);
  lcd.print("Bluetooth");
  lcd.setCursor(1,1);
  lcd.print("Configuration!");
}

void printPlayers() {
  lcd.setCursor(0,0);
  lcd.print("Players Number");
}

void printTimeGame() {
  lcd.setCursor(0,0);
  lcd.print("Time Game");
}

void printTimeBomb() {
  lcd.setCursor(0,0);
  lcd.print("Time Bomb");
}

void printBombCode() {
  lcd.setCursor(0,0);
  lcd.print("Bomb Code");
}

void printGPS(String status){
  lcd.setCursor(0,0);
  lcd.print("GPS?");
  lcd.setCursor(9,0);
  lcd.print(status);
  lcd.setCursor(0,1);
  lcd.print("A - Yes   B - No");
}

void WaitSat() {
  lcd.setCursor(0,0);
  lcd.print("*****Wait*******");
  lcd.setCursor(0, 1);
  lcd.print("For more Sats!!*");
}

void printCoordinate() {
  lcd.setCursor(0, 0);
  lcd.print("Lat: "); lcd.print(gps.location.lat(), 6);
  lcd.setCursor(0, 1);
  lcd.print("Long: "); lcd.print(gps.location.lng(), 6);
}

void setNewCoordinates() {
  lcd.setCursor(2, 0);
  lcd.print("coordenates");
  lcd.setCursor(3, 1);
  lcd.print("Configured");
}

void printLeds(String status){
  lcd.setCursor(0,0);
  lcd.print("Leds?");
   lcd.setCursor(9,0);
  lcd.print(status);
  lcd.setCursor(0,1);
  lcd.print("A - Yes   B - No");

}

void printSound(String status){
  lcd.setCursor(0,0);
  lcd.print("Sound?");
   lcd.setCursor(9,0);
  lcd.print(status);
  lcd.setCursor(0,1);
  lcd.print("A - Yes   B - No");

}

void printSmoke(String status){
  lcd.setCursor(0,0);
  lcd.print("Smoke?");
   lcd.setCursor(9,0);
  lcd.print(status);
  lcd.setCursor(0,1);
  lcd.print("A - Yes   B - No");
}

void printConfirmConfig(){
  lcd.setCursor(4,0);
  lcd.print("Confirm?");
  lcd.setCursor(0,1);
  lcd.print("D - Yes   C - No");
}

void bombIsReady(){
  lcd.setCursor(6,0);
  lcd.print("Bomb");
  lcd.setCursor(5, 1);
  lcd.print("READY!");
}

void availableZone(){
  lcd.backlight();
  lcd.setCursor(6, 0);
  lcd.print("Zone");
  lcd.setCursor(3, 1);
  lcd.print("Autorized");
}

void invalidZone(){
  lcd.backlightOff();
  lcd.setCursor(6, 0);
  lcd.print("Zone");
  lcd.setCursor(4, 1);
  lcd.print("Invalid");
}

void teamIntro(){
  lcd.setCursor(1,0);
  lcd.print("Montain Wolves");
  lcd.setCursor(4,1);
  lcd.print(F("Press D!!"));
}


void insertCode(){
  lcd.setCursor(0,0);
  lcd.print("Insert Bomb Code");
}


void bombArmed(){
  lcd.setCursor(0,0);
  lcd.print("Armed");
}

void printClock(int timeMin, int timeSec){
  lcd.setCursor(11, 0); // Or setting the cursor in the desired position.
  if (timeMin < 10){
    lcd.print("0");  
  }
  lcd.print(timeMin);
  lcd.print(":");
  if (timeSec < 10){
    lcd.print("0");  
  }
  lcd.print(timeSec);
}

void printDigit(String digit){
  lcd.setCursor(0, 1);
  lcd.print(digit); 
}

void correctCode(){
  lcd.setCursor(1,0);
  lcd.print("Correct Code!");
}

void wrongCode(){
  lcd.setCursor(2,0);
  lcd.print("Wrong Code!");
}

void printCode(String code){
  lcd.setCursor(0, 1);
  lcd.print(code);
}

void tryAgain(){
  lcd.setCursor(3,1);
  lcd.print("Try Again!!");
}

void bombExploded(){
  lcd.setCursor(1,0);
  lcd.print("Bomb Exploded");
}

void bombExplodedToArming(){
  lcd.setCursor(1,0);
  lcd.print("Bomb Exploded");
  lcd.setCursor(3, 1);
  lcd.print("To Arming");
}

void youWin(){
  lcd.setCursor(4,0);
  lcd.print("YOU WIN!");
}

void restart() {
  lcd.setCursor(5,0);
  lcd.print("Restart");
  lcd.setCursor(4,1);
  lcd.print("Press D");
}

void printBarChar(){
  lcd.createChar(0, barChar);
  lcd.write(0);
}


