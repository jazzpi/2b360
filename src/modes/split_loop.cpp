#include "leds.h"

namespace modes {
namespace split_loop {

static uint8_t splits;
static uint8_t leds_per_split;
static uint8_t hue;
static uint8_t hue_per_split;
static uint8_t rot;

void setup(uint8_t splits_) {
    splits = splits_;
    leds_per_split = NUM_LEDS / splits;
    hue = 0;
    hue_per_split = 256 / splits_;
    rot = 0;
}

void step() {
  for (uint8_t split = 0; split < splits; split++) {
    for (uint8_t i = 0; i < leds_per_split; i++) {
      // uint8_t val = (i > leds_per_split / 3) ? 3 * i : 0;
      uint8_t val = 64;
      setLED(rot + i + split * leds_per_split, split * hue_per_split + hue, 255, val);
    }
  }
  FastLED.show();
  hue += 2;
  rot = (rot + 1) % NUM_LEDS;
}

} // namespace split_loop
} // namespace modes
