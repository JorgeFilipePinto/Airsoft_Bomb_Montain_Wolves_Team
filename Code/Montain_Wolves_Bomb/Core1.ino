
extern void bluetoothConfig();
extern void invalidZone();
extern void availableZone();
extern void insertCode();
extern void correctCode();
extern void tryAgain();
extern void youWin();
extern void bombArmed();
extern void printDigit();
extern void printCode(String);
extern void bombExploded();
extern void bombExplodedToArming();
void core_1();

boolean discovoredCode = false;
String code = "";
String secondCode = "";
int codeSize = 0;

void core_1(){

  switch(gameStatus){
    case Configuration: {
      String message = "";
      Serial.println("Bluetooth configuration!");
      bluetoothConfig();
      bluetoothConfig(BT);
      gameStatus = Prepared;
      break;
    }
    case Prepared: {
      if(bomb.isValidZone()){
        availableZone();
        gameStatus = ReadyToArm;  
      }else{
        invalidZone();
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
            lcd.clear();
          }else{
            bomb.tryArming--;
            code = "";
            codeSize = 0;
            }
        }else if (key == 'C' & codeSize > 0){
          lcd.clear();
          codeSize--;
          if (codeSize > 0) {
          String tempCode = code.substring(0, code.length() - 1);
          code = tempCode;
          printCode(code);
          }
        }else{
          code += key;
          codeSize++;
          Serial.print("Digit Insert "); Serial.println(key);

          printDigit(key);
        }
      }
      if (bomb.tryArming == 0){
        gameStatus == ExplodeTryArming;
      }
      break;
    }
    case TryCode: {
      void bombArmed();
      char key = keypad.getKey();
      if(key){
        delay(100);
        if(codeSize > 0){
          secondCode += key;
          Serial.print("Digit Insert "); Serial.println(key);
          codeSize--;
          Serial.print("Faltam "); Serial.println(codeSize);
          printDigit(key);
        }
      }
      if(codeSize == 0){
        gameStatus = VerifyCode;
        lcd.clear();
        }
      break;
    }
    case VerifyCode: {
      discovoredCode = bomb.checkCode(secondCode);
      if(discovoredCode){
        correctCode();
        Serial.println("correct code!");
        gameStatus = Disarm;
      }else{
        tryAgain();
        bomb.tries--;
        Serial.println("Try Again!!");
        codeSize = bomb.getSize();
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
      break;
    }
    case Explode: {
      bombExploded();
      Serial.println("Bomb Exploded");
      break;
    }
    case ExplodeTryArming: {
      void bombExplodedToArming();
      break;
    }
    default: {
      Serial.println("Something wrong!!");
      break;
    }
  }
  delay(50);

}