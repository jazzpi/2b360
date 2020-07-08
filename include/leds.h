#include "FastLED.h"

#define NUM_LEDS 60
#define LED_PIN 13
#define SPEED_SHIFT 4
#define MAX_BRIGHTNESS 84

extern CRGB leds[NUM_LEDS];
extern uint8_t brightness;
extern uint8_t speed;

inline void setLED(uint8_t i, uint8_t hue, uint8_t sat, uint8_t val) {
  leds[i % NUM_LEDS] = CHSV(hue, sat, val);
}

void led_setup();
void setAllLED(uint8_t hue, uint8_t sat, uint8_t val);