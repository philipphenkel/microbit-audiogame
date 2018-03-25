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
const int checkIntervalMillis = 200;
int _threshold = 1000;
int _sampleRate = 8000;
uint16_t *_samples = NULL;
int N = 205;
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
    return _pService->readSample();
}

inline bool isActive(Goertzel *goertzel)
{
    return goertzel->getMagnitudeSquared() > _threshold;
}

Goertzel *frequencyToGoertzel(int frequency)
{
    switch (frequency)
    {
    case FREQ_L1:
        return _goertzels[0];
    case FREQ_L2:
        return _goertzels[1];
    case FREQ_L3:
        return _goertzels[2];
    case FREQ_L4:
        return _goertzels[3];
    case FREQ_H1:
        return _goertzels[4];
    case FREQ_H2:
        return _goertzels[5];
    case FREQ_H3:
        return _goertzels[6];
    case FREQ_H4:
        return _goertzels[7];
    }

    return NULL;
}

inline bool isToneActive(DtmfTone tone)
{
    TwoTone tt = getTwoTone(tone);
    return isActive(frequencyToGoertzel(tt.A)) && isActive(frequencyToGoertzel(tt.B));
}

inline void notifyActiveTone(DtmfTone tone)
{
    if (isToneActive(tone))
    {
        zkm::notifyToneDetected(tone);
    }
}

void processSamples()
{
    for (int i = 0; i < 8; i++)
    {
        _goertzels[i]->reset();
        _goertzels[i]->processSamples(_samples);
    }
}

void detectAndNotifyDtmf()
{
    processSamples();
    notifyActiveTone(DtmfTone::Tone_1);
    notifyActiveTone(DtmfTone::Tone_2);
}

void detectTones()
{
    while(true) {
        _pService->captureSamples(_samples, N, _sampleRate);
        //_pService->generateSineSamples(_samples, N, _sampleRate, 1000);
        schedule();
        detectAndNotifyDtmf();
        fiber_sleep(checkIntervalMillis);
    }
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

    _pService = new AdcService(pin);

    _goertzels[0] = new Goertzel(FREQ_L1, N, sampleRate);
    _goertzels[1] = new Goertzel(FREQ_L2, N, sampleRate);
    _goertzels[2] = new Goertzel(FREQ_L3, N, sampleRate);
    _goertzels[3] = new Goertzel(FREQ_L4, N, sampleRate);
    _goertzels[4] = new Goertzel(FREQ_H1, N, sampleRate);
    _goertzels[5] = new Goertzel(FREQ_H2, N, sampleRate);
    _goertzels[6] = new Goertzel(FREQ_H3, N, sampleRate);
    _goertzels[7] = new Goertzel(FREQ_H4, N, sampleRate);

    _sampleRate = sampleRate;
    _samples = new uint16_t[N];

    create_fiber(detectTones);
}

//%
void setThreshold(int threshold)
{
    _threshold = threshold;
}

//%
void onTest(Action handler)
{
    _testHandler = handler;
    pxt::incr(_testHandler);
}

//%
int getTest()
{
    printf("getTest2\n");
    return _pService->readSample();
}

//%
int getGoertzel(int index)
{
    return _goertzels[index]->getMagnitudeSquared();
}
}
