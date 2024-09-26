
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
CodeStatus codeStatus = InsertCode;

void setup(){
  Serial.begin(115200);
  pinMode(BUZZER, OUTPUT);
}

void loop(){
  switch(codeStatus){
    case InsertCode: {
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
        }else{
          code += key;
          codeSize++;
          Serial.print("Digit Insert ");
          Serial.println(key);
        }
      }
      break;
    }
    case TryCode: {
      char key = keypad.getKey();
      funcTone(1000);
      if(key){
        noTone(BUZZER);
        tone(BUZZER, 500);
        delay(100);
        noTone(BUZZER);
        if(codeSize > 0){
          secondCode += key;
          Serial.print("Digit Insert ");
          Serial.println(key);
          codeSize--;
          Serial.print("Faltam ");
          Serial.println(codeSize);
        }
      }
      if(codeSize == 0){
        codeStatus = VerifyCode;
        }
      break;
    }
    case VerifyCode: {
      if(code == secondCode){
        Serial.println("correct code!");
        codeStatus = InsertCode;
      }else{
        Serial.println("Try Again!!");
        codeSize = code.length();
        codeStatus = TryCode;
        secondCode = "";
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




