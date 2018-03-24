
namespace zkm {

    export enum AdcPin {
        P0 = AnalogPin.P0,
        P1 = AnalogPin.P1,
    }

   /**
    * Starts sampling
    * @pin value to send over serial, eg: AdcPin.P0
    * @sampleRate in Hz, eg: 4096
    */
    //% blockId=zkm_start block="start capture from pin %pin | with sample rate %sampleRate"
    export function startCapture(adcPin: AdcPin, sampleRate: number) {
        startAdcService(adcPin, sampleRate)
    }

    //% shim=zkm::startAdcService
    export function startAdcService(adcPin: number, sampleRate: number): void { return }

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



    /**
    * test callback
    * @handler action
    */
    //% blockId=zkm_on_test block="on test"
    export function onTestCallback(handler: Action) {
        onTest(handler)
    }

    //% shim=zkm::onTest
    export function onTest(handler: Action): void { return }

    /**
     * todo
     */
    //% blockId="zkm_get_test" block="get test"
    export function getTestValue(): number {
        return getTest()
    }

    //% shim=zkm::getTest
    export function getTest(): number { return 4 }



}
