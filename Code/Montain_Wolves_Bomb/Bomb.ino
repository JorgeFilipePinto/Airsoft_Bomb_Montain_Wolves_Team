#include"Bomb.h"
extern double getDIstance(double, double);

Bomb::Bomb(int time, String code, int tries){
  this->time = time;
  this->tries = tries;
  this->tryArming = 3;
  this->code = code;
  this->players = 0;
  this->gameTime = 30000;
  this->gps = false;
  this->sound = false;
  this->leds = false;
  this->smoke = false;
  this->speedLight[4] = 20, 50, 100, 255;
  this->latZone = 0.0;
  this->longZone = 0.0;
  this->maxDistance = 20.0;
};

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

int Bomb::getSize(){
  int size = this->code.length();
  return size;
};

boolean Bomb::isValidZone(){
  double distance = getDistance(bomb.latZone, bomb.latZone);
  if(distance <= bomb.maxDistance){
    return true;
  }else{
    return false;
  }
};
void Bomb::gametime(int time){
  this->gameTime = time;
}
void Bomb::setTimeBomb(int time){
  this->time = time;
};

void Bomb::setCode(String code){
 this->code = code;
};

boolean Bomb::rigthSize(String code){
  if (code.length() == this->players){
    return true;
  }else { return false;}
}

void Bomb::setPlayers(int players){
  this->players = players;
};

