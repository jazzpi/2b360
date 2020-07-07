#include "leds.h"

CRGB leds[NUM_LEDS];

void led_setup() {
  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);
  pinMode(LED_PIN, OUTPUT);
}