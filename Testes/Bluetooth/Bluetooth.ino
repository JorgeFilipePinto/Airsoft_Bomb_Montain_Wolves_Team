#include "BluetoothSerial.h"

String device_name = "Montain_Wolves_Airsoft_Bomb";
String message = "";
char isComingChar;
boolean gps, leds, smoke, sound = false;
boolean gameConfigured = false;
int playersNum, gameTime;
String bombCode = "";



// Check if Bluetooth is available
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

// Check Serial Port Profile
#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Port Profile for Bluetooth is not available or not enabled. It is only available for the ESP32 chip.
#endif

BluetoothSerial BT;

void setup() {
Serial.begin(115200);
BT.begin(device_name);
//BT.deleteAllBondedDevices();
Serial.printf("The device with name \"%s\" is started \nNow you can pai it with Bluetooth\n", device_name.c_str());
Serial.print("MAC Address: "); Serial.println(BT.getBtAddressString());


while(!gameConfigured)
{

    if (BT.available())
  {
    char inComingChar = BT.read();
    if (inComingChar != '\n')
    {
      message += String (inComingChar);
    }
    else
    {
      message = "";
    }
    Serial.write(inComingChar);
  }

  if (message.substring(0, 4) == "TEAM")
  {
    playersNum = message.substring(4).toInt();
    Serial.print("\nPlayers: "); Serial.println(playersNum);
  }

  if (message.substring(0,4) == "TIME")
  {
    gameTime = message.substring(4).toInt() * 1000;
    Serial.print("\nGame Time: "); Serial.println(gameTime);
  }

  if (message.substring(0,4) == "CODE")
  {
    bombCode = message.substring(4);
    Serial.print("Bomb Code: "); Serial.println(bombCode);
  }

  if (message == "gpsON")
  {
    gps = true;
    Serial.println("\nGPS is ON!");
  }

  if (message == "gpsOFF")
  {
    gps = false;
    Serial.println("\nGPS is OFF!");
  }

  if (message == "ledsON")
  {
    leds = true;
    Serial.println("\nLeds are ON!");
  }

  if (message == "ledsOFF")
  {
    leds = false;
    Serial.println("\nLeds are OFF!");
  }

  if (message == "soundON")
  {
    sound = true;
    Serial.println("\nSound is ON!");
  }

  if (message == "soundOFF")
  {
    sound = false;
    Serial.println("\nSound is OFF!");
  }

  if (message == "smokeON")
  {
    sound = false;
    Serial.println("\nSmoke is ON!");
  }

  if (message == "smokeOFF")
  {
    sound = false;
    Serial.println("\nSmoke is OFF!");
  }

  if (message == "sendConfig")
  {
    gameConfigured = true;
    Serial.println("\nGame READY!!");
  }
  delay(50);
  }

}

void loop() {

}

