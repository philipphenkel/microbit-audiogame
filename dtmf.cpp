#include "pxt.h"
#include "DtmfService.h"
#include "Ticker.h"

using namespace pxt;

namespace zkm
{


DtmfService *_dtmfService = NULL;
Ticker dtmfTimer;

void playTones()
{
    _dtmfService->process();
}

//%
void startDtmfService(int dtmfPin1, int dtmfPin2)
{
    if (NULL != _dtmfService) {
        return;
    }

    MicroBitPin *pin1 = getPin(dtmfPin1);
    if (!pin1) {
        return;
    }
    MicroBitPin *pin2 = getPin(dtmfPin2);
    if (!pin2)
    {
        return;
    }

    _dtmfService = new DtmfService(pin1->name, pin2->name);

    dtmfTimer.attach_us(&playTones, 5 * 100000);
}

//%
void playTone(int frequence1, int frequence2, int duration)
{
    if (NULL == _dtmfService) {
        return;
    }
    _dtmfService->playTone(frequence1, frequence2, duration);
}

}
