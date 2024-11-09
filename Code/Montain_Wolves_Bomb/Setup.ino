extern void beepingTimes(int, int);

void setup_ori() {
  bomb.bombStatus = initialize;
  pinMode(beep, OUTPUT);
  beepingTimes(3, 250);
  Serial.begin(115200);
  
    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
      Serial.println(F("SSD1306 allocation failed"));
      for(;;); // Don't proceed, loop forever
      }

  Wire.begin();
  lcd.begin(&Wire);
  lcd.display();
  lcd.backlight();
  display.clearDisplay();
  display.display();

  neogps.begin(9600, SERIAL_8N1, RXD2, TXD2);
  
  BT.begin(device_name);

  FastLED.addLeds<WS2812B, PINO_FITA, GRB>(fita, NUM_LEDS_FITA);
  FastLED.setBrightness(200);

  delay(2000);

  display.display();
  Serial.printf("The device with name \"%s\" is started \nNow you can pai it with Bluetooth\n", device_name.c_str());
  Serial.print("MAC Address: "); Serial.println(BT.getBtAddressString());
  
  xMutex = xSemaphoreCreateMutex();

  xTaskCreatePinnedToCore (
    &GPSData,
    "GPSData",
    10000,
    NULL,
    1,
    NULL,
    0
  );

  xTaskCreatePinnedToCore(
    &gpsTracker,
    "Task2",
    10000,
    NULL,
    3,
    NULL,
    0
    );

  

}