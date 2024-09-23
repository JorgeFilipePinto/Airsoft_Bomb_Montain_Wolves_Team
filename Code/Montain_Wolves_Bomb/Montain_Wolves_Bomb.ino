
boolean gpsEnable, soundEnable, ledsEnable, smokeEnable = false;

enum GameStatus {
  Configuration,
  Prepared,
  ReadyToArm,
  Armed,
  TryDisarm,
  Disarm,
  Explod
} ;

GameStatus gameStatus = Configuration;

String code = "123456789";
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

}

void loop() {
  switch(gameStatus){
    case Configuration:

      break;
    case Prepared:

      break;
    case ReadyToArm:

      break;
    case Armed:

      break;
    case TryDisarm:

      break;
    case Disarm:

      break;
    case Explod:

      break;
    default:
      Serial.println("Something wrong!!");
      break;
  }

  for(char digit : code){
    Serial.println(digit);
    delay(2000);
  }



}
