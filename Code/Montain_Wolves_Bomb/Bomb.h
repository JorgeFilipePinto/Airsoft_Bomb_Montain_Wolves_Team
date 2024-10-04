#pragma once


class Bomb{
  public:
    int time;
    int tries;
    int tryArming;
    int players;
    int gameTime;
    int speedLight[4];
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
    Bomb(int time, String code, int tries);
    boolean checkCode(String code);
    boolean isExplode();
    boolean finishGame(unsigned long);
    boolean isTimeOut(unsigned long);
    int getSize();
    boolean isValidZone();



  private:




};