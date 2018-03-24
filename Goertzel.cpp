#include "Goertzel.h"

#define ADCCENTER 512

Goertzel::Goertzel(float frequencyToDetect, float N, float samplingFrequency)
{
    this->samplingFrequency = samplingFrequency;
    this->frequencyToDetect = frequencyToDetect;
    this->N = N;
    float omega = (2.0 * PI * frequencyToDetect) / samplingFrequency;
    coeff = 2.0 * cos(omega);
    Q1 = 0;
    Q2 = 0;
    count = 0;
}

void Goertzel::resetGoertzel(void)
{
    count = 0;
    Q2 = 0;
    Q1 = 0;
}

bool Goertzel::processSample(uint16_t sample)
{
    count++;
    float Q0 = coeff * Q1 - Q2 + ((float)sample - ADCCENTER);
    Q2 = Q1;
    Q1 = Q0;
    if (count >= N) {
        lastMagnitude = (Q1 * Q1 + Q2 * Q2 - coeff * Q1 * Q2); // no sqrt
        resetGoertzel();
        return true;
    }
    return false;
}

int Goertzel::getMagnitude()
{
    return lastMagnitude;
}

