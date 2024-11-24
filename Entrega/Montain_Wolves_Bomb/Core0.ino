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
    if(gps.satellites.value() < 1) {
      display.clearDisplay();
    }
    if(getNewData()) {
      if(gps.satellites.value() > 3) {
        SerialGPSData();
        printDisplayData();
      }
    }
    vTaskDelay(pdMS_TO_TICKS(10));
  }
}






