#include "pxt.h"
#include "Ticker.h"
#include "dtmf.h"
#include "AdcService.h"
#include "Goertzel.h"

using namespace pxt;

namespace zkm
{

namespace
{
AdcService *_pService = NULL;
Goertzel *_goertzels[8];
Action _testHandler;
Ticker timer;
const int checkIntervalMillis = 1000;
int lastDtmfCheckMillis = 0;
}



void callTest()
{
    if (_testHandler)
    {
        pxt::runAction0(_testHandler);
    }
}

//%
uint16_t getSample()
{
    if (NULL == _pService)
    {
        return -1;
    }
    return _pService->getSample();
}

inline bool isActive(Goertzel *goertzel)
{
    return goertzel->getMagnitude() > 1000;
}


inline bool isToneActive(DtmfTone tone)
{
    // TwoTone tt = getTwoTone(tone);
    switch(tone) {
        case DtmfTone::Tone_1:
            return isActive(_goertzels[0]) && isActive(_goertzels[1]);
        case DtmfTone::Tone_2:
            return isActive(_goertzels[0]) && isActive(_goertzels[3]);
        default:
            return false;
    }
}

inline void notifyActiveTone(DtmfTone tone)
{
    if (isToneActive(tone))
    {
        zkm::notifyToneDetected(tone);
    }
}

void detectAndNotifyDtmf()
{
    int currentMillis = uBit.systemTime();
<<<<<<< HEAD
    if (currentMillis - lastDtmfCheckMillis > checkIntervalMillis)
    {
=======
    if ((currentMillis - lastDtmfCheckMillis) > checkIntervalMillis) {
>>>>>>> move tick to adc
        lastDtmfCheckMillis = uBit.systemTime();
        notifyActiveTone(DtmfTone::Tone_1);
        notifyActiveTone(DtmfTone::Tone_2);
    }
}

void processSample(uint16_t sample)
{
    for (int i = 0; i < 4; i++)
    {
        _goertzels[i]->processSample(sample);
    }
}

void captureSamples()
{
    processSample(getSample());
    detectAndNotifyDtmf();

    dtmfTick();
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
    if (NULL != _pService)
    {
        return;
    }

    MicroBitPin *pin = getPin(adcPin);
    if (!pin)
    {
        return;
    }

    _pService = new AdcService(pin->name);

    _goertzels[0] = new Goertzel(FREQ_L1, 20, sampleRate);
    _goertzels[1] = new Goertzel(FREQ_H1, 20, sampleRate);
    _goertzels[2] = new Goertzel(FREQ_L2, 20, sampleRate);
    _goertzels[3] = new Goertzel(FREQ_H2, 20, sampleRate);
    _goertzels[4] = new Goertzel(FREQ_L3, 20, sampleRate);
    _goertzels[5] = new Goertzel(FREQ_H3, 20, sampleRate);
    _goertzels[6] = new Goertzel(FREQ_L4, 20, sampleRate);
    _goertzels[7] = new Goertzel(FREQ_H4, 20, sampleRate);

    const int sampleInterval_us = 1000000 / sampleRate;

    timer.attach_us(&captureSamples, sampleInterval_us);
}

//%
void setSampleRate(int rate)
{
    if (NULL == _pService)
    {
        return;
    }
    _pService->setSampleRate(rate);
}

//%
int getTest()
{
    return _goertzels[0]->getMagnitude();
}
}
