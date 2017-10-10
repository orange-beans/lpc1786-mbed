#ifndef PULSE_H
#define PULSE_H

#include "mbed.h"
#include <vector>

// Create a Pulse waveform class
class Pulse {
  public:
    Pulse(PinName pin);
    Pulse(PinName pin, double factor);
    // for Pulse
    void pulseOut(uint16_t n);
    void setPulse(double factor, uint16_t period, uint16_t onPeriod);
  private:
    // calculate the new amplitude (pulse only)
    void updateAmp(double factor);
    AnalogOut _pin;
    uint16_t amplitude;
    uint16_t onLength;
    uint16_t length;
};

#endif
