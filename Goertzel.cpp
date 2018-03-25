#include "Goertzel.h"

#define ADCCENTER 512

Goertzel::Goertzel(float targetFrequency, float N, float samplingRate)
{
    this->samplingRate = samplingRate;
    this->targetFrequency = targetFrequency;
    this->N = N;
    float k = (int)(0.5 + ((N * targetFrequency) / samplingRate));
    float omega = (2.0 * PI * k) / N;
    coeff = 2.0 * cos(omega);
    q1 = 0;
    q2 = 0;
}

void Goertzel::reset(void)
{
    q2 = 0;
    q1 = 0;
}

void Goertzel::processSamples(uint16_t *samples)
{
    for (int i = 0; i < (int)N; i++)
    {
        float q0 = coeff * q1 - q2 + (samples[i] - 511); // -AdcCenter???
        q2 = q1;
        q1 = q0;
    }
}

int Goertzel::getMagnitudeSquared()
{
    return (int)(q1 * q1 + q2 * q2 - q1 * q2 * coeff);
}
