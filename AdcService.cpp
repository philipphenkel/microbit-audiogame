#include "MicroBitConfig.h"
#include "AdcService.h"

AdcService::AdcService(MicroBitPin *pin)
{
    this->pin = pin;
    pin->getAnalogValue();
    timer = new Timer();
}

AdcService::~AdcService() {
    delete timer, timer = 0;
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

void AdcService::generateSineSamples(uint16_t *samples, int count, int sampleRate, int frequency)
{
    float step = ((float)frequency) * ((2.0 * PI) / ((float)sampleRate));

    for (int index = 0; index < count; index++)
    {
        samples[index] = (uint16_t)(100.0f * sin(index * step) + 100.0);
    }
}

template <class T>
void AdcService::capture(T *samples, int count, int sampleRate)
{
    const int readInterval_us = 1000000 / sampleRate;
    int nextReadTimestamp = readInterval_us;
    timer->start();
    timer->reset();
    for (int i = 0; i < count; ++i, nextReadTimestamp += readInterval_us)
    {
        read(samples[i]);
        while (timer->read_us() < nextReadTimestamp)
        {
            ;
        }
    }

    /*
    int dur = timer->read_us();
    int sr = 1000000.0f / ((1.0f * dur) / count);
    printf("capture %d/%d us %d/%d Hz\n", dur, count * readInterval_us, sr, sampleRate);
    */

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
