#include "MicroBitConfig.h"
#include "AdcService.h"

AdcService::AdcService(MicroBitPin *pin)
{
    this->pin = pin;
    pin->getAnalogValue();
}

uint16_t AdcService::readSample()
{
    return pin->getAnalogValue();
}

void AdcService::captureSamples(uint16_t *samples, int count)
{
    capture(samples, count);
}

void AdcService::captureSamples8Bit(uint8_t *samples, int count)
{
    capture(samples, count);
}

template <class T>
void AdcService::capture(T *samples, int count)
{
    unsigned long start = uBit.systemTime();
    for (int i = 0; i < count; ++i)
    {
        read(samples[i]);
    }
    unsigned long end = uBit.systemTime();
    unsigned long duration = end - start;
    measuredSampleRate = (int)count / (duration / 1000);
}

void AdcService::read(uint16_t &sample)
{
    sample = pin->getAnalogValue();
}

void AdcService::read(uint8_t &sample)
{
    sample = pin->getAnalogValue() >> 2;
}
