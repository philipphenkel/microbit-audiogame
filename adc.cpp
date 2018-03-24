#include "pxt.h"
#include "AdcService.h"
#include "Ticker.h"

using namespace pxt;

namespace zkm
{


AdcService *_pService = NULL;
Action _handler;
Ticker timer;
bool test = false;

void captureSamples()
{
  /*  test = !test;

    if (test) {
        uBit.display.printCharAsync('A');
    }
    else {
        uBit.display.printCharAsync('B');
    }
*/
    _pService->getSample();

    if (_handler)
    {
        pxt::runAction0(_handler);
        
        
//        MicroBitEvent ev(MICROBIT_ID_ADC, MICROBIT_ADC_EVT_UPDATE);
    }
}


//%
void onSample(Action handler)
{
    _handler = handler;
    pxt::incr(_handler);
}

//%
void startAdcService(int adcPin)
{
    if (NULL != _pService) {
        return;
    }

    MicroBitPin *pin = getPin(adcPin);
    if (!pin) {
        return;
    }

    _pService = new AdcService(pin->name);

    timer.attach_us(&captureSamples, 5 * 100000);
}

//%
void setSampleRate(int rate)
{
    if (NULL == _pService) {
        return;
    }
    _pService->setSampleRate(rate);
}

//%
int getSample()
{
    if (NULL == _pService) {
        return -1;
    }
    return _pService->getSample();
}

}
