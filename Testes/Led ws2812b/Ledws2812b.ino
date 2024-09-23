/*
      Programa Efeitos de Fita de LED WS2812b com FASTLed
 
      Componentes:
        - Arduino (Qualquer placa) ou ESP32/8266;
        - 1 Capacitor 10uF
        - 1 Resistores de 270-470 Ohms
        - 1 Fita de Led WS2812b

      Versão 1.0 - Versão inicial com 10 efeitos utilizando biblioteca FASTLed - 27/Nov/2021

 *    * Criado por Cleber Borges - FunBots - @cleber.funbots  *     *
      Referências:
      Scott Marley: https://www.youtube.com/playlist?list=PLgXkGn3BBAGi5dTOCuEwrLuFtfz0kGFTC
      Dave's Garage: https://www.youtube.com/playlist?list=PLF2KJ6Gy3cZ7ynsp8s4tnqEFmY15CKhmH
      
      Instagram: https://www.instagram.com/cleber.funbots/
      Facebook: https://www.facebook.com/cleber.funbots
      YouTube: https://www.youtube.com/c/funbots
      Telegram: https://t.me/cleberfunbots

*/

// Inclusão de Bibliotecas e .h
#include <FastLED.h>
#include "paletas.h"

// delcara Fita de LEDs
#define NUM_LEDS_FITA 22
#define PINO_FITA 12
CRGB fita[NUM_LEDS_FITA];

// Variáveis de programa
uint8_t hue = 10;
uint8_t palleteIndex = 0;
uint16_t breatheLevel = 0;
byte cor = 0;
uint16_t beatA = 0;
uint16_t beatB = 0;
uint8_t sinBeat = 0;
uint8_t sinBeat2 = 0;
uint8_t sinBeat3 = 0;

void setup() {
  FastLED.addLeds<WS2812B, PINO_FITA, GRB>(fita, NUM_LEDS_FITA);
  FastLED.setBrightness(200);

  // Serial para Debug
  Serial.begin(115200);
}

void loop() {

  //Efeito 1 - Paletas em Ondas
  gradienteOndas();
  fillSolidColor(CRGB::Black);

  // Efeito 2 - Respiracao
  cor = random(1, 255);
  respiracao(cor);
  fillSolidColor(CRGB::Black);

  // Efeito 3 - Paleta com movimento
  gradienteMovendo();
  fillSolidColor(CRGB::Black);

  // Efeito 4 - Pixels Aleatorios em uma Paleta
  PixelsAleatorios();
  fillSolidColor(CRGB::Black);

  // Efeito 5 - Raio Arco-Iris
  raioArcoiris();
  fillSolidColor(CRGB::Black);

  // Efeito 6 - Luzes dançantes
  luzesDancantes();
  fillSolidColor(CRGB::Black);

  // Efeito 7 - Cometas
  cometa();
  fillSolidColor(CRGB::Black);

  // Efeito 8 - Explosão
  explosao();

  // Efeito 9 - Bolas coloridas
  bolasColoridas();
  fillSolidColor(CRGB::Black);

  // Efeito 10 - Teatro 2021
  cor = random(1, 255);
  teatro2021(cor);
  fillSolidColor(CRGB::Black);

}

/*
 * EFEITO 1
 */
void respiracao(byte selcor) {
  for (int i = 0; i < 1000; i++) {
    breatheLevel = beatsin16(10, 0, 255);
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
 * EFEITO 4
 */
void PixelsAleatorios() {
  CRGBPalette16 selPalette = returnPalette(random(1, NUM_PALETTES + 1));
  for (int i = 0; i < 1000; i++) {
    if (i % 5 == 0) {
      fita[random16(0, NUM_LEDS_FITA - 1)] = ColorFromPalette(selPalette, random8(), 255, LINEARBLEND);
    }
    fadeToBlackBy(fita, NUM_LEDS_FITA, 1);
    FastLED.show();
    delay(10);
  }
}

/*
 * EFEITO 5
 */
void raioArcoiris() {
  static uint8_t hue = 0;
  int dir1 = 0;
  int i1 = 0;

  for (int i = 0; i < 2000; i++) {
    fita[i1] = CHSV(hue++, 255, 255);

    FastLED.show();
    for (int i = 0; i < NUM_LEDS_FITA; i++) {
      fita[i].nscale8(250);
    }

    if (dir1 == 0) {
      i1++;
    } else {
      i1--;
    }
    if (i1 == NUM_LEDS_FITA) {
      dir1 = 1;
    } else if ( i1 == 0) {
      dir1 = 0;
    }
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
 * EFEITO 8
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

    delay(100);
    for (int i = 0; i < 400; i++) {
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
 * EFEITO 9
 */
void bolasColoridas() {
  byte dothue = 0;
  for (int i = 0 ; i < 4000 ; i++) {
    fadeToBlackBy( fita, NUM_LEDS_FITA, 20);

    for ( int i = 0; i < 8; i++) {
      fita[beatsin16( i + 7, 0, NUM_LEDS_FITA - 1 )] |= CHSV(dothue, 200, 255);
      dothue += 32;
    }
    FastLED.show();
  }
}

/*
 * EFEITO 10
 */
void teatro2021(byte selcor) {
  int tamLuz = 6;
  int luzes[tamLuz];
  int luzesTemp;
  luzes[0] = 125;//CHSV(selcor, 255, 125);
  luzes[1] = 255;//CHSV(selcor, 255, 255);
  luzes[2] = 255;//CHSV(selcor, 255, 255);
  luzes[3] = 125;//CHSV(selcor, 255, 125);
  luzes[4] = 0;//CHSV(selcor, 255, 0);
  luzes[5] = 0;//CHSV(selcor, 255, 0);

  for (int i = 0; i < 500; i++) {

    for (int l = 0; l < NUM_LEDS_FITA; l = l + tamLuz) {
      for (int m = 0; m < tamLuz; m++) {
        fita[l + m] = CHSV(selcor, 255, luzes[m]);
      }
      FastLED.show();
    }

    luzesTemp = luzes[0];
    for (int n = 0; n < tamLuz - 1; n++) {
      luzes[n] = luzes[n + 1];
    }
    luzes[tamLuz - 1] = luzesTemp;

    delay(30);
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
