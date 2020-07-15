#include <Arduino.h>

#include "leds.h"
#include "modes.h"
#include "config.h"
#include "controls.h"

static uint8_t mode = 0;

void reset() {
  led_setup();
  led_off();
  controls_setup();
  mode = 0;
  modes::split_loop::setup(5);
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
      mode = (mode + 1) % 4;
      switch (mode) {
      case 0:
        modes::split_loop::setup(5);
        break;
      case 1:
        modes::ice::setup();
      case 2:
        modes::strobopop::setup(false);
      case 3:
        modes::strobopop::setup(true);
      default:
        break;
      }
    }
    btn_interrupt = 0;
  }

  switch (mode) {
  case 0:
    modes::split_loop::step();
    break;
  case 1:
    modes::ice::step();
  case 2:
  case 3:
    modes::strobopop::step();
  default:
    break;
  }
  delay(2);
  // delay(30);
}