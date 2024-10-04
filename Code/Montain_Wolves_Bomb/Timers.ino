extern void printClock(int, int);
void bombClock(unsigned long);
int timeMin = bomb.time / 60000;
int timeSec = 0;

void bombClock(unsigned long lastTimeSec) {
  
  if(timeMin != 0 || timeSec != 0) {
    if(timeSec == 0){
      lastTimeSec = millis();
      timeMin--;
      timeSec = 59;
      lcd.clear();
    }else if(millis() - lastTimeSec >= 1000){
      lastTimeSec = millis();
      timeSec--;
      lcd.clear();
    }
    printClock(timeMin, timeSec);
  }
}


void gameClock(unsigned long lastTime) {
  
  
}