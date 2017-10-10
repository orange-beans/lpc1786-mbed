#include "Pulse.h"
#include "mbed.h"

// const uint16_t FIXED_PERIOD = 667;
// const uint16_t FIXED_LENGTH = 1000;

const uint16_t FIXED_PERIOD = 1333;
const uint16_t FIXED_LENGTH = 2000;

// For class init, normal assignment not working
Pulse::Pulse(PinName pin, double factor) : _pin(pin) {
  updateAmp(factor);
}

Pulse::Pulse(PinName pin) : _pin(pin) {
  updateAmp(0.1);
}

void Pulse::pulseOut(uint16_t n = 0) {
  // Run for n cycles
  for ( int j = 0; j < n; j++) {
    // This is a single-shot pulse
    _pin.write_u16(amplitude);
    wait_us(onLength);
    _pin.write_u16(0);
    wait_us(length - onLength);
  }
}

void Pulse::setPulse(double factor = 0.1, uint16_t period = 1000, uint16_t onPeriod = 10) {
  if (factor > 1) factor = 1;
  if (factor <= 0) factor = 0;
  if (onPeriod >= period) onPeriod = 0;
  amplitude = (uint16_t)(factor * 65535);
  length = period;
  onLength = onPeriod;
}

void Pulse::updateAmp(double factor = 0.1) {
  if (factor > 1) factor = 1;
  if (factor <= 0) factor = 0;
  amplitude = (uint16_t)(factor * 65535);
}
