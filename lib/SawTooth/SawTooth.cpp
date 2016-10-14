#include "SawTooth.h"
#include "mbed.h"

// For class init, normal assignment not working
SawTooth::SawTooth(PinName pin, double factor) : _pin(pin) {
  length = 1000;
  amplitude = (uint16_t)(factor * 65535);
  // calculate the table
  // longer length, higher resolution, longer period
  // maximum 1023
  for (int i = 0; i < length; i++) {
    // scale to amplitude range
    table[i] = i * amplitude / length;
  }
}

SawTooth::SawTooth(PinName pin) : _pin(pin) {
  length = 1000;
  amplitude = 65535;
  for (int i = 0; i < length; i++) {
    // scale to amplitude range
    table[i] = i * amplitude / length;
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

void SawTooth::setWave(double factor) {
  amplitude = (uint16_t)(factor * 65535);
  for (int i = 0; i < length; i++) {
    // scale to amplitude range
    table[i] = i * amplitude / length;
  }
}
