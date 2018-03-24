#include "MicroBitConfig.h"
#include "dtmfService.h"

namespace zkm
{

DtmfService::DtmfService(PinName pin1Name, PinName pin2Name)
{
    this->pwmOut1 = new PwmOut(pin1Name);
    this->pwmOut2 = new PwmOut(pin2Name);
    this->isPlaying = false;
}

void DtmfService::playTone(TwoTone twoTone, int duration)
{
    this->isPlaying = true;

    this->pwmOut1->period_us(1000000 / twoTone.A);
    this->pwmOut1->pulsewidth_us(1000000 / (twoTone.A << 1));

    this->pwmOut2->period_us(1000000 / twoTone.B);
    this->pwmOut2->pulsewidth_us(1000000 / (twoTone.B << 1));

    this->toneEndTime = uBit.systemTime() + duration;
}

void DtmfService::tick()
{
    if (this->isPlaying && uBit.systemTime() > this->toneEndTime)
    {
        this->isPlaying = false;

        this->pwmOut1->pulsewidth_us(0);
        this->pwmOut2->pulsewidth_us(0);
    }
}
}
