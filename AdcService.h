#ifndef ADC_SERVICE_H
#define ADC_SERVICE_H

#include "pxt.h"
#include "mbed.h"

class AdcService
{
private:
  MicroBitPin *pin;
  Timer *timer;

public:
  AdcService(MicroBitPin *pin);

  uint16_t readSample();
  void captureSamples(uint16_t *samples, int count, int sampleRate);
  void captureSamples8Bit(uint8_t *samples, int count, int sampleRate);
  void generateSineSamples(uint16_t *samples, int count, int sampleRate, int frequency);

private:
  template <class T>
  void capture(T *samples, int count, int sampleRate);
  void read(uint16_t &sample);
  void read(uint8_t &sample);
};

#endif
