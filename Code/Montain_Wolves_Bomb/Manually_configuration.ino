extern String code;

void manuallyConfig();

String playersNum = "";
enum ConfigMan {
  BombTime,
  PlayersNum,
  InsertCode,
};

ConfigMan configMan = BombTime;

void manuallyConfig(){
  switch(configMan){
    case BombTime: {
      char key = keypad.getKey();
      if(key) {
        if (key == 'D'){

        }else if ('C') {

        }
        else if (key != 'C' && key != 'D' && key != 'A' && key != 'B' && key !='*' && key != '#'){

        }
      }
      break;
    }
    case PlayersNum: {
      char key = keypad.getKey();
      if(key) {
        if (key == 'D'){

        }else if ('C') {

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




