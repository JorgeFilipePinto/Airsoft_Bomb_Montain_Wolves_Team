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
    String code;
    boolean gps;
    boolean sound;
    boolean leds;
    boolean smoke;
    Bomb(int, String, int);
    void gametime(int);
    void setTimeBomb(int);
    void setCode(String);
    boolean rigthSize(String);
    void setPlayers(int);
    boolean checkCode(String);
    boolean isExplode();
    int getSize();
    boolean isValidZone();



  private:




};