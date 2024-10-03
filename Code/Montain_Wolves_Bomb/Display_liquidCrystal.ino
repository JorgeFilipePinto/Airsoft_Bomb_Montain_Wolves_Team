
extern boolean setupFinish;
extern String code;

void printBluetoothConfig();
void printPlayers();
void printTimeGame();
void printTimeBomb();
void printBombCode();
void printConfirmConfig();
void bombIsReady();
void availableZone();
void invalidZone();
void insertCode();
void teamScroll();
void printTeam();
void printDigit(String);
void printCode(String);
void correctCode();
void tryAgain();
void bombExploded();
void bombExplodedToArming();
void youWin();
void bombArmed();


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

void printConfirmConfig(){
  lcd.setCursor(0,0);
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

void teamScroll(){
  lcd.setCursor(9,0);
  lcd.print("Montain Wolves");
  lcd.setCursor(5,1);
  lcd.print(F("Press D to continue!!"));
}

void printTeam(){
  lcd.setCursor(1,0);
  lcd.print("Montain Wolves");
  lcd.setCursor(2,1);
  lcd.print("Airsoft Bomb");
}

void insertCode(){
  lcd.setCursor(0,0);
  lcd.print("Insert Bomb Code");
}


void bombArmed(){
  lcd.setCursor(2,0);
  lcd.print("Bomb Armed!");
}

void printDigit(String digit){
  lcd.setCursor(0, 1);
  lcd.print(digit); 
}

void correctCode(){
  lcd.setCursor(1,0);
  lcd.print("Correct Code!");
  delay(5000);
  lcd.clear();
}

void printCode(String code){
  lcd.setCursor(0, 1);
  lcd.print(code);
}

void tryAgain(){
  lcd.setCursor(3,0);
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


