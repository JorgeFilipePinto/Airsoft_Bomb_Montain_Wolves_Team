extern void menuCore0();
extern void getData();
extern void printData();
extern void printNoData();
extern boolean getNewData();
extern void NoData();
extern void printDisplayData();

void gpsTracker(void * pvParameters) {
  for(;;) {

    //menuCore0();

    //If newData is true
    if(getNewData()) {
      Serial.println(gps.satellites.value());
      Serial.print("LAT=");  Serial.println(gps.location.lat(), 6);
      Serial.print("LONG="); Serial.println(gps.location.lng(), 6);
      Serial.print("ALT=");  Serial.println(gps.altitude.meters());
      Serial.print("Time= "); Serial.print(gps.time.hour()+1); Serial.print(":"); Serial.print(gps.time.minute()); Serial.print(":"); Serial.println(gps.time.second());
      Serial.print("Date= "); Serial.println(gps.date.value());
      Serial.print("Hdop value: "); Serial.println(gps.hdop.value());
      display.clearDisplay();
      display.setTextColor(SSD1306_WHITE);

    if (gps.location.isValid() == 1) {
      printDisplayData();
    }
    else {
      NoData();
      }  
    }
  }
}