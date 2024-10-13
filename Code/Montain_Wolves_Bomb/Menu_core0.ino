extern boolean setupFinish;
extern unsigned long int bombTime_millisAnterior;
extern void fillSolidColor(CRGB);
void menuCore0();



void menuCore0(){

  while(!setupFinish){
    respiracao(22, 20);
  }
  switch(bomb.bombStatus){
    case initialize: {
      gradienteMovendo();
      break;
    }
    case configuration: {
      luzesDancantes();
      break;
    }
    case readyToArm: {
      fillSolidColor(CRGB::Black);
      break;
    }
    case armed: {
        cor = 22;
        respiracao(cor, bomb.speedLight);
      break;
    }
    case disarm: {
      cor = 100;
      respiracao(cor, bomb.speedLight);
      break;
    }
    case explode: {
      cor = 22;
      respiracao(cor, bomb.speedLight);
      break;
    }
    default: {
      Serial.println("Something wrong!!");
      break;
    }
  }
};
