#include"Bomb.h"


Bomb::Bomb(int time, String code, int tries){
  this->time = time;
  this->tries = tries;
  this->code = code;
  this->gps = false;
  this->sound = false;
  this->leds = false;
  this->smoke = false;
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

