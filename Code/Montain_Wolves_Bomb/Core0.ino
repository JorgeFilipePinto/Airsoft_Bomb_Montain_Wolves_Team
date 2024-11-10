//extern void menuCore0();
extern void respiracao(byte, accum88);
extern void gradienteOndas();
extern void fillSolidColor(CRGB);
extern void gradienteMovendo();
extern void luzesDancantes();
extern void cometa();
extern void getData();
extern void SerialGPSData();
extern boolean getNewData();
extern void clearAll();
extern void NoData();
extern void printDisplayData();

void gpsTracker(void * pvParameters) {
  for(;;) {
    switch(bomb.bombStatus){
      case initialize: {
        if(intro) {
          player.volume(30);
          player.play(1);
          intro = false;
        }
        bomb.leds ? cometa() : fillSolidColor(CRGB::Black);
        break;
      }
      case configuration: {
        cor = 100;
        bomb.leds ? respiracao(22, bomb.speedLight) : fillSolidColor(CRGB::Black);
        //bomb.gps ? NoData() : clearAll();
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
  }
}





