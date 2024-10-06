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
void core_1();

String code = "";
String secondCode = "";
int codeSize = 0;
int secondCodeSize = 0;
int minutesAnterior = bomb.time / 1000;
int secondsAnterior = 59;

unsigned long int bombTime_millisAnterior = 0;
unsigned long int clock_millisAnterior = 0;
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
      printBluetoothChoice();
      char key = keypad.getKey();
      if (key == 'A'){
        lcd.clear();
        String message = "";
        Serial.println("Bluetooth configuration!");
        printBluetoothConfig();
        bluetoothConfig(BT);
        lcd.clear();
        gameStatus = Prepared;
      }
      if (key == 'D'){
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
      insertCode();

      char key = keypad.getKey();
      if(key){
        if(key == 'D' && bomb.tryArming > 0 && codeSize > 0){
          if(code == bomb.code){
            //Serial.println("Codigo inserido com sucesso!");
            //Serial.print("code size "); Serial.println(codeSize);
            gameStatus = TryCode;
            Serial.println("https://www.google.com/maps/place/40.769838,-8.026673");
            timeMin = bomb.time / 60000;
            timeSec = 0;
            lcd.clear();
          }else{
            lcd.clear();
            tryAgain();
            bomb.tryArming--;
            code = "";
            codeSize = 0;
            if (bomb.tryArming == 0){
              lcd.clear();
              gameStatus = ExplodeTryArming;
            }else{
              delay(5000);
              }
            }
        }else if (key == 'C' && codeSize > 0){
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
      printDigit(secondCode);
      Serial.println(bomb.time);
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
      youWin();
      Serial.println("YOU WIN!");
      delay(2 * 60000);
      //delay(5 * 60000);
      gameStatus = Restart;
      break;
    }
    case Explode: {
      bombExploded();
      //Serial.println("Bomb Exploded");
      delay(2 * 60000);
      //delay(5 * 60000);
      gameStatus = Restart;
      break;
    }
    case ExplodeTryArming: {
      bombExplodedToArming();
      delay(2 * 60000);
      //delay(5 * 60000);
      gameStatus = Restart;
      break;
    }
    case Restart: {
      char key = keypad.getKey();
      restart();
      if (key) {
        if (key == 'D') {
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