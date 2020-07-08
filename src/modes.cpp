#include "modes.h"
#include "leds.h"

namespace modes {
namespace split_loop {

static uint8_t splits;
static uint8_t leds_per_split;
static uint8_t hue_per_split;
static uint16_t rot;

void setup(uint8_t splits_) {
    splits = splits_;
    leds_per_split = NUM_LEDS / splits;
    hue_per_split = 256 / splits_;
    rot = 0;
}

void step() {
  for (uint8_t split = 0; split < splits; split++) {
    for (uint8_t i = 0; i < leds_per_split; i++) {
      uint8_t index = split * leds_per_split + i + (rot >> SPEED_SHIFT);
      setLED(index, split * hue_per_split, 255, brightness);
    }
  }
  FastLED.show();
  rot = (rot + speed) % (NUM_LEDS << SPEED_SHIFT);
}

} // namespace split_loop

namespace strobopop
{

static bool on;
static bool color;
static uint8_t hue;
static uint16_t progress;

void setup(bool color_) {
    on = false;
    color = color_;
    hue = 0;
    progress = 0;
}

void step() {
    static uint8_t iter = 0;
    if (on) {
        if (progress == ON_TIME) {
            progress = 0;
            on = false;
            setAllLED(hue, 0, 0);
        } else {
            progress++;
        }
    } else {
        if (progress > DELAY) {
            progress = 0;
            on = true;
            uint8_t sat = color ? 127 : 0;
            setAllLED(hue, sat, brightness);
            if (color) {
                hue += millis();
            }
        } else {
            progress += speed;
        }
    }
    FastLED.show();
}

} // namespace strobopop

namespace ice
{

int16_t hue;
int16_t next_hue;
uint8_t leds_on_next_hue;
bool inc;

void setup() {
    hue = MIN_HUE;
    next_hue = hue + 1;
    inc = true;
    leds_on_next_hue = 0;
}

void step() {
    if (hue > MAX_HUE) {
        inc = false;
        hue = MAX_HUE;
        next_hue = hue - 1;
    } else if (hue < MIN_HUE) {
        inc = true;
        hue = MIN_HUE;
        next_hue = hue + 1;
    }

    uint16_t counter = 0;
    for (uint8_t i = 0; i < NUM_LEDS; i++) {
        counter += leds_on_next_hue;
        if (counter >= 10) {
            counter -= 10;
            setLED(i, next_hue, next_hue, brightness);
        } else {
            setLED(i, hue, hue, brightness);
        }
    }
    // for (uint8_t split = 0; split < 6; split++) {
    //     for (uint8_t i = 0; i < leds_on_next_hue; i++) {
    //         setLED(split * 10 + i, next_hue, next_hue, brightness);
    //     }
    //     for (uint8_t i = leds_on_next_hue; i < 10; i++) {
    //         setLED(split * 10 + i, hue, hue, brightness);
    //     }
    // }
    FastLED.show();

    leds_on_next_hue++;
    if (leds_on_next_hue == 10) {
      leds_on_next_hue = 0;
      if (inc) {
        hue++;
        next_hue = hue + 1;
      } else {
        hue--;
        next_hue = hue - 1;
      }
    }
}

} // namespace ice

} // namespace modes