
extern unsigned long bombTime_millisAnterior;
extern unsigned long bombTime_millisAnterior;
boolean bombClock();

boolean isExploded = false;


boolean keypadIsInactive() {
  
}


boolean bombClock(){
  
  if (millis() - bombTime_millisAnterior >= bomb.time){
    isExploded = true;
  }else if (millis() - clock_millisAnterior >= 1000){
    clock_millisAnterior = millis();
    secondsAnterior--;
    lcd.setCursor(4, 1);
    lcd.print(minutesAnterior);
    lcd.print(":");
    lcd.print(secondsAnterior);
    count++;
    if(count == 60){
      secondsAnterior = 59;
      minutesAnterior--;
      count = 0;
    }
  }
  return isExploded;
}