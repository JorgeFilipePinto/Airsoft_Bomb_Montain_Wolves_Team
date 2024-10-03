extern boolean bluetoothConfigured;
extern void bombIsReady();


void bluetoothConfig(BluetoothSerial);



void bluetoothConfig(BluetoothSerial BT){
  String message = "";
  while(!bluetoothConfigured){

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
    bomb.players = message.substring(4).toInt();
    Serial.print("\nPlayers: "); Serial.println(bomb.players);
    lcd.clear();
    lcd.setCursor(4,0);
    lcd.print("Players");
    lcd.setCursor(7, 1);
    lcd.print(String(bomb.players));
  }

  if (message.substring(0,4) == "TIME")
  {
    bomb.time = message.substring(4).toInt() * 1000;
    Serial.print("\nGame Time: "); Serial.println(bomb.time);
    lcd.clear();
    lcd.setCursor(3,0);
    lcd.print("Bomb Time");
    lcd.setCursor(2, 1);
    lcd.print(String(bomb.time / 1000));
    lcd.setCursor(5, 1);
    lcd.print("Minutes");
  }

  if (message.substring(0,4) == "CODE")
  {
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
    bomb.gps = false;
    Serial.println("\nGPS is OFF!");
    lcd.clear();
    lcd.setCursor(6,0);
    lcd.print("GPS");
    lcd.setCursor(6, 1);
    lcd.print("OFF");
  }

  if (message == "ledsON")
  {
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
    bluetoothConfigured = true;
    Serial.println("\nGame READY!!");
    lcd.clear();

    bombIsReady();
    
    delay(2000);
    lcd.clear();
    lcd.backlightOff();
  }
  delay(50);
  }

  }
}