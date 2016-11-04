#ifndef SAWTOOTH_H
#define SAWTOOTH_H

#include "mbed.h"
#include <vector>

// Create a SawTooth waveform class
class SawTooth {
  public:
    SawTooth(PinName pin);
    SawTooth(PinName pin, double factor);
    // set length means set resolution,
    // longer length also means longer period
    void setLength(uint16_t length);
    // output the waveForm
    void waveOut(uint16_t n);
    // dynamically re-calculate the waveForm table
    void setWave(double factor, uint16_t period);
  private:
    // calculate waveform table
    void updateTable();
    void updateTable(double factor);
    AnalogOut _pin;
    uint16_t length;
    std::vector<uint16_t> table;
};

#endif
