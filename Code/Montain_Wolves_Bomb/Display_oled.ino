
extern int fuseTime;
void printData();
void printNoData();
void print_speed();

void printData(){
  Serial.println(gps.satellites.value());
  Serial.print("LAT=");  Serial.println(gps.location.lat(), 6);
  Serial.print("LONG="); Serial.println(gps.location.lng(), 6);
  Serial.print("ALT=");  Serial.println(gps.altitude.meters());
  Serial.print("Time= "); Serial.print(gps.time.hour() + fuseTime); Serial.print(":"); Serial.println(gps.time.minute());
  Serial.print("Date= "); Serial.println(gps.date.value());
  Serial.print("Hdop value: "); Serial.println(gps.hdop.value());
  print_speed();
}


void printNoData(){
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.setTextSize(3);
  display.print("No Data");
  display.setCursor(50,50);
  display.setTextSize(1);
  display.print("Hdop= "); display.print(gps.hdop.value());
  display.display();
}


void print_speed(){
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  
  if (gps.location.isValid() == 1)
  {
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
    display.print("ALT: "); display.print(gps.altitude.meters(), 0);
    display.display();
  }
  else
  {
    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.setTextSize(3);
    display.print("No Data");
    display.setCursor(50,50);
    display.setTextSize(1);
    display.print("Hdop= "); display.print(gps.hdop.value());
    Serial.println();
    display.display();
  }  
}





