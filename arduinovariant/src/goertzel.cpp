/*
  The Goertzel algorithm is long standing so see
  http://en.wikipedia.org/wiki/Goertzel_algorithm for a full description.
  It is often used in DTMF tone detection as an alternative to the Fast
  Fourier Transform because it is quick with low overheard because it
  is only searching for a single frequency rather than showing the
  occurrence of all frequencies.

  This work is entirely based on the Kevin Banks code found at
  http://www.embedded.com/design/configurable-systems/4024443/The-Goertzel-Algorithm
  so full credit to him for his generic implementation and breakdown. I've
  simply massaged it into an Arduino library. I recommend reading his article
  for a full description of whats going on behind the scenes.

  Created by Jacob Rosenthal, June 20, 2012.
  Released into the public domain.
*/
// include core Wiring API
#include "Arduino.h"

// include this library's description file
#include "Goertzel.h"

float _SAMPLING_FREQUENCY;
float _TARGET_FREQUENCY;
float coeff;
float Q1;
float Q2;

Goertzel::Goertzel(float TARGET_FREQUENCY, float SAMPLING_FREQUENCY)
{
  _SAMPLING_FREQUENCY = SAMPLING_FREQUENCY;	//on 16mhz, ~8928.57142857143, on 8mhz ~44444
  _TARGET_FREQUENCY = TARGET_FREQUENCY; //should be integer of SAMPLING_RATE/N

  float omega = (2.0 * PI * _TARGET_FREQUENCY) / _SAMPLING_FREQUENCY;

  coeff = 2.0 * cos(omega);

  ResetGoertzel();
}

/* Call this routine before every "block" (size=N) of samples. */
void Goertzel::ResetGoertzel(void)
{
  Q2 = 0;
  Q1 = 0;
}


/* Call this routine for every sample. */
void Goertzel::ProcessSample(int sample)
{
  float Q0;
  Q0 = coeff * Q1 - Q2 + (float) (sample - ADCCENTER);
  Q2 = Q1;
  Q1 = Q0;
}


float Goertzel::detect(int *samples, int sampleCount)
{
  float	magnitude;

  for (int index = 0; index < sampleCount; index++)
  {
    ProcessSample(samples[index]);
  }

  /* Do the "standard Goertzel" processing. */
  magnitude = sqrt(Q1*Q1 + Q2*Q2 - coeff*Q1*Q2);

  ResetGoertzel();
  return magnitude;
}
