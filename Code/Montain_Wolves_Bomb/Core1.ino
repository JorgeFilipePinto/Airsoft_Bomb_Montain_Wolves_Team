extern void printBluetoothChoice();
extern void printBluetoothConfig();
extern void bluetoothConfig(BluetoothSerial);
extern boolean manuallyConfigured();
extern void invalidZone();
extern void availableZone();
extern void insertCode();
extern void correctCode();
extern void wrongCode();
extern void tryAgain();
extern void bombClock(unsigned long, int, int);
extern void youWin();
extern void bombArmed();
extern void printDigit(String);
extern void printCode(String);
extern void bombExploded();
extern void bombExplodedToArming();
extern void restart();
extern void beepingTimes(int, int);
extern void beepBomb();
extern void beepOn(boolean);
void core_1();
unsigned long lastBeep;
int bombTime;

String code = "";
String secondCode = "";
int codeSize = 0;
int secondCodeSize = 0;
int minutesAnterior = bomb.time / 1000;
int secondsAnterior = 59;

unsigned long int bombTime_millisAnterior = 0;
unsigned long int clock_millisAnterior = 0;
unsigned long int gameTimeLast = 0;
int count = 0;
int timeMin;
int timeSec;

enum GameStatus {
  Configuration,
  Prepared,
  ReadyToArm,
  TryCode,
  VerifyCode,
  Disarm,
  Explode,
  ExplodeTryArming,
  Restart
};

GameStatus gameStatus = Configuration;

void core_1(){

  switch(gameStatus){
    case Configuration: {
      bomb.bombStatus = configuration;
      printBluetoothChoice();
      char key = keypad.getKey();
      if (key == 'A'){
        beepingTimes(1, 50);
        lcd.clear();
        String message = "";
        Serial.println("Bluetooth configuration!");
        printBluetoothConfig();
        bluetoothConfig(BT);
        lcd.clear();
        gameStatus = Prepared;
        gameTimeLast = millis();
      }
      if (key == 'D'){
        beepingTimes(1, 50);
        lcd.clear();
        manuallyConfigured();
        gameStatus = Prepared;
      }
      break;
    }
    case Prepared: {
      /*double coordinates = TinyGPSPlus::distanceBetween(gps.location.lat(), gps.location.lng(), bomb.latZone, bomb.longZone);
      if(bomb.isValidZone()){
        availableZone();*/
        gameStatus = ReadyToArm;  
      /*}else{
        lcd.setCursor(0,0);
        Serial.println(coordinates);
        invalidZone();
      }*/
      break;
    }
    case ReadyToArm: {
      if (millis() - gameTimeLast >= bomb.gameTime) {
        bomb.bombStatus = explode;
        gameStatus = Explode;
        lcd.clear();
        break;
      }
      insertCode();
      bomb.bombStatus = readyToArm;
      char key = keypad.getKey();
      if(key){
        beepingTimes(1, 50);
        if(key == 'D' && bomb.tryArming > 0 && codeSize > 0){
          if(code == bomb.code){
            //Serial.println("Codigo inserido com sucesso!");
            //Serial.print("code size "); Serial.println(codeSize);
            gameStatus = TryCode;
            Serial.println("https://www.google.com/maps/place/40.769838,-8.026673");
            lastBeep = millis();
            timeMin = bomb.time / 60000;
            bombTime = bomb.time;
            timeSec = 0;
            lcd.clear();
            bomb.bombStatus = armed;
          }else{
            lcd.clear();
            tryAgain();
            bomb.tryArming--;
            code = "";
            codeSize = 0;
            if (bomb.tryArming == 0){
              lcd.clear();
              //gameStatus = ExplodeTryArming;
            }
          }
        } else if (key == 'C' && codeSize > 0){
          lcd.clear();
          codeSize--;
          if (codeSize > 0) {
            code = code.substring(0, code.length() - 1);
            printCode(code);
          }else { 
            code = "";
          }
        }else  if (isNum(key)) {
          code += key;
          codeSize++;
          //Serial.print("Digit Insert "); Serial.println(key);
          printDigit(code);
        }
      }
      break;
    }
    case TryCode: {
      if (millis() - gameTimeLast >= bomb.gameTime) {
        bomb.bombStatus = explode;
        gameStatus = Explode;
        lcd.clear();
        break;
      }
      beepBomb();
      printDigit(secondCode);
      //Serial.println(bomb.time);
      bombArmed();
      if (bomb.time > 0) {
        if (timeSec == 0) {
          bombTime_millisAnterior = millis();
          timeMin--;
          timeSec = 59;
          lcd.clear();
        } else if (millis() - bombTime_millisAnterior >= 1000) {
          bombTime_millisAnterior = millis();
          timeSec--;
          bomb.time -= 1000;
          lcd.clear();
        }
        if (timeMin > 0 || timeSec > 0){
          printClock(timeMin, timeSec);
        }
      }else {
        lcd.clear();
        gameStatus = Explode;
      }

      char key = keypad.getKey();
      if (key){
        beepingTimes(1, 50);
        if (key == 'D' && secondCodeSize > 0){
          gameStatus = VerifyCode;
          lcd.clear();
        }else if (key == 'C' && secondCodeSize > 0){
          lcd.clear();
          secondCodeSize--;
          if (secondCodeSize > 0) {
            secondCode = secondCode.substring(0, secondCode.length() - 1);
            printCode(secondCode);
          }else{
            secondCode = "";
          }
        }else if (isNum(key)){
          secondCode += key;
          //Serial.print("Digit Insert "); Serial.println(key);
          secondCodeSize++;
          //Serial.print("Faltam "); Serial.println(secondCodeSize);
          printDigit(secondCode);
        }
      }
      break;
    }
    case VerifyCode: {
      if(bomb.checkCode(secondCode)){
        lcd.clear();
        correctCode();
        bomb.codeDiscovered = true;
        //Serial.println("correct code!");
        gameStatus = Disarm;
        lcd.clear();
      } else if (bomb.tries == 0){
        lcd.clear();
        bomb.codeDiscovered = false;
        gameStatus = Explode;
      }else{
        lcd.clear();
        bomb.codeDiscovered = false;
        wrongCode();
        tryAgain();
        bomb.tries--;
        delay(5 * 1000);
        //Serial.println("Try Again!!");
        secondCodeSize = 0;
        secondCode = "";
        lcd.clear();
        gameStatus = TryCode;
      }
      break;
    }
    case Disarm: {
      bomb.bombStatus = disarm;
      youWin();
      //Serial.println("YOU WIN!");
      delay(60000);
      //delay(5 * 60000);
      gameStatus = Restart;
      break;
    }
    case Explode: {
      bomb.bombStatus = explode;
      beepOn(true);
      bombExploded();
      //Serial.println("Bomb Exploded");
      delay(60000);
      //delay(5 * 60000);
      gameStatus = Restart;
      break;
    }
    case ExplodeTryArming: {
      beepOn(true);
      bombExplodedToArming();
      delay(60000);
      //delay(5 * 60000);
      gameStatus = Restart;
      lcd.clear();
      break;
    }
    case Restart: {
      char key = keypad.getKey();
      restart();
      if (key) {
        beepingTimes(1, 50);
        if (key == 'D') {
          beepOn(false);
          ESP.restart();
        }
      }
      break;
    }
    default: {
      Serial.println("Something wrong!!");
      break;
    }
  }
}