extern boolean setupFinish;
extern unsigned long int bombTime_millisAnterior;
extern void fillSolidColor(CRGB);
void menuCore0();



void menuCore0(){

  while(!setupFinish){
    //cor = random(1, 255);
    respiracao(22, 20);
    //fillSolidColor(CRGB::Black);
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

      break;
    }
    case armed: {
        cor = 22;
        respiracao(cor, bomb.speedLight[3]);
      break;
    }
    case disarm: {
      cor = 100;
      respiracao(cor, bomb.speedLight[3]);
      break;
    }
    case explode: {
      cor = 22;
      respiracao(cor, bomb.speedLight[3]);
      break;
    }
    default: {
      Serial.println("Something wrong!!");
      break;
    }
  }
};
