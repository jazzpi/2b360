#include "FastLED.h"

#define NUM_LEDS 60
#define LED_PIN 13

extern CRGB leds[NUM_LEDS];

inline void setLED(uint8_t i, uint8_t hue, uint8_t sat, uint8_t val) {
  leds[i % NUM_LEDS] = CHSV(hue, sat, val);
}

void led_setup();