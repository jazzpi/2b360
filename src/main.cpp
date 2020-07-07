#include <Arduino.h>

#include "leds.h"
#include "modes/split_loop.h"

#define LEDS_PER_SPLIT (NUM_LEDS / SPLITS)
#define MAX_BRIGHTNESS 32


void setup() {
  // pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  Serial.println("setup");

  led_setup();
  modes::split_loop::setup(1);
}

void loop() {
  modes::split_loop::step();
  delay(30);
}