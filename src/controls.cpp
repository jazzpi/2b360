#include "controls.h"

#include "Arduino.h"
#include "config.h"
#include "leds.h"

int btn_interrupt = 0;
bool on = false;

static uint8_t last_val = 0xFF;
static unsigned long last_time = 0;

void controls_setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(SPEED_PIN, INPUT);
  pinMode(BRIGHTNESS_PIN, INPUT);

  // Interrupt setup, see https://playground.arduino.cc/Main/PinChangeInterrupt/
  // Enable pin
  *digitalPinToPCMSK(BUTTON_PIN) |= bit(digitalPinToPCMSKbit(BUTTON_PIN));
  // Clear any outstanding interrupt
  PCIFR |= bit(digitalPinToPCICRbit(BUTTON_PIN));
  // Enable interrupt for the group
  PCICR |= bit(digitalPinToPCICRbit(BUTTON_PIN));

  last_val = digitalRead(BUTTON_PIN);
}

#if 0 <= BUTTON_PIN && BUTTON_PIN <= 7
ISR(PCINT2_vect)
#elif 8 <= BUTTON_PIN && BUTTON_PIN <= 13
ISR(PCINT0_vect)
#elif A0 <= BUTTON_PIN && BUTTON_PIN <= A5
ISR(PCINT1_vect)
#else
#error "Invalid BUTTON_PIN"
#endif
{
  unsigned long time = millis();
  if (time - last_time < 10) return;
  last_time = time;
  uint8_t val = digitalRead(BUTTON_PIN);
  if (val != last_val) {
    btn_interrupt++;
    last_val = val;
  }
}

inline uint16_t shift_right_round(uint16_t val, uint8_t shift) {
  uint16_t ret = val >> shift;
  if (val & (1 << (shift - 1))) {
    // Round up
    ret++;
  }
  return ret;
}

void controls_step() {
  on = (digitalRead(SWITCH_PIN) == LOW) ? true : false;

  unsigned long time = millis();
  uint8_t val = digitalRead(BUTTON_PIN);
  if (time - last_time >= 10 && val != last_val) {
    btn_interrupt++;
    last_val = val;
    last_time = time;
  }

  speed = shift_right_round(analogRead(SPEED_PIN), SPEED_SHIFT);
  brightness = MIN_BRIGHTNESS + shift_right_round(analogRead(BRIGHTNESS_PIN), BRIGHTNESS_SHIFT);
  brightness = min(brightness, MAX_BRIGHTNESS);
}