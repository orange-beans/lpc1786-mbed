#include "SawTooth.h"
#include "mbed.h"

// For class init, normal assignment not working
SawTooth::SawTooth(PinName pin, uint16_t num) : _pin(pin) {
  length = num;
  // calculate the table
  // longer length, higher resolution, longer period
  // maximum 1023
  for (int i = 0; i < length; i++) {
    // scale to full range
    table[i] = i * 65535 / length;
  }
}

SawTooth::SawTooth(PinName pin) : _pin(pin) {
  length = 1000;
  for (int i = 0; i < length; i++) {
    // scale to full range
    table[i] = i * 65535 / length;
  }
}

void SawTooth::waveOut(uint16_t n) {
  // Run for n times
  for ( int j = 0; j < n; j++) {
    // This is a single-shot wave
    for(int i = 0; i < length; i++) {
      _pin.write_u16(table[i]);
    }
  }
}
