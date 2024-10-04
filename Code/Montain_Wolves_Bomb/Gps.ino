int fuseTime = 1;
void getData();
double getDistance();


double getDistance(double latZone, double longZone){
  double distance = TinyGPSPlus::distanceBetween(gps.location.lat(), gps.location.lng(), latZone, longZone);
  return distance;
}