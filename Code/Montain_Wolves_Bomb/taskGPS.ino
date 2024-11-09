void GPSData (void * paramteter) {
  while (1) {
    if (xMutex != NULL && bomb.gps) {
      boolean newData = false;
      for (unsigned long start = millis(); millis() - start < 1000;) {
        while (neogps.available()) {
          if (gps.encode(neogps.read())) {
            newData = true;
            break;
          }
        }
      }
      if (newData) {
        display.clearDisplay();
        display.setTextSize(1);
        display.setCursor(2, 5);
        display.print("Lat: "); display.print(gps.location.lat(),6);
        display.setCursor(2, 15);
        display.print("Long: "); display.print(gps.location.lng(),6);
        display.setCursor(2, 25);
        display.print("SAT: "); display.print(gps.satellites.value());
        display.setCursor(2, 35);
        display.print("speed: "); display.print(gps.speed.kmph());
        display.setCursor(2, 45);
        display.print("hdop: "); display.print(gps.hdop.value());
        display.setCursor(2, 55);
        double distance = TinyGPSPlus::distanceBetween(gps.location.lat(), gps.location.lng(), bomb.latZone, bomb.longZone);
        display.print("Dist: "); display.print(distance);
        display.display();
        newData = false;
      }
      xSemaphoreGive(xMutex);
    }
    vTaskDelay(1000/portTICK_PERIOD_MS);
  }
}