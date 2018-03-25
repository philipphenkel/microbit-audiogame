#ifndef ADC_SERVICE_H
#define ADC_SERVICE_H

#include "mbed.h"

class AdcService
{
private:
  AnalogIn *pin;
  Timer *timer;

public:
  AdcService(PinName name);

  uint16_t readSample();
  void captureSamples(uint16_t *samples, int count, int sampleRate);
  void captureSamples8Bit(uint8_t *samples, int count, int sampleRate);

private:
  template <class T>
  void capture(T *samples, int count, int sampleRate);
  void read(uint16_t &sample);
  void read(uint8_t &sample);
};

#endif
