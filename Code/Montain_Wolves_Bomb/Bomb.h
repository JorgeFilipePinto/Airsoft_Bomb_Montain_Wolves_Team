#pragma once


class Bomb{
  public:
    int time;
    int tries;
    String code;
    boolean gps;
    boolean sound;
    boolean leds;
    boolean smoke;
    Bomb(int time, String code, int tries);
    boolean checkCode(String code);
    boolean isExplode();



  private:




};