#include"Bomb.h"
extern double getDistance(double, double);


Bomb::Bomb(int time, String code, int tries, int tryArming, int gameTime){
  this->time = time;
  this->tries = tries;
  this->tryArming = tryArming;
  this->code = code;
  this->players = 0;
  this->gameTime = gameTime * 60000;
  this->gps = false;
  this->sound = true;
  this->leds = true;
  this->smoke = false;
  this->latZone = 40.769726;
  this->longZone = -8.027784;
  this->maxDistance = 10.0;
  this->codeDiscovered = false;
};


String Bomb::checkGPS(){
  if (this->gps){
    return "Enable";
  }else {return "Disable";}
}

String Bomb::checkLeds() {
  if (this->leds){
    return "Enable";
  }else {return "Disable";}
}

String Bomb::checkSound() {
  if (this->sound){
    return "Enable";
  }else {return "Disable";}
}

String Bomb::checkSmoke() {
  if (this->smoke){
    return "Enable";
  }else {return "Disable";}
}

boolean Bomb::checkCode(String trycode){
  if (trycode == this->code){
    return true;
  }else{
    return false;
  }
};

boolean Bomb::isExplode(){
  if (this->tries < 0){
    return true;
  }else{
    return false;
  }
};

boolean Bomb::finishGame(unsigned long timeInit) {
  if (millis() - timeInit >= this->gameTime){
    return true;
  }
  return false;
}


boolean Bomb::isTimeOut(unsigned long timeInit) {
  if (millis() - timeInit >= this->time){
    return true;
  }
  return false;
}

int Bomb::getSize(){
  int size = this->code.length();
  return size;
};

boolean Bomb::isValidZone(){
  double distance = getDistance(this->latZone, this->longZone);
  if(distance <= bomb.maxDistance){
    return true;
  }else{
    return false;
  }
};



