#include "MicroBitConfig.h"
#include "DtmfService.h"

DtmfService::DtmfService(PinName pin1Name, PinName pin2Name)
{
    this->pwmOut1 = new PwmOut(pin1Name);
    this->pwmOut2 = new PwmOut(pin2Name);
}

void DtmfService::playTone(int frequency1, int frequency2, int duration)
{
    this->pwmOut1->period_us(1000000 / 900);
    this->pwmOut1->pulsewidth_us(1000000 / 1800);
    //this->pwmOut1->period_us(1000000 / 900);
    //this->pwmOut1->pulsewidth_us(1000000 / (900 >> 1));

    //this->pwmOut2->period_us(1000000 / 900);
    //this->pwmOut2->pulsewidth_us(1000000 / (900 >> 1));

    this->toneEndTime = uBit.systemTime() + duration;
}

void DtmfService::process()
{
    if (uBit.systemTime() > this->toneEndTime)
    {
        this->pwmOut1->pulsewidth_us(0);
        this->pwmOut2->pulsewidth_us(0);
    }
}
