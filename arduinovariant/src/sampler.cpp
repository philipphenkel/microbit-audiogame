#include "sampler.h"

Sampler::Sampler() {}

void Sampler::sample(int sensorPin)
{
  for (int index = 0; index < this->sampleCount; index++)
  {
    this->samples[index] = analogRead(sensorPin);
  }
}
