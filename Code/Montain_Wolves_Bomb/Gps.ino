int fuseTime = 1;
void getData();
double getDistance();
void SerialGPSData();
void clearAll();


double getDistance(double latZone, double longZone){
  double distance = TinyGPSPlus::distanceBetween(gps.location.lat(), gps.location.lng(), latZone, longZone);
  return distance;
}


boolean getNewData() {
  boolean newData = false;
  if (start - millis() >= 1000) {
    //Serial.print("inicio: "); Serial.println(millis());
    while (neogps.available())
    {
      if (gps.encode(neogps.read())) {
        newData = true;
        break;
      }
    }
    //Serial.print("Fim: "); Serial.println(millis());
  }
  return newData;
}


void SerialGPSData() {
  Serial.println(gps.satellites.value());
  Serial.print("LAT=");  Serial.println(gps.location.lat(), 6);
  Serial.print("LONG="); Serial.println(gps.location.lng(), 6);
  Serial.print("ALT=");  Serial.println(gps.altitude.meters());
  Serial.print("Time= "); Serial.print(gps.time.hour()+1); Serial.print(":"); Serial.print(gps.time.minute()); Serial.print(":"); Serial.println(gps.time.second());
  Serial.print("Date= "); Serial.println(gps.date.value());
  Serial.print("Hdop value: "); Serial.println(gps.hdop.value());
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
}

void printDisplayData() {
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
}

void clearAll() {
  display.clearDisplay();
  delay(1000);
  display.display();
}


void NoData() {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(2, 5);
  display.print("Lat: ");
  display.setCursor(2, 15);
  display.print("Long: ");
  display.setCursor(2, 25);
  display.print("SAT: ");
  display.setCursor(2, 35);
  display.print("speed: ");
  display.setCursor(2, 45);
  display.print("hdop: "); display.print(gps.hdop.value());
  display.setCursor(2, 55);
  display.print("Dist: ");
  display.display();
}
