#include "MicroBitConfig.h"
#include "AdcService.h"


AdcService::AdcService(PinName name)
{
    pin = new AnalogIn(name);
}

void AdcService::setSampleRate(int)
{
}

uint16_t AdcService::getSample()
{
    return pin->read_u16() >> 2;
}
