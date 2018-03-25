#include "pxt.h"

#ifndef GOERTZEL_H
#define GOERTZEL_H

class Goertzel
{
    float samplingRate;
    float targetFrequency;
    float coeff;
    float q1;
    float q2;
    float N;
    int lastMagnitude;
    int count;

  public:
    Goertzel(float,float,float);
    Goertzel(float,float);
	void processSamples(uint16_t *samples);
	void reset(void);
    int getMagnitudeSquared();

};

#endif
