int fuseTime = 1;
void getData();
double getDistance();



void getData(boolean newData){

  while (neogps.available()){
    if (gps.encode(neogps.read())){
      newData = true;
    }
  }
}


double getDistance(double latZone, double longZone){
  return TinyGPSPlus::distanceBetween(gps.location.lat(), gps.location.lng(), latZone, longZone);
}