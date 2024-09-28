#include<Wire.h>
#include "BluetoothSerial.h"
#include <LCD-I2C.h>
#include <Keypad.h>
#include"Bomb.h"
#include <Adafruit_SSD1306.h>
#include <TinyGPS++.h>


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

//On ESP32: GPIO-21(SDA), GPIO-22(SCL)
#define OLED_RESET -1 //Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C //See datasheet for Address
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


enum GameStatus {
  Configuration,
  Prepared,
  ReadyToArm,
  TryCode,
  VerifyCode,
  Disarm,
  Explode
};


String code = "";
String secondCode = "";
int codeSize = 0;
int playersNum;
int gameTime;

String device_name = "Montain_Wolves_Airsoft_Bomb";
boolean bluetoothConfigured = false;
const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
byte rowPins[ROWS] = {13, 12, 14,27}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {26, 25, 33, 32}; //connect to the column pinouts of the keypad


char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};


void bluetoothConfig(BluetoothSerial);
void intro();



// Check if Bluetooth is available
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

// Check Serial Port Profile
#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Port Profile for Bluetooth is not available or not enabled. It is only available for the ESP32 chip.
#endif


BluetoothSerial BT;
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS );
GameStatus gameStatus = Configuration;
LCD_I2C lcd(0x27, 16, 2);
Bomb bomb(30, "0000", 3);



void setup() {
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
    }
  display.clearDisplay();
  display.display();
  delay(2000);
      display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.setTextSize(3);
    display.print("No Data");
    display.display();


  Serial.begin(115200);
  BT.begin(device_name);
  Serial.printf("The device with name \"%s\" is started \nNow you can pai it with Bluetooth\n", device_name.c_str());
  Serial.print("MAC Address: "); Serial.println(BT.getBtAddressString());
  Wire.begin();
  lcd.begin(&Wire);
  lcd.display();
  lcd.backlight();

  intro();
}



void loop() {

  switch(gameStatus){
    case Configuration: {
      String message = "";
      Serial.println("Bluetooth configuration!");
      lcd.setCursor(3,0);
      lcd.print("Bluetooth");
      lcd.setCursor(1,1);
      lcd.print("Configuration!");
      bluetoothConfig(BT);
      gameStatus = Prepared;
      break;
    }
    case Prepared: {
      lcd.backlight();
      lcd.setCursor(6, 0);
      lcd.print("Zone");
      lcd.setCursor(3, 1);
      lcd.print("Autorized");
      delay(500);
      lcd.backlightOff();
      break;
    }
    case ReadyToArm: {
      lcd.setCursor(0,0);
      lcd.print("Insert Bomb Code");
      char key = keypad.getKey();
      if(key){
        if(key == 'D'){
          Serial.println("Codigo inserido com sucesso!");
          Serial.print("code size "); Serial.println(codeSize);
          gameStatus = TryCode;
          lcd.clear();
        }else if (key == 'C' & codeSize > 0){
          lcd.clear();
          codeSize--;
          if (code.length() > 0) {
          String tempCode = code.substring(0, code.length() - 1);
          code = tempCode;
          lcd.setCursor(4, 1);
          lcd.print(code);
          }
        }else{
          code += key;
          codeSize++;
          Serial.print("Digit Insert "); Serial.println(key);
          lcd.setCursor(codeSize + 4, 1);
          lcd.print(key);
        }
      }
      break;
    }
    case TryCode: {
      lcd.setCursor(2,0);
      lcd.print("Bomb Armed!");
      char key = keypad.getKey();
      if(key){
        delay(100);
        if(codeSize > 0){
          secondCode += key;
          Serial.print("Digit Insert "); Serial.println(key);
          codeSize--;
          Serial.print("Faltam "); Serial.println(codeSize);
          lcd.setCursor(codeSize + 4, 1);
          lcd.print(key); 
        }
      }
      if(codeSize == 0){
        gameStatus = VerifyCode;
        lcd.clear();
        }
      break;
    }
    case VerifyCode: {
      if(code == secondCode){
        lcd.setCursor(1,0);
        lcd.print("Correct Code!");
        Serial.println("correct code!");
        delay(5000);
        lcd.clear();
        gameStatus = Disarm;
      }else{
        lcd.setCursor(3,0);
        lcd.print("Try Again!!");
        Serial.println("Try Again!!");
        codeSize = code.length();
        gameStatus = TryCode;
        secondCode = "";
        delay(5000);
        lcd.clear();
      }
      break;
    }
    case Disarm: {
      lcd.setCursor(4,0);
      lcd.print("YOU WIN!");
      Serial.println("YOU WIN!");
      break;
    }
    case Explode: {
      lcd.setCursor(1,0);
      lcd.print("Bomb Exploded");
      Serial.println("Bomb Exploded");
      break;
    }
    default: {
      Serial.println("Something wrong!!");
      break;
    }
  }
  delay(50);
}

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
    playersNum = message.substring(4).toInt();
    Serial.print("\nPlayers: "); Serial.println(playersNum);
    lcd.clear();
    lcd.setCursor(4,0);
    lcd.print("Players");
    lcd.setCursor(7, 1);
    lcd.print(String(playersNum));
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
    lcd.setCursor(6,0);
    lcd.print("Bomb");
    lcd.setCursor(3, 1);
    lcd.print("READY!");
    delay(2000);
    lcd.clear();
    lcd.backlightOff();
  }
  delay(50);
  }

  }
}



void intro(){
  lcd.setCursor(1,0);
  lcd.print("Montain Wolves");
  lcd.setCursor(2,1);
  lcd.print("Airsoft Bomb");
  char key;
  while(key != 'D'){
    key = keypad.getKey();
    lcd.setCursor(9,0);
    lcd.print("Montain Wolves");
    lcd.setCursor(5,1);
    lcd.print(F("Press D to continue!!"));
    for(int i = 0; i < 10; i++){
      key = keypad.getKey();
      if(key == 'D'){
        break;
      }
      lcd.scrollDisplayLeft();
      delay(300);
    }
    lcd.clear();
  }
};
