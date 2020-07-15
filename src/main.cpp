#include <Arduino.h>

#include "leds.h"
#include "modes.h"
#include "config.h"
#include "controls.h"

void reset() {
  led_setup();
  led_off();
  controls_setup();
  modes::setup();
}

void setup() {
  Serial.begin(9600);
  Serial.println("setup");

  reset();
}

void loop() {
  controls_step();
  if (!on) {
    reset();
    return;
  }

  if (btn_interrupt) {
    if (digitalRead(BUTTON_PIN) == LOW) {
      modes::cycle_mode();
    }
    btn_interrupt = 0;
  }

  modes::step_current();
  delay(2);
  // delay(30);
}