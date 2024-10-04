boolean manuallyConfigured();
extern boolean isNum(char);
extern void printPlayers();
extern void printTimeGame();
extern void printTimeBomb();
extern void printBombCode();
extern void printDigit(String);
extern void printSmoke(String);
extern void printSound(String);
extern void printLeds(String);
extern void printGPS(String);
extern void printConfirmConfig();

enum Config {
  Players,
  TimeGame,
  TimeBomb,
  BombCode,
  GPS,
  Leds,
  Sound,
  Smoke,
  Confirm
};

boolean manuallyConfigured(){
  Config config = Players;
  String _players = "";
  String _timeGame = "30";
  String _timeBomb = "15";
  String _code = "";

  char key;
  while (!Configured) {
    switch(config){
      case Players: {
        printPlayers();
        printDigit(_players);
        key = keypad.getKey();
        if (key) {
          if (isNum(key)) {
            lcd.clear();
            _players += key;
            printDigit(_players);
            }
          if (key == 'C' && _players.length() > 0) {
            lcd.clear();
            _players = _players.substring(0, _players.length() - 1);
            printDigit(_players);
            }
          if (key == 'D' && _players.length() > 0) {
            lcd.clear();
            config = TimeGame;
            bomb.players = _players.toInt();
            }
          }
        break;
        }
        case TimeGame: {
          printTimeGame();
          printDigit(_timeGame);
          key = keypad.getKey();
          if (key) {
            if (isNum(key)) {
              lcd.clear();
              _timeGame += key;
              printDigit(_timeGame);
            }
            if (key == 'C' && _timeGame.length() > 0) {
              lcd.clear();
              _timeGame = _timeGame.substring(0, _timeGame.length() - 1);
              printDigit(_timeGame);
            }
            if (key == 'D' && _timeGame.length() > 0) {
              bomb.gameTime = _timeGame.toInt();
              config = TimeBomb;
              lcd.clear();
            }
          }
          break;
        }
        case TimeBomb : {
        printTimeBomb();
        printDigit(_timeBomb);
        key = keypad.getKey();
        if (key) {
          if (isNum(key)) {
            lcd.clear();
            _timeBomb += key;
            printDigit(_timeBomb);
          }
          if (key == 'C' && _timeBomb.length() > 0) {
            lcd.clear();
            _timeBomb = _timeBomb.substring(0, _timeBomb.length() - 1);
            printDigit(_timeBomb);
          }
          if (key == 'D' && _timeBomb.length() > 0) {
            bomb.time = _timeBomb.toInt();
            config = BombCode;
            lcd.clear();
          }
        }
        break;
        }
        case BombCode: {
        printBombCode();
        printDigit(_code);
        key = keypad.getKey();
        if (key) {
          if (isNum(key)) {
            lcd.clear();
            _code += key;
            printDigit(_code);
            }
          if (key == 'C' && _code.length() > 0) {
            lcd.clear();
            _code = _code.substring(0, _code.length() - 1);
            printDigit(_code);
            }
          if (key == 'D' && _code.length() > 0 && _code.length() == _players.toInt()) {
            bomb.code = _code;
            config = GPS;
            lcd.clear();
            }
          }
          break;
        }
        case GPS: {
          printGPS(bomb.checkGPS());
          key = keypad.getKey();
          if (key) {
            if (key == 'B' && bomb.gps) {
              lcd.clear();
              bomb.gps = false;
            }
            if (key == 'A' && !bomb.gps) {
              lcd.clear();
              bomb.gps = true; 
            }
            if (key == 'D') {
              config = Leds;
              lcd.clear();
            }
          }
          break;
        }
        case Leds: {
          printLeds(bomb.checkLeds());
          key = keypad.getKey();
          if (key) {
            if (key == 'B' && bomb.leds) {
              lcd.clear();
              bomb.leds = false;
            }
            if (key == 'A' && !bomb.leds) {
              lcd.clear();
              bomb.leds = true; 
            }
            if (key == 'D') {
              config = Sound;
              lcd.clear();
            }
          }
          break;
        }
        case Sound: {
          printSound(bomb.checkSound());
          key = keypad.getKey();
          if (key) {
            if (key == 'B' && bomb.sound) {
              lcd.clear();
              bomb.sound = false;
            }
            if (key == 'A' && !bomb.sound) {
              lcd.clear();
              bomb.sound = true; 
            }
            if (key == 'D') {
              config = Smoke;
              lcd.clear();
            }
          }
          break;
        }
        case Smoke: {
          printSmoke(bomb.checkSmoke());
          key = keypad.getKey();
          if (key) {
            if (key == 'B' && bomb.smoke) {
              lcd.clear();
              bomb.smoke = false;
            }
            if (key == 'A' && !bomb.smoke) {
              lcd.clear();
              bomb.smoke = true; 
            }
            if (key == 'D') {
              config = Confirm;
              lcd.clear();
            }
          }
          break;
        }
        case Confirm: {
          printConfirmConfig();
          key = keypad.getKey();
          if (key) {
            if (key == 'C') {
              lcd.clear();
              config = Players;
            }
            if (key == 'D') {
              lcd.clear();
              Configured = true;
            }
          }
          break;
        }
      }
    }
    return true;
  }