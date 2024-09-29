extern boolean setupFinish;
extern GameStatus gameStatus;
extern boolean discovoredCode;
extern void fillSolidColor(CRGB);
void menuCore0();

void menuCore0(){
  while(!setupFinish){
    cor = random(1, 255);
    respiracao(cor, 20);
    fillSolidColor(CRGB::Black);
  }
  switch(gameStatus){
    case Configuration: {

      break;
    }
    case Prepared: {

      break;
    }
    case ReadyToArm: {

      break;
    }
    case TryCode: {
      cor = 22;
      respiracao(cor, bomb.speedLight[0]);
      fillSolidColor(CRGB::Black);
      break;
    }
    case VerifyCode: {
      if(discovoredCode){
        fillSolidColor(CRGB::Green);
      }else{
        fillSolidColor(CRGB::Red);
      }
      break;
    }
    case Disarm: {

      break;
    }
    case Explode: {

      break;
    }
    default: {
      Serial.println("Something wrong!!");
      break;
    }
  }
}
