#ifndef ADC_SERVICE_H
#define ADC_SERVICE_H

#include "MicroBitConfig.h"
#include "EventModel.h"

#define MICROBIT_ID_ADC 9602
#define MICROBIT_ADC_EVT_UPDATE 2

class AdcService
{
  public:
    AdcService(PinName name);

    void setSampleRate(int rate);
    int getSample();

  private:
};

#endif
