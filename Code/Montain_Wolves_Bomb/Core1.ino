extern void printBluetoothChoice();
extern void bluetoothConfig();
extern void invalidZone();
extern void availableZone();
extern void insertCode();
extern void correctCode();
extern void tryAgain();
extern void youWin();
extern void bombArmed();
extern void printDigit(String);
extern void printCode(String);
extern void bombExploded();
extern void bombExplodedToArming();
void core_1();

boolean discovoredCode = false;
String code = "";
String secondCode = "";
int codeSize = 0;
int secondCodeSize = 0;
int minutesAnterior = bomb.time / 1000;
int secondsAnterior = 59;

unsigned long int bombTime_millisAnterior = 0;
unsigned long int clock_millisAnterior = 0;
int count = 0;

void core_1(){

  switch(gameStatus){
    case Configuration: {
      printBluetoothChoice();
      char key = keypad.getKey();
      if (key == 'A'){
        lcd.clear();
        String message = "";
        Serial.println("Bluetooth configuration!");
        bluetoothConfig();
        bluetoothConfig(BT);
        gameStatus = Prepared;
        lcd.clear();
      }else if (key == 'D'){
        bomb.time = 120000;
        bomb.tries = 3;
        bomb.tryArming = 3;
        bomb.code = "123";
        lcd.clear();
        gameStatus = Prepared;
      }

      break;
    }
    case Prepared: {
      if(bomb.isValidZone()){
        availableZone();
        lcd.clear();
        gameStatus = ReadyToArm;  
      }else{
        invalidZone();
        lcd.clear();
      }
      break;
    }
    case ReadyToArm: {

      insertCode();
      
      char key = keypad.getKey();
      if(key){
        if(key == 'D' & bomb.tryArming > 0){
          if(code == bomb.code){
            Serial.println("Codigo inserido com sucesso!");
            Serial.print("code size "); Serial.println(codeSize);
            gameStatus = TryCode;
            bombTime_millisAnterior = millis();
            clock_millisAnterior = millis();
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
        }else if (key == 'C' & codeSize > 0){
          lcd.clear();
          codeSize--;
          if (codeSize > 0) {
          String tempCode = code.substring(0, code.length() - 1);
          code = tempCode;
          printCode(code);
          }else { 
            code = "";
          }
        }else{
          code += key;
          codeSize++;
          Serial.print("Digit Insert "); Serial.println(key);

          printDigit(code);
        }
      }
      break;
    }
    case TryCode: {
      if (millis() - bombTime_millisAnterior >= bomb.time){
        gameStatus = Explode;
      }else if (millis() - clock_millisAnterior >= 1000){
        clock_millisAnterior = millis();
        secondsAnterior--;
        lcd.setCursor(4, 1);
        lcd.print(minutesAnterior);
        lcd.print(":");
        lcd.print(secondsAnterior);
        count++;
        if(count == 60){
          secondsAnterior = 59;
          minutesAnterior--;
          count = 0;
        }
      }
      bombArmed();
      char key = keypad.getKey();
      if (key){
        if (key == 'D' & secondCodeSize > 0){
          gameStatus = VerifyCode;
          lcd.clear();
        }else if (key == 'C' & secondCodeSize > 0){
          lcd.clear();
          secondCodeSize--;
          if (secondCodeSize > 0) {
            String tempCode = secondCode.substring(0, secondCode.length() - 1);
            secondCode = tempCode;
            printCode(secondCode);
          }else{
            secondCode = "";
          }
          }else{
            secondCode += key;
            Serial.print("Digit Insert "); Serial.println(key);
            secondCodeSize++;
            Serial.print("Faltam "); Serial.println(secondCodeSize);
            printDigit(secondCode);
        }
      }
      break;
    }
    case VerifyCode: {
      discovoredCode = bomb.checkCode(secondCode);
      if(discovoredCode){
        correctCode();
        Serial.println("correct code!");
        gameStatus = Disarm;
      } else if (bomb.tries == 0){
        gameStatus = Explode;
      }else{
        tryAgain();
        bomb.tries--;
        Serial.println("Try Again!!");
        codeSize = 0;
        gameStatus = TryCode;
        secondCode = "";
        delay(5000);
        lcd.clear();
      }
      break;
    }
    case Disarm: {
      youWin();
      Serial.println("YOU WIN!");

      delay(10000);
      gameStatus = ReadyToArm;
      break;
    }
    case Explode: {
      bombExploded();
      Serial.println("Bomb Exploded");

      delay(10000);
      gameStatus = ReadyToArm;
      break;
    }
    case ExplodeTryArming: {
      bombExplodedToArming();

      delay(10000);
      gameStatus = ReadyToArm;
      break;
    }
    default: {
      Serial.println("Something wrong!!");
      break;
    }
  }


}