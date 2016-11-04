#include "SawTooth.h"
#include "mbed.h"

// const uint16_t FIXED_PERIOD = 667;
// const uint16_t FIXED_LENGTH = 1000;

const uint16_t FIXED_PERIOD = 1333;
const uint16_t FIXED_LENGTH = 2000;

// For class init, normal assignment not working
SawTooth::SawTooth(PinName pin, double factor) : _pin(pin) {
  length = FIXED_LENGTH;
  updateTable(factor);
}

// TODO: create a private method to generate waveform table
SawTooth::SawTooth(PinName pin) : _pin(pin) {
  length = FIXED_LENGTH;
  updateTable();
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

void SawTooth::setWave(double factor, uint16_t period) {
  // if (period >= FIXED_PERIOD) {
  //   length = FIXED_LENGTH;
  // } else {
  //   length = period * FIXED_LENGTH / FIXED_PERIOD;
  // }
  length = period * FIXED_LENGTH / FIXED_PERIOD;
  updateTable(factor);
}

// calculate the table
// longer length, higher resolution, longer period
// maximum 1023

void SawTooth::updateTable() {
  table.clear();
  table.resize(length);
  uint16_t amplitude = 65535;
  // Low to high waveform
  // for (int i = 0; i < length; i++) {
  //   // scale to amplitude range
  //   table[i] = i * amplitude / length;
  // }
  // High to low waveform
  for (int i = 0; i < length; i++) {
    // scale to amplitude range
    table[i] = (length - i) * amplitude / length;
  }
}

void SawTooth::updateTable(double factor) {
  table.clear();
  table.resize(length);
  if (factor > 1 || factor <= 0) factor = 1;
  uint16_t amplitude = (uint16_t)(factor * 65535);
  // Low to high waveform
  // for (int i = 0; i < length; i++) {
  //   // scale to amplitude range
  //   table[i] = i * amplitude / length;
  // }
  // High to low waveform
  for (int i = 0; i < length; i++) {
    // scale to amplitude range
    table[i] = (length - i) * amplitude / length;
  }
  printf("length is %d ms\n", length);
  printf("table is %d ms\n", table[1]);
}
