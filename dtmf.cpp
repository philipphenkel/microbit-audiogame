#include "pxt.h"
#include "dtmfService.h"
#include "Ticker.h"
#include "dtmf.h"

using namespace pxt;

namespace zkm
{

static DtmfService *_dtmfService = NULL;
static Ticker dtmfTimer;
static Action _handler[DTMF_TONE_COUNT];

TwoTone DTMFTONES[DTMF_TONE_COUNT] = {
    {FREQ_L1, FREQ_H1}, // DtmfTone::Tone_1
    {FREQ_L1, FREQ_H2}, // DtmfTone::Tone_2
    {FREQ_L1, FREQ_H3}, // DtmfTone::Tone_3
    {FREQ_L2, FREQ_H1}, // DtmfTone::Tone_4
    {FREQ_L2, FREQ_H2}, // DtmfTone::Tone_5
    {FREQ_L2, FREQ_H3}, // DtmfTone::Tone_6
    {FREQ_L3, FREQ_H1}, // DtmfTone::Tone_7
    {FREQ_L3, FREQ_H2}, // DtmfTone::Tone_8
    {FREQ_L3, FREQ_H3}, // DtmfTone::Tone_9
    {FREQ_H4, FREQ_H2}, // DtmfTone::Tone_0
    {FREQ_L1, FREQ_H4}, // DtmfTone::Tone_A
    {FREQ_L2, FREQ_H4}, // DtmfTone::Tone_B
    {FREQ_L3, FREQ_H4}, // DtmfTone::Tone_C
    {FREQ_L4, FREQ_H4}, // DtmfTone::Tone_D
    {FREQ_H4, FREQ_H1}, // DtmfTone::Tone_STAR
    {FREQ_H4, FREQ_H3}, // DtmfTone::Tone_HASH
};

void playTones()
{
    _dtmfService->process();
}

//%
void startDtmfService(int dtmfPin1, int dtmfPin2)
{
    if (NULL != _dtmfService)
    {
        return;
    }

    MicroBitPin *pin1 = getPin(dtmfPin1);
    if (!pin1)
    {
        return;
    }
    MicroBitPin *pin2 = getPin(dtmfPin2);
    if (!pin2)
    {
        return;
    }

    _dtmfService = new DtmfService(pin1->name, pin2->name);

    dtmfTimer.attach_us(&playTones, 5 * 10000);
}

//%
void playTone(DtmfTone tone, int duration)
{
    if (NULL == _dtmfService)
    {
        return;
    }
    TwoTone twoTone = DTMFTONES[tone];

    _dtmfService->playTone(twoTone, duration);
}

//%
void onTone(DtmfTone tone, Action handler)
{
    _handler[tone] = handler;
    pxt::incr(_handler[tone]);
}


void notifyToneDetected(DtmfTone tone)
{
    Action handler = _handler[tone];
    if (handler)
    {
        pxt::runAction0(handler);
    }
}

}