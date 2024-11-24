extern boolean bluetoothConfigured;
extern void bombIsReady();
extern void beepingTimes(int, int);
extern void WaitSat();
extern void setNewCoordinates();
void bluetoothConfig(BluetoothSerial);
void bluetoothInit();

void bluetoothInit(){
  bomb.gps = false;
  bomb.sound = false;
  bomb.leds = false;
  bomb.smoke = false;
}

void bluetoothConfig(BluetoothSerial BT){
  String message = "";
  while(!bluetoothConfigured){
    (gps.satellites.value() < 3) ? fillSolidColor(CRGB::Red) : fillSolidColor(CRGB::Green);

    if (BT.available()) {
      char inComingChar = BT.read();
    if (inComingChar != '\n'){
      message += String (inComingChar);
    }
    else{
      message = "";
    }
    Serial.write(inComingChar);

  if (message.substring(0, 4) == "TEAM")
  {
    if(bomb.sound){beepingTimes(5, 50);}
    bomb.players = message.substring(4).toInt();
    Serial.print("\nPlayers: "); Serial.println(bomb.players);
    lcd.clear();
    lcd.setCursor(4,0);
    lcd.print("Players");
    lcd.setCursor(7, 1);
    lcd.print(String(bomb.players));
  }

  if (message.substring(0,5) == "TIMEG")
  {
    if(bomb.sound){beepingTimes(5, 50);}
    bomb.gameTime = message.substring(5).toInt() * 60000;
    Serial.print("\nGame Time: "); Serial.println(bomb.gameTime);
    lcd.clear();
    lcd.setCursor(3,0);
    lcd.print("Game Time");
    lcd.setCursor(2, 1);
    lcd.print(String(bomb.gameTime / 60000));
    lcd.setCursor(5, 1);
    lcd.print("Minutes");
  }

    if (message.substring(0,5) == "TIMEB")
  {
    if(bomb.sound){beepingTimes(5, 50);}
    bomb.time = message.substring(5).toInt() * 60000;
    Serial.print("\nGame Time: "); Serial.println(bomb.time);
    lcd.clear();
    lcd.setCursor(3,0);
    lcd.print("Bomb Time");
    lcd.setCursor(2, 1);
    lcd.print(String(bomb.time / 60000));
    lcd.setCursor(5, 1);
    lcd.print("Minutes");
  }

  if (message.substring(0,4) == "CODE")
  {
    if(bomb.sound){beepingTimes(5, 50);}
    bomb.code = message.substring(4);
    Serial.print("Bomb Code: "); Serial.println(bomb.code);
    lcd.clear();
    lcd.setCursor(3,0);
    lcd.print("Bomb Code");
    lcd.setCursor(4, 1);
    lcd.print("Defined");
  }

  if (message == "gpsON")
  {
    if(bomb.sound){beepingTimes(5, 50);}
    bomb.gps = true;
    Serial.println("\nGPS is ON!");
    lcd.clear();
    lcd.setCursor(6,0);
    lcd.print("GPS");
    lcd.setCursor(7, 1);
    lcd.print("ON");
  }

  if (message == "gpsOFF")
  {
    if(bomb.sound){beepingTimes(5, 50);}
    bomb.gps = false;
    Serial.println("\nGPS is OFF!");
    lcd.clear();
    lcd.setCursor(6,0);
    lcd.print("GPS");
    lcd.setCursor(6, 1);
    lcd.print("OFF");
  }

  if (message == "setCoordinates") {
    if(bomb.sound){beepingTimes(5, 50);}
    if(gps.satellites.value() > 5){
      bomb.latZone = gps.location.lat();
      bomb.longZone = gps.location.lng();
      setNewCoordinates();
    } else {
      WaitSat();
      beepingTimes(20, 50);
      delay(2000);
      lcd.clear();
    }
  }

  if (message == "ledsON")
  {
    if(bomb.sound){beepingTimes(5, 50);}
    bomb.leds = true;
    Serial.println("\nLeds are ON!");
    lcd.clear();
    lcd.setCursor(6,0);
    lcd.print("LEDS");
    lcd.setCursor(7, 1);
    lcd.print("ON");
  }

  if (message == "ledsOFF")
  {
    if(bomb.sound){beepingTimes(5, 50);}
    bomb.leds = false;
    Serial.println("\nLeds are OFF!");
    lcd.clear();
    lcd.setCursor(6,0);
    lcd.print("LEDS");
    lcd.setCursor(6, 1);
    lcd.print("OFF");
  }

  if (message == "soundON")
  {
    if(bomb.sound){beepingTimes(5, 50);}
    bomb.sound = true;
    Serial.println("\nSound is ON!");
    lcd.clear();
    lcd.setCursor(5,0);
    lcd.print("SOUND");
    lcd.setCursor(7, 1);
    lcd.print("ON");
  }

  if (message == "soundOFF")
  {
    if(bomb.sound){beepingTimes(5, 50);}
    bomb.sound = false;
    Serial.println("\nSound is OFF!");
    lcd.clear();
    lcd.setCursor(6,0);
    lcd.print("SOUND");
    lcd.setCursor(6, 1);
    lcd.print("OFF");
  }

  if (message == "smokeON")
  {
    if(bomb.sound){beepingTimes(5, 50);}
    bomb.smoke = false;
    Serial.println("\nSmoke is ON!");
    lcd.clear();
    lcd.setCursor(5,0);
    lcd.print("SMOKE");
    lcd.setCursor(7, 1);
    lcd.print("ON");
  }

  if (message == "smokeOFF")
  {
    if(bomb.sound){beepingTimes(5, 50);}
    bomb.smoke = false;
    Serial.println("\nSmoke is OFF!");
    lcd.clear();
    lcd.setCursor(5,0);
    lcd.print("SMOKE");
    lcd.setCursor(6, 1);
    lcd.print("OFF");
  }

  if (message == "sendConfig")
  {
    if(bomb.sound){beepingTimes(1, 2000);}
    if(bomb.gps && bomb.latZone != 0.0 || !bomb.gps) {
      bluetoothConfigured = true;
      Serial.println("\nGame READY!!");
      lcd.clear();
      bombIsReady();
      delay(2000);
      lcd.clear();
    } else {
      lcd.setCursor(6, 0);
      lcd.print("Set");
      lcd.setCursor(2, 1);
      lcd.print("Coordinates");
      delay(2000);
    }

  }
  delay(50);
  }

  }
}