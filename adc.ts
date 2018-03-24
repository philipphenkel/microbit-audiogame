
namespace zkm {

    export enum AdcPin {
        P0 = AnalogPin.P0,
        P1 = AnalogPin.P1,
    }

   /**
    * Starts a custom sensor service. The handler must call ``setSensorTemperature`` 
    * to update the temperature sent to the service.
    * @pin value to send over serial, eg. AdcPin.P0
    */
    //% blockId=zkm_start block="start capture from pin %pin "
    export function startCapture(adcPin: AdcPin) {
        startAdcService(adcPin)
    }

    //% shim=zkm::startAdcService
    export function startAdcService(adcPin: number): void { return }

    /**
    * Starts a custom sensor service. The handler must call ``setSensorTemperature`` 
    * to update the temperature sent to the service.
    * @handler action
    */
    //% blockId=zkm_on_sample block="on sample "
    export function onSampleReady(handler: Action) {
        onSample(handler)
    }

    //% shim=zkm::onSample
    export function onSample(handler: Action): void { return }

    /**
     * todo
     */
    //% blockId="zkm_get" block="get "
    export function get(): number {
        return getSample()
    }

    //% shim=zkm::getSample
    export function getSample(): number { return 5 }


}
