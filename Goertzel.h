#include "pxt.h"

#ifndef GOERTZEL_H
#define GOERTZEL_H

class Goertzel
{
    float samplingFrequency;
    float frequencyToDetect;
    float scalingFactor;
    float coeff;
    float Q1;
    float Q2;
    int N;
    int lastMagnitude;
    int count;

  public:
    Goertzel(float,float,float);
    Goertzel(float,float);
	bool processSample(uint16_t);
	void resetGoertzel(void);
    int getMagnitude();

};

#endif
