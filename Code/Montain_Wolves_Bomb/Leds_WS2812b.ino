

void respiracao(byte);
void gradienteOndas();
void gradienteMovendo();
void fillSolidColor(CRGB);
void luzesDancantes();
void cometa();
void explosao();
CRGB returnColor(int);
CRGBPalette16 returnPalette(int);

/*
 * EFEITO 1
 */
void respiracao(byte selcor, accum88 speed) {
  for (int i = 0; i < 1000; i++) {
    breatheLevel = beatsin16(speed, 0, 255);
    fill_solid(fita, NUM_LEDS_FITA, CHSV(selcor, 255, breatheLevel));
    FastLED.show();
    delay(10);
  }
}

/*
 * EFEITO 2
 */
void gradienteOndas() {
  CRGBPalette16 selPalette = returnPalette(random(1, NUM_PALETTES + 1));
  int indexPal = 2;
  for (int i = 0; i < 1000; i++) {
    beatA = beatsin16(30, 0, 255);
    beatB = beatsin16(20, 0, 255);
    fill_palette(fita, NUM_LEDS_FITA, (beatA + beatB) / 2, indexPal, selPalette, 255, LINEARBLEND);
    FastLED.show();
    delay(10);
  }
}


/*
 * EFEITO 3
 */
void gradienteMovendo() {
  CRGBPalette16 selPalette = returnPalette(random(1, NUM_PALETTES + 1));
  for (int i = 0; i < 1000; i++) {
    fill_palette(fita, NUM_LEDS_FITA, palleteIndex, 255 / NUM_LEDS_FITA, selPalette, 255, LINEARBLEND);
    FastLED.show();
    palleteIndex++;
    delay(10);
  }
}


/*
 * EFEITO 6
 */
void fillSolidColor(CRGB selcor) {
  fill_solid(fita, NUM_LEDS_FITA, selcor);
  FastLED.show();
}

/*
 * EFEITO 7
 */
void luzesDancantes() {
  int c = random(1, 5);
  CRGB cor1 = returnColor(c);
  CRGB cor2 = returnColor(c + 1);
  CRGB cor3 = returnColor(c + 2);

  int c2 = random(1, 5);
  CRGB cor4 = returnColor(c2);
  CRGB cor5 = returnColor(c2 + 1);
  CRGB cor6 = returnColor(c2 + 2);

  for (int i = 0; i < 2000; i++) {
    sinBeat   = beatsin8(30, 0, NUM_LEDS_FITA / 2, 0, 0);
    sinBeat2  = beatsin8(30, 0, NUM_LEDS_FITA / 2, 0, NUM_LEDS_FITA);
    sinBeat3  = beatsin8(30, 0, NUM_LEDS_FITA / 2, 0, NUM_LEDS_FITA / 2);

    fita[sinBeat]   = cor1;
    fita[sinBeat2]  = cor2;
    fita[sinBeat3]  = cor3;

    fita[sinBeat + NUM_LEDS_FITA / 2]   = cor4;
    fita[sinBeat2 + NUM_LEDS_FITA / 2]  = cor5;
    fita[sinBeat3 + NUM_LEDS_FITA / 2]  = cor6;

    fadeToBlackBy(fita, NUM_LEDS_FITA, 10);
    FastLED.show();
  }
}

/*
 * EFEITO 7
 */
void cometa() {
  byte fade = 128;
  int cometaSize = 5;
  byte hue = random(1, 255);
  int iDirection = 1;
  int iPos = 0;

  for (int i = 0; i < 1000; i++) {

    iPos += iDirection;
    if (iPos == (NUM_LEDS_FITA - cometaSize) || iPos == 0)
      iDirection *= -1;

    for (int i = 0; i < cometaSize; i++)
      fita[iPos + i].setHue(hue);

    // Randomly fade the LEDs
    for (int j = 0; j < NUM_LEDS_FITA; j++)
      if (random(10) > 5)
        fita[j] = fita[j].fadeToBlackBy(fade);

    delay(20);
    FastLED.show();
  }
}

/*
 * EFEITO 8
 */
void explosao() {
  FastLED.clear();
  byte fade = 128;
  int expSize = NUM_LEDS_FITA / 2;   // tamanho da explosao
  int numExplosoes = 4;         // quantas explosoes no efeito

  for (int x = 0; x < numExplosoes ; x++) {
    byte hue = random(1, 255);        // escolhe cor aleatoria
    Serial.print("Cor: "); Serial.println(hue);

    for (int i = 0; i < expSize; i++) {
      fita[NUM_LEDS_FITA / 2 + i].setHue(hue);
      fita[NUM_LEDS_FITA / 2 - i].setHue(hue);
      if (i > expSize / 2) {
        i++;
        fita[NUM_LEDS_FITA / 2 + i].setHue(hue);
        fita[NUM_LEDS_FITA / 2 - i].setHue(hue);
      }
      FastLED.show();
    }

    delay(10);
    for (int i = 0; i < 50; i++) {
      for (int j = 0; j < NUM_LEDS_FITA; j++) {
        if (random(10) > 8)
          fita[j] = fita[j].fadeToBlackBy(fade);
      }
      delay(10);
      FastLED.show();
    }
  }
}


/*
   FUNÇÃO DE SELEÇÃO DE CORES
*/
CRGB returnColor(int num) {
  switch (num) {
    case 1:
      return CRGB::Red;
      break;
    case 2:
      return CRGB::Green;
      break;
    case 3:
      return CRGB::Blue;
      break;
    case 4:
      return CRGB::Pink;
      break;
    case 5:
      return CRGB::Yellow;
      break;
    case 6:
      return CRGB::Magenta;
      break;
    case 7:
      return CRGB::Cyan;
      break;
    case 8:
      return CRGB::Purple;
      break;
    case 9:
      return CRGB::Gray;
      break;
    default:
      return CRGB::Black;
      break;
  }
}

/*
   FUNÇÃO DE SELEÇÃO DE PALETAS
*/
CRGBPalette16 returnPalette(int selPalette) {
  switch (selPalette) {
    case 1:
      return brownGreenPalette;
      break;
    case 2:
      return heatPalette;
      break;
    case 3:
      return purplePalette;
      break;
    case 4:
      return greenbluePalette;
      break;
    case 5:
      return sunsetPalette;
      break;
    case 6:
      return fireandicePalette;
      break;
    case 7:
      return turqPalette;
      break;
    case 8:
      return autumnrosePalette;
      break;
    case 9:
      return bhw1_06Palette;
      break;
    case 10:
      return xmasPalette;
      break;
    case 11:
      return justduckyPalette;
      break;
    default:
      return heatPalette;
      break;
  }
}