#ifndef DTMF_SERVICE_H
#define DTMF_SERVICE_H

#include "MicroBitConfig.h"
#include "EventModel.h"
#include "PwmOut.h"
#include "pxt.h"
#include "dtmf.h"

#define MICROBIT_ID_DTMF 9602
#define MICROBIT_DTMF_EVT_UPDATE 2

class DtmfService
{
    PwmOut *pwmOut1;
    PwmOut *pwmOut2;
    unsigned long toneEndTime;

  public:
    DtmfService(PinName pin1Name, PinName pin2Name);

    void playTone(TwoTone tone, int duration);

    void process();

  private:
};

#endif
