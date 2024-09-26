#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Montain Wolves Airsoft Bomb";
const char* password = "123456789";

boolean gps, leds, smoke, sound = false;
boolean gameConfigured = false;

WiFiServer server(80);
void setup() {
  WiFi.softAP(ssid, password);
  server.begin();
  Serial.begin(115200);
  Serial.print("IP address: "); Serial.println(WiFi.softAPIP());

}

void loop() {
  WiFiClient client = server.available();
  String all_command = "";
  while(client & !gameConfigured){
    String request = "";
    if (client.available()){
      char c = client.read();
      request += c;
      if (c =='\r'){
        Serial.println(request);

        int start = request.indexOf("GET /") + 5;
        int end = request.indexOf("HTTP/");
        String appCommand = request.substring(start, end);

        appCommand.replace("\n", "");
        appCommand.replace("\r", "");
        appCommand.replace(" ", "");
        appCommand.replace("\t", "");
        appCommand.trim();

        Serial.println(appCommand);
        all_command = appCommand + "is on";

        if (appCommand.equals("gpsON")){
          gps = true;
        }

        if (appCommand.equals("gpsOFF")){
          gps = false;
        }

        if (appCommand.equals("ledsON")){
          leds = true;
        }

        if (appCommand.equals("ledsOFF")){
          leds = false;
        }

        if (appCommand.equals("soundON")){
          sound = true;
        }

        if (appCommand.equals("soundOFF")){
          sound = false;
        }

        if (appCommand.equals("sendConfig")){
          gameConfigured = true;
        }

        if (client.peek() == '\n'){
          client.println("HTTP/1.1 200 OK");
          client.println("Content-type:text/html");
          client.println();
          String commandWithTags = "<html><body>" + all_command + "</body><html>";
          client.println(commandWithTags);
          break;
        }
      }
    }
  }

}
