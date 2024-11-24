extern void teamIntro();
extern void bluetoothInit();
extern void gradienteOndas();
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
  Intro,
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

GameStatus gameStatus = Intro;

void core_1(){
  switch(gameStatus){
    case Intro: {
      fillSolidColor(CRGB::Blue);
      char key = keypad.getKey();
      key ? beepingTimes(1, 50): void();
      teamIntro();
      if (key == 'D') {
        lcd.clear();
        gameStatus = Configuration;
        fillSolidColor(CRGB::Black);
      }
      break;
    }

    case Configuration: {
      bomb.bombStatus = configuration;
      printBluetoothChoice();
      char key = keypad.getKey();
      if (key == 'A'){
        beepingTimes(1, 50);
        lcd.clear();
        String message = "";
        bluetoothInit();
        printBluetoothConfig();
        bluetoothConfig(BT);
        lcd.clear();
        gameStatus = Prepared;
        gameTimeLast = millis();
      }
      if (key == 'D'){
        beepingTimes(1, 50);
        lcd.clear();
        if (manuallyConfigured()) {
          gameStatus = Prepared;
        }
      }
      break;
    }

    case Prepared: {
      if(bomb.gps) {
        if(bomb.isValidZone()){
          availableZone();
          char key = keypad.getKey();
          if(key == 'D') {
            gameStatus = ReadyToArm;
            lcd.clear();
          }
        }else{
          lcd.setCursor(0,0);
          invalidZone();
        }
      } else {
        gameStatus = ReadyToArm;
      }
      break;
    }

    case ReadyToArm: {
      bomb.bombStatus = readyToArm;
      if(!bomb.isValidZone() && bomb.gps) {
        gameStatus = Prepared;
      }
      if (millis() - gameTimeLast >= bomb.gameTime) {
        bomb.bombStatus = explode;
        gameStatus = Explode;
        lcd.clear();
        break;
      }
      insertCode();
      char key = keypad.getKey();
      if(key){
        beepingTimes(1, 50);
        if(key == 'D' && bomb.tryArming > 0 && codeSize > 0){
          if(code == bomb.code){
            gameStatus = TryCode;
            Serial.println("https://www.google.com/maps/place/" + String(bomb.latZone,6) + "," + String(bomb.longZone,6));
            lastBeep = millis();
            timeMin = bomb.time / 60000;
            bombTime = bomb.time;
            timeSec = 0;
            lcd.clear();
            bomb.bombStatus = armed;
          }else{
            lcd.clear();
            wrongCode();
            tryAgain();
            delay(500);
            bomb.tryArming--;
            code = "";
            codeSize = 0;
            delay(500);
            lcd.clear();
            if (bomb.tryArming == 0){
              lcd.clear();
              gameStatus = ExplodeTryArming;
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
          printDigit(code);
        }
      }
      break;
    }

    case TryCode: {
      bomb.leds ? respiracao(22, bomb.speedLight) : fillSolidColor(CRGB::Black);
      if (millis() - gameTimeLast >= bomb.gameTime) {
        bomb.bombStatus = explode;
        gameStatus = Explode;
        lcd.clear();
        break;
      }
      beepBomb();
      printDigit(secondCode);
      bombArmed();
      if (bomb.time > 0) {
        if (timeSec == 0) {
          bombTime_millisAnterior = millis();
          timeMin--;
          timeSec = 59;
          //lcd.clear();
        } else if (millis() - bombTime_millisAnterior >= 1000) {
          bombTime_millisAnterior = millis();
          timeSec--;
          bomb.time -= 1000;
          //lcd.clear();
        }
        if (timeMin > 0 || timeSec > 0){
          if(timeSec == 9 || timeMin == 9) {lcd.clear();}
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
          secondCodeSize++;
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
        bomb.leds ? fillSolidColor(CRGB::Red) : fillSolidColor(CRGB::Black);
        (bomb.tries > 0) ? delay(5 * 1000) : delay(0);
        fillSolidColor(CRGB::Black);
        secondCodeSize = 0;
        secondCode = "";
        lcd.clear();
        gameStatus = TryCode;
      }
      break;
    }

    case Disarm: {
      bomb.leds ? fillSolidColor(CRGB::Green) : fillSolidColor(CRGB::Black);
      bomb.bombStatus = disarm;
      youWin();
      beepOn(bomb.sound);
      char key = keypad.getKey();
      if (key == 'D') {
        gameStatus = Restart;
        lcd.clear();
        fillSolidColor(CRGB::Black);
        delay(200);
      }
      break;
    }

    case Explode: {
      bomb.leds ? fillSolidColor(CRGB::Red) : fillSolidColor(CRGB::Black);
      bomb.bombStatus = explode;
      beepOn(bomb.sound);
      bombExploded();
      char key = keypad.getKey();
      if (key == 'D') {
        gameStatus = Restart;
        lcd.clear();
        fillSolidColor(CRGB::Black);
        delay(200);
      }
      break;
    }

    case ExplodeTryArming: {
      bomb.leds ? fillSolidColor(CRGB::Red) : fillSolidColor(CRGB::Black);
      beepOn(bomb.sound);
      bombExplodedToArming();
      char key = keypad.getKey();
      if (key == 'D') {
        lcd.clear();
        gameStatus = Restart;
        fillSolidColor(CRGB::Black);
        delay(200);
      }
      break;
    }

    case Restart: {
      char key = keypad.getKey();
      restart();
      digitalWrite(beep, LOW);
      if (key) {
        beepingTimes(1, 50);
        if (key == 'D') {
          fillSolidColor(CRGB::Black);
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