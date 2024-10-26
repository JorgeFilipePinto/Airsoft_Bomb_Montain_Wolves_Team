#include <esp_now.h>
#include <WiFi.h>

#define CHANNEL 1



uint8_t gpios[] = {23, 2};

int gpioCount;

uint8_t macSlaves [][6] = {{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}};





void setup() {
  Serial.begin(115200);

  gpioCount = sizeof(gpios)/sizeof(uint8_t);

  WiFi.mode(WIFI_STA);
  Serial.print("Mac Address in Station: "); Serial.println(WiFi.macAddress());

  InitESPNow();

  int slavesCount = sizeof(macSlaves) / 6 / sizeof(uint8_t);
  esp_now_peer_info_t slave;

  for (int i = 0; i < slavesCount; i++){
    esp_now_peer_info_t slave;

    slave.channel = CHANNEL;

    slave.encrypt = 0;
    memcpy(slave.peer_addr, macSlaves[i], sizeof(macSlaves[i]));

    esp_now_add_peer(&slave);
  }

  esp_now_register_send_cb (OnDataSent);


  for (int i = 0; i < gpioCount; i++) {
    pinMode(gpios[i], INPUT);
  }

  send();


}


void InitESPNow () {
  if (esp_now_init () == ESP_OK) {
    Serial.println("ESPNow Init Success");
  } else {
    Serial.println("ESPNow Init Failed");
    ESP.restart();
  }
}



void send () {
  uint8_t values[2] = {100, 200};

  /*for (int i = 0; i< gpioCount; i++) {
    values[i] = digitalRead(gpios[i]);
  }*/

  uint8_t broadcast [] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
  esp_err_t result = esp_now_send(broadcast, (uint8_t*) &values, sizeof(values));
  Serial.println("Send Status: ");

  if (result == ESP_OK) {
    Serial.println("Success");
  } else {
    Serial.println("Error");
  }
  delay(2000);
}


void OnDataSent (const uint8_t *mac_addr, esp_now_send_status_t status) {
  char macStr[18];

  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x", 
          mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);

          Serial.print("Sent to:"); Serial.println(macStr);
          Serial.print("Status: "); Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Success" : "Fail");
  send();
}





void loop() {
  // put your main code here, to run repeatedly:

}
