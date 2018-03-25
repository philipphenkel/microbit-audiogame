#include "MicroBitConfig.h"
#include "AdcService.h"

AdcService::AdcService(MicroBitPin *pin)
{
    this->pin = pin;
    pin->getAnalogValue();
    timer = new Timer();
}

uint16_t AdcService::readSample()
{
    return pin->getAnalogValue();
}

void AdcService::captureSamples(uint16_t *samples, int count, int sampleRate)
{
    capture(samples, count, sampleRate);
}

void AdcService::captureSamples8Bit(uint8_t *samples, int count, int sampleRate)
{
    capture(samples, count, sampleRate);
}

template <class T>
void AdcService::capture(T *samples, int count, int sampleRate)
{
    const int readInterval_us = 1000000 / sampleRate;
    timer->start();
    for (int i = 0; i < count; ++i)
    {
        timer->reset();
        read(samples[i]);
        while (timer->read_us() < readInterval_us)
        {
            ;
        }
    }
    timer->stop();
}

void AdcService::read(uint16_t &sample)
{
    sample = pin->getAnalogValue();
}

void AdcService::read(uint8_t &sample)
{
    sample = pin->getAnalogValue() >> 2;
}
