#ifndef sampler_h
#define sampler_h

#include "Arduino.h"

class Sampler
{
public:
  Sampler();

  // if you're trying to detect several different drum hits all within low frequency like
  // ~100-200hz you'll need a small bin size like 25 or 50 to distinguish them.
  // If however you're just trying to find ANY bass hit you might want something
  // basically equal to frequency youre looking for like ~100

  // If Im detecting a frequency much higher with no care about nearby tones, like 2000hz
  // Ill set to a round divisor like 200 So 1900 to 2100 could trigger, but not less or more
  // Max is 200 as we have limited ram in the Arduino, and sampling longer would make us less
  // responsive anyway
  int sampleCount = 100;
  int samples[200];

  void sample(int sensorPin);
};

#endif
