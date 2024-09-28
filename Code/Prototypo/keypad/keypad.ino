#include <LCD-I2C.h>
#include <Wire.h>
#include <Keypad.h>

#define BUZZER 0

void funcTone(int);

unsigned long oldTone = millis();
unsigned long newTone;

String code = "";
String secondCode = "";
int codeSize = 0;
enum CodeStatus {
  InsertCode,
  TryCode,
  VerifyCode};
  

const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {13, 12, 14,27}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {26, 25, 33, 32}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
LCD_I2C lcd(0x27, 16, 2);
CodeStatus codeStatus = InsertCode;

void setup(){
  Serial.begin(115200);
  Serial.println("Montain Wolves");
  Serial.println("Airsoft Bomb");
  pinMode(BUZZER, OUTPUT);
  Wire.begin();
  lcd.begin(&Wire);
  lcd.display();
  lcd.backlight();
  lcd.setCursor(1,0);
  lcd.print("Montain Wolves");
  lcd.setCursor(2,1);
  lcd.print("Airsoft Bomb");
  char key;
  while(key != 'D'){
    key = keypad.getKey();
    lcd.setCursor(9,0);
    lcd.print("Montain Wolves");
    lcd.setCursor(5,1);
    lcd.print(F("Press D to continue!!"));
    for(int i = 0; i < 10; i++){
      key = keypad.getKey();
      if(key == 'D'){
        break;
      }
      lcd.scrollDisplayLeft();
      delay(300);
    }
    lcd.clear();
  }
}

void loop(){
  switch(codeStatus){
    case InsertCode: {
      lcd.setCursor(0,0);
      lcd.print("Insert Bomb Code");
      char key = keypad.getKey();
      if(key){
        tone(BUZZER, 1000);
        delay(100);
        noTone(BUZZER);
        if(key == 'D'){
          Serial.println("Codigo inserido com sucesso!");
          Serial.print("code size ");
          Serial.println(codeSize);
          codeStatus = TryCode;
          oldTone = millis();
          noTone(BUZZER);
          lcd.clear();
        }else if (key == 'C' & codeSize > 0){
          lcd.clear();
          codeSize--;
          String tempCode = code.substring(0,code.length()-1);
          code = tempCode;
          lcd.setCursor(4,1);
          lcd.print(code);
        }else{
          lcd.setCursor(codeSize + 4, 1);
          code += key;
          codeSize++;
          Serial.print("Digit Insert ");
          Serial.println(key);
          lcd.print(key);
        }
      }
      break;
    }
    case TryCode: {
      lcd.setCursor(2,0);
      lcd.print("Bomb Armed!");
      char key = keypad.getKey();
      funcTone(1000);
      if(key){
        noTone(BUZZER);
        tone(BUZZER, 500);
        delay(100);
        noTone(BUZZER);
        if(codeSize > 0){
          lcd.setCursor(codeSize + 4, 1);
          secondCode += key;
          Serial.print("Digit Insert ");
          Serial.println(key);
          codeSize--;
          Serial.print("Faltam ");
          Serial.println(codeSize);
          lcd.print(key);
        }
      }
      if(codeSize == 0){
        codeStatus = VerifyCode;
        lcd.clear();
        }
      break;
    }
    case VerifyCode: {
      if(code == secondCode){
        lcd.setCursor(1,0);
        lcd.print("Correct Code!");
        lcd.setCursor(4,1);
        lcd.print("YOU WIN!");
        Serial.println("correct code!");
        delay(5000);
        lcd.clear();
        codeStatus = InsertCode;
      }else{
        lcd.setCursor(3,0);
        lcd.print("Try Again!!");
        Serial.println("Try Again!!");
        codeSize = code.length();
        codeStatus = TryCode;
        secondCode = "";
        delay(5000);
        lcd.clear();
      }
      break;
    }
  }

  /*
  char key = keypad.getKey();
  if(key == 'D'){
    for(char digit : code){
      Serial.println(digit);
    }
  }else if (key){
    Serial.println(key);
    code += key;
    Serial.println(code);
  }*/
}


void funcTone(int time){
  newTone = millis();
  if(newTone - oldTone < 2000){
    if(newTone - oldTone < time){
      tone(BUZZER, 1500);
    }else{
      noTone(BUZZER);
    }
  }else{
    oldTone = millis();
  }
}




