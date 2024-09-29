extern void menuCore0();
extern void getData();
extern void printData();
extern void printNoData();

void gpsTracker(void * pvParameters){
  for(;;){

    menuCore0();

    boolean newData = false;
    for (unsigned long start = millis(); millis() - start < 1000;)
    {
      getData(newData);
    }

    //If newData is true
    if(newData == true)
    {
      newData = false;
      printData();
    }
    else
    {
      printNoData();
    }
  }
}
