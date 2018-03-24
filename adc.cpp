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
bool test = false;
int count = 0;
int startMillis = 0;
int endMillis = 0;
bool measureDone = false;
int _magnitude = 0;
const int checkIntervalMillis = 5000;
int lastDtmfCheckMillis = 0;
}

void callTest()
{
    if (_testHandler)
    {
        pxt::runAction0(_testHandler);
    }
}

/* When a sample is taken, do calculations, and get frequency if ready 


void Goertzel::sample(int sensorPin)
{
  for (int index = 0; index < _N; index++)
  {
    testData[index] = analogRead(sensorPin);
  }
}


float Goertzel::detect()
{
  float	magnitude;

  for (int index = 0; index < _N; index++)
  {
    ProcessSample(testData[index]);
  }

  magnitude = sqrt(Q1*Q1 + Q2*Q2 - coeff*Q1*Q2);

  ResetGoertzel();
  return magnitude;
}


*/

//%
uint16_t getSample()
{
    if (NULL == _pService)
    {
        return -1;
    }
    return _pService->getSample();
}

void detectAndNotifyDtmf() {
    int currentMillis = uBit.systemTime();
    if (currentMillis - lastDtmfCheckMillis > checkIntervalMillis) {
        lastDtmfCheckMillis = uBit.systemTime();
        zkm::notifyToneDetected(DtmfTone::Tone_1);
    }
}

void processSample(uint16_t sample)
{
    for (int i=0; i<4; i++) {
        _goertzels[i]->processSample(sample);
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

    processSample(getSample());
    detectAndNotifyDtmf();
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
    _goertzels[1] = new Goertzel(FREQ_L2, 20, sampleRate);
    _goertzels[2] = new Goertzel(FREQ_L3, 20, sampleRate);
    _goertzels[3] = new Goertzel(FREQ_L4, 20, sampleRate);
    _goertzels[4] = new Goertzel(FREQ_H1, 20, sampleRate);
    _goertzels[5] = new Goertzel(FREQ_H2, 20, sampleRate);
    _goertzels[6] = new Goertzel(FREQ_H3, 20, sampleRate);
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
