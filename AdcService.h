#ifndef ADC_SERVICE_H
#define ADC_SERVICE_H

#include "pxt.h"
#include "mbed.h"

class AdcService
{
private:
  MicroBitPin *pin;
  int measuredSampleRate;

public:
  AdcService(MicroBitPin *pin);

  uint16_t readSample();
  void captureSamples(uint16_t *samples, int count);
  void captureSamples8Bit(uint8_t *samples, int count);

private:
  template <class T>
  void capture(T *samples, int count);
  void read(uint16_t &sample);
  void read(uint8_t &sample);
};

#endif
