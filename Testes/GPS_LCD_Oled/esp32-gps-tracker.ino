#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <TinyGPS++.h>


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

//On ESP32: GPIO-21(SDA), GPIO-22(SCL)
#define OLED_RESET -1 //Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C //See datasheet for Address
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define RXD2 16
#define TXD2 17
HardwareSerial neogps(1);
double lat2 = 40.769460;
double long2 = -8.027666;

TinyGPSPlus gps;

void setup() {
  Serial.begin(115200);
  //Begin serial communication Arduino IDE (Serial Monitor)

  //Begin serial communication Neo6mGPS
  neogps.begin(9600, SERIAL_8N1, RXD2, TXD2);
  
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  display.clearDisplay();
  display.display();
  delay(2000);

}

void loop() {
    
  boolean newData = false;
  for (unsigned long start = millis(); millis() - start < 1000;)
  {
    while (neogps.available())
    {
      if (gps.encode(neogps.read()))
      {
        newData = true;
      }
    }
  }

  //If newData is true
  if(newData == true)
  {
    newData = false;
    Serial.println(gps.satellites.value());
    Serial.print("LAT=");  Serial.println(gps.location.lat(), 6);
    Serial.print("LONG="); Serial.println(gps.location.lng(), 6);
    Serial.print("ALT=");  Serial.println(gps.altitude.meters());
    Serial.print("Time= "); Serial.print(gps.time.hour()+1); Serial.print(":"); Serial.println(gps.time.minute());
    Serial.print("Date= "); Serial.println(gps.date.value());
    Serial.print("Hdop value: "); Serial.println(gps.hdop.value());
    print_speed();
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
    display.display();
  }

}

void print_speed()
{
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
    
    /*
   //String gps_speed = String(gps.speed.kmph());
    display.setTextSize(1);
    
    display.setCursor(25, 5);
    display.print("Lat: ");
    display.setCursor(50, 5);
    display.print(gps.location.lat(),6);

    display.setCursor(25, 20);
    display.print("Lng: ");
    display.setCursor(50, 20);
    display.print(gps.location.lng(),6);

    display.setCursor(25, 35);
    display.print("Speed: ");
    display.setCursor(65, 35);
    display.print(gps.speed.kmph());
    
    display.setTextSize(1);
    display.setCursor(0, 50);
    display.print("SAT:");
    display.setCursor(25, 50);
    display.print(gps.satellites.value());

    display.setTextSize(1);
    display.setCursor(70, 50);
    display.print("ALT:");
    display.setCursor(95, 50);
    display.print(gps.altitude.meters(), 0);
    Serial.print("Distance= "); Serial.print(TinyGPSPlus::distanceBetween(gps.location.lat(), gps.location.lng(), lat2, long2));
    Serial.println();
    display.display();*/
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
