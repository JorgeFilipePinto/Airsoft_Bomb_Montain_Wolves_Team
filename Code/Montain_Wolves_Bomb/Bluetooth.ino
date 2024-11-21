extern boolean bluetoothConfigured;
extern void bombIsReady();
extern void beepingTimes(int, int);


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
    beepingTimes(5, 50);
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
    beepingTimes(5, 50);
    bomb.time = message.substring(4).toInt() * 60000;
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
    beepingTimes(5, 50);
    bomb.time = message.substring(4).toInt() * 60000;
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
    beepingTimes(5, 50);
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
    beepingTimes(5, 50);
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
    beepingTimes(5, 50);
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
    beepingTimes(5, 50);
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
    beepingTimes(5, 50);
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
    beepingTimes(5, 50);
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
    beepingTimes(5, 50);
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
    beepingTimes(5, 50);
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
    beepingTimes(5, 50);
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
    beepingTimes(1, 2000);
    bluetoothConfigured = true;
    Serial.println("\nGame READY!!");
    lcd.clear();

    bombIsReady();
    delay(2000);
    lcd.clear();
  }
  delay(50);
  }

  }
}