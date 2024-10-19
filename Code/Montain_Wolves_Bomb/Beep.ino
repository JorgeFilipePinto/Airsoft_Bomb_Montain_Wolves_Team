void beepingTimes(int, int);
void beepBomb();
void beepOn(boolean);
extern unsigned long lastBeep;
extern int bombTime;



void beepingTimes(int times, int time){
  if (bomb.sound) {
    for (int i = 0; i < times; i++) {
      digitalWrite(beep, HIGH);
      delay(time);
      digitalWrite(beep, LOW);
      delay(time);
    }
  }
}

void beepBomb() {
  int bombState = 0;
  if (bomb.time > bombTime / 2){
    //bombState = 2000;
    bombState = bomb.speedSound[3];
  }else if (bomb.time < bombTime / 2 && bomb.time > bombTime / 4) {
    bomb.speedLight = 50;
    //bombState = 1000;
    bombState = bomb.speedSound[2];
  } else if (bomb.time < bombTime / 4 && bomb.time > 20000) {
    bomb.speedLight = 100;
    //bombState = 500;
    bombState = bomb.speedSound[1]; 
  } else if (bomb.time < 20000) {
    bomb.speedLight = 255;
    //bombState = 250;
    bombState = bomb.speedSound[0];
  }
  if (millis() - lastBeep >= bombState) {
    if (digitalRead(beep) == HIGH) {
      lastBeep = millis();
      digitalWrite(beep, LOW);
    }else {
      digitalWrite(beep, HIGH);
      lastBeep = millis();
    }
  } else if (millis() - lastBeep < bombState && millis() - lastBeep >= 50 && bomb.sound) {
      int stateBeeper = digitalRead(beep);
      if (stateBeeper == HIGH) {
        digitalWrite(beep, LOW);
      }
  }
}


void beepOn(boolean beeping) {
  if (beeping) {
    delay(10);
    digitalWrite(beep, HIGH);
  } else {
    digitalWrite(beep, LOW);
  }
}

