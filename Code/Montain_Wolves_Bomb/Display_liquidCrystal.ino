
extern boolean setupFinish;

void bluetoothConfig();
void bombIsReady();
void availableZone();
void invalidZone();
void insertCode();
void teamScroll();
void printTeam();
void printDigit();
void printCode(String);
void correctCode();
void tryAgain();
void bombExploded();
void bombExplodedToArming();
void youWin();
void bombArmed();



void bluetoothConfig(){
  lcd.setCursor(3,0);
  lcd.print("Bluetooth");
  lcd.setCursor(1,1);
  lcd.print("Configuration!");
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

void printDigit(char key){
  lcd.setCursor(0, 1);
  lcd.print(key); 
}

void correctCode(){
  lcd.setCursor(1,0);
  lcd.print("Correct Code!");
  delay(5000);
  lcd.clear();
}

void printCode(String code){
  lcd.setCursor(4, 1);
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


