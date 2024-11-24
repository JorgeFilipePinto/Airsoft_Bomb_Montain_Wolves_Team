#pragma once

enum BombStatus {
  initialize,
  configuration,
  readyToArm,
  armed,
  disarm,
  explode
};


class Bomb{
  public:
    int time;
    int tries;
    int tryArming;
    int players;
    int gameTime;
    int speedLight = 20;
    const int speedSound[4] = {250, 500, 1000, 2000};
    BombStatus bombStatus = initialize;
    double latZone;
    double longZone;
    double maxDistance;
    boolean codeDiscovered;
    String code;
    boolean gps;
    boolean sound;
    boolean leds;
    boolean smoke;
    String checkGPS();
    String checkLeds();
    String checkSound();
    String checkSmoke();
    Bomb(int, String, int, int, int);
    boolean checkCode(String code);
    boolean isExplode();
    boolean finishGame(unsigned long);
    boolean isTimeOut(unsigned long);
    int getSize();
    boolean isValidZone();

  private:

};