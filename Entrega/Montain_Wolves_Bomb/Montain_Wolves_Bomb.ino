#include <Wire.h>
#include "BluetoothSerial.h"
#include <LCD-I2C.h>
#include <Keypad.h>
#include "Bomb.h"
#include <Adafruit_SSD1306.h>
#include <TinyGPS++.h>
#include <FastLED.h>
#include "paletas.h"
#include <LoRa.h>

// Check if Bluetooth is available
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
// Check Serial Port Profile
#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Port Profile for Bluetooth is not available or not enabled. It is only available for the ESP32 chip.
#endif

#define SCREEN_WIDTH 128 // OLED display width
#define SCREEN_HEIGHT 64 // OLED display height
#define OLED_RESET -1 //Reset pin
#define SCREEN_ADDRESS 0x3C //LCD Oled Address
#define NUM_LEDS_FITA 20
#define PINO_FITA 15
#define LED_BRIGHTNESS 10
#define RXD2 16
#define TXD2 17
#define beep 2

HardwareSerial neogps(1);//GPS created serial

//Led Strip values
CRGB fita[NUM_LEDS_FITA];
uint8_t hue = 10;
uint8_t palleteIndex = 0;
uint16_t breatheLevel = 0;
byte cor = 0;
uint16_t beatA = 0;
uint16_t beatB = 0;
uint8_t sinBeat = 0;
uint8_t sinBeat2 = 0;
uint8_t sinBeat3 = 0;


unsigned long start = millis();
boolean setupFinish = false;
String device_name = "Montain_Wolves_Airsoft_Bomb";
boolean Configured = false;
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

TaskHandle_t Task2;

extern void setup_ori();
extern void core_1();

BluetoothSerial BT; //Bluetooth object
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS ); //keypad object
LCD_I2C lcd(0x27, 16, 2); //liquid cristal lcd object
Bomb bomb(15, "123456789", 3, 3, 30); //bomb object
TinyGPSPlus gps; //gps object
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); //oled display object

void setup() {
  setup_ori();

}

void loop() {

  core_1();
  
}
