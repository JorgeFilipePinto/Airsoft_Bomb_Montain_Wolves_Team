extern boolean isNum(char);
String _code;
String _players;

void manuallyConfig();
char tempKey;

String playersNum = "";
enum ConfigMan {
  BombTime,
  PlayersNum,
  InsertCode,
};

ConfigMan configMan = BombTime;

void manuallyConfig(){
  switch(configMan){
    case PlayersNum: {
      char key = keypad.getKey();
      if(key) {
        if (isNum(key)) {
          _players += key;
        }
        
      }
      break;
    }
    case BombTime: {
      char key = keypad.getKey();
      if(key) {
        if(isNum(key)) {
          _code += key;
        }
      }
      

      break;
    }
    case InsertCode: {
      char key = keypad.getKey();
      if(key) {
        if (key == 'D'){

        }else if ('C') {

        }
      }
      break;
    }
  }
}




