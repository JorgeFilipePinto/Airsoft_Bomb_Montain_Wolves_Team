extern boolean setupFinish;
extern GameStatus gameStatus;
extern boolean discovoredCode;
extern unsigned long int bombTime_millisAnterior;
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
      gradienteMovendo();
      //fillSolidColor(CRGB::Black);
      break;
    }
    case Prepared: {
      luzesDancantes();
      fillSolidColor(CRGB::Black);
      break;
    }
    case ReadyToArm: {

      break;
    }
    case TryCode: {

        cor = 22;
        respiracao(cor, bomb.speedLight[4]);
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
      cor = 100;
      respiracao(cor, bomb.speedLight[4]);
      fillSolidColor(CRGB::Black);
      break;
    }
    case Explode: {
      cor = 22;
      respiracao(cor, bomb.speedLight[4]);
      fillSolidColor(CRGB::Black);
      break;
    }
    case ExplodeTryArming: {
      cor = 22;
      respiracao(cor, bomb.speedLight[4]);
      fillSolidColor(CRGB::Black);
      break;
    }
    default: {
      Serial.println("Something wrong!!");
      break;
    }
  }
}
