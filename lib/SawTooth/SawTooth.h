#ifndef SAWTOOTH_H
#define SAWTOOTH_H

#include "mbed.h"

// Create a SawTooth waveform class
class SawTooth {
  public:
    SawTooth(PinName pin);
    SawTooth(PinName pin, uint16_t num);
    // set length means set resolution,
    // longer length also means longer period
    void setLength(uint16_t length);
    // number of period out
    void waveOut(uint16_t n);
  private:
    AnalogOut _pin;
    uint16_t length;
    uint16_t table[1000] = {};
};

#endif
