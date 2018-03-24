#include "pxt.h"
#include "Ticker.h"
#include "dtmf.h"
#include "AdcService.h"
#include "Goertzel.h"

using namespace pxt;

namespace zkm
{

AdcService *_pService = NULL;
Goertzel *_pGoertzel = NULL;
Action _handler;
Action _testHandler;
Ticker timer;
bool test = false;
int count = 0;
int startMillis = 0;
int endMillis = 0;
bool measureDone = false;
int _magnitude = 0;

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

void handleSample(uint16_t sample)
{
    _pGoertzel->processSample(sample);
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
    zkm::notifyToneDetected(DtmfTone::Tone_1);
    handleSample(getSample());

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
    _pGoertzel = new Goertzel(697, 20, sampleRate);

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
    return _pGoertzel->getMagnitude();
}
}
