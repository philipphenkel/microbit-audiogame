#include "pxt.h"
#include "AdcService.h"
#include "Ticker.h"

using namespace pxt;

namespace zkm
{


AdcService *_pService = NULL;
Action _handler;
Action _testHandler;
Ticker timer;
bool test = false;
int count = 0;
int startMillis = 0;
int endMillis = 0;
bool measureDone = false;



void callTest() {
    if (_testHandler) {
        pxt::runAction0(_testHandler);
    }
}


void captureSamples()
{
    /*
    if (count == 0) {
        startMillis = uBit.systemTime();
    }

    _pService->getSample();

    if (!measureDone) {
        count++;
        int currentMillis = uBit.systemTime();
        if (currentMillis - startMillis > 1000 )  {
            measureDone = true;
            callTest();
        }
    }
*/
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
void onTest(Action handler)
{
    _testHandler = handler;
    pxt::incr(_testHandler);
}


//%
void startAdcService(int adcPin, int sampleRate)
{
    if (NULL != _pService) {
        return;
    }

    MicroBitPin *pin = getPin(adcPin);
    if (!pin) {
        return;
    }

    _pService = new AdcService(pin->name);

    const int sampleInterval_us = 1000000 / sampleRate;
    //timer.attach_us(&captureSamples, sampleInterval_us);
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


//%
int getTest()
{
    return count;
}

}
