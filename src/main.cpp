#include <Arduino.h>

#include "leds.h"
#include "modes.h"

void setup() {
  Serial.begin(9600);
  Serial.println("setup");

  led_setup();
  // modes::strobopop::setup(true);
  modes::split_loop::setup(5);
  // modes::ice::setup();
}

inline uint16_t shift_right_round(uint16_t val, uint8_t shift) {
  uint16_t ret = val >> shift;
  if (val & (1 << (shift - 1))) {
    // Round up
    ret++;
  }
  return ret;
}

void loop() {
  speed = shift_right_round(analogRead(A0), 2);
  brightness = 25 + shift_right_round(analogRead(A1), 4);
  brightness = min(brightness, MAX_BRIGHTNESS);
  // a0_sum += analogRead(A0);
  // a1_sum += analogRead(A1);
  // if (iter % 1 == 0) {
  //   speed = a0_sum >> 6;
  //   brightness = 25 + (a1_sum >> 8);
  //   brightness = min(brightness, MAX_BRIGHTNESS);
  //   a0_sum = 0;
  //   a1_sum = 0;
  //   Serial.print("s: ");
  //   Serial.print(speed);
  //   Serial.print(", b: ");
  //   Serial.println(brightness);
  // }

  // modes::strobopop::step();
  modes::split_loop::step();
  // modes::ice::step();
  delay(2);
  // delay(30);
}