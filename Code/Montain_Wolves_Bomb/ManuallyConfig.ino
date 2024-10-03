extern boolean manuallyConfigured;

void manuallyConfigured();

enum Config {
  Players,
  TimeBomb,
  BombCode
};



void manuallyConfigured(){
  Config config = Players;
  char key;
  while (!manuallyConfigured) {
    String _players;
    String _timeBombe;
    String _code;
    
    switch(config):
    case Players: {
      key = keypad.getKey();
      
    }
  }
}