#ifndef dtmf_h
#define dtmf_h

#include "Arduino.h"

class DTMF
{
private:
  int pin1;
  int pin2;

public:
  DTMF(int pin1, int pin2);
  void playDTMF(int digit, int duration);
};

#endif
