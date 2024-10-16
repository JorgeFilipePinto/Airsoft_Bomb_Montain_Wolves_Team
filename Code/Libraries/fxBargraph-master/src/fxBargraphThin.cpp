#include "fxBargraph.h"

fxBargraphThin::fxBargraphThin(LiquidCrystal_I2C& lcd, byte x, byte y, byte id, byte width, int max, byte clr, bool rtl)
  : fxBargraph(lcd, x, y, id, width, max, clr, rtl) {
    steps = CHAR_COLS + 1; // bridge inter-character gap
    fullchar = '-';
}

void fxBargraphThin::createFraction(byte frac) {
  // Create fractional custom character
  byte dyn[CHAR_ROWS] = { 0,0,0,0,0,0,0,0 };
  byte pattern;
  if (rtl) pattern = (0b11111100 << frac) >> 8;
  else pattern = 0b11111000000 >> frac;
  dyn[3] = pattern;
  lcd.createChar(id, dyn);
}

