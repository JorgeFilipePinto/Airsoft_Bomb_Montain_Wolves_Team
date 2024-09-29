#pragma once


class Bomb{
  public:
    int time;
    int tries;
    int players;
    int gameTime;
    int speedLight[4];
    double latZone;
    double longZone;
    double maxDistance;
    String code;
    boolean gps;
    boolean sound;
    boolean leds;
    boolean smoke;
    Bomb(int time, String code, int tries);
    boolean checkCode(String code);
    boolean isExplode();
    int getSize();
    boolean isValidZone();



  private:




};