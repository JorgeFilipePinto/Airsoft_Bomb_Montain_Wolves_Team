extern boolean setupFinish;
extern unsigned long int bombTime_millisAnterior;
extern void fillSolidColor(CRGB);
void menuCore0();



void menuCore0(){

  while(!setupFinish){
    cor = 22;
    respiracao(cor, 20);
  }
  switch(bomb.bombStatus){
    case initialize: {
      gradienteMovendo();
      break;
    }
    case configuration: {
      bomb.leds ? luzesDancantes() : fillSolidColor(CRGB::Black);
      break;
    }
    case readyToArm: {
      fillSolidColor(CRGB::Black);
      break;
    }
    case armed: {
        cor = 22;
        bomb.leds ? respiracao(cor, bomb.speedLight) : fillSolidColor(CRGB::Black);
      break;
    }
    case disarm: {
      cor = 100;
      bomb.leds ? respiracao(cor, bomb.speedLight) : fillSolidColor(CRGB::Black);
      break;
    }
    case explode: {
      cor = 22;
      bomb.leds ? respiracao(cor, bomb.speedLight) : fillSolidColor(CRGB::Black);
      break;
    }
    default: {
      Serial.println("Something wrong!!");
      break;
    }
  }
};
