
namespace zkm {

    export enum AdcPin {
        P0 = AnalogPin.P0,
        P1 = AnalogPin.P1,
    }

   /**
    * Starts sampling
    * @pin value to send over serial; eg: AdcPin.P0
    * @sampleRate in Hz; eg: 8000
    */
    //% weight=80
    //% blockId=zkm_start block="start capture from pin %pin | with sample rate %sampleRate"
    export function startCapture(adcPin: AdcPin, sampleRate: number) {
        startAdcService(adcPin, sampleRate)
    }

    //% shim=zkm::startAdcService
    export function startAdcService(adcPin: number, sampleRate: number): void { return }

    /**
     * todo
     */
    //% blockId="zkm_get" block="get sample"
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

   /**
    * test
    * @threshold threshold, eg: 1000
    */
    //% weight=80
    //% blockId=zkm_threshold block="set threshold %threshold"
    export function setGoertzelThreshold(threshold: number) {
        setThreshold(threshold)
    }

    //% shim=zkm::setThreshold
    export function setThreshold(threshold: number): void { return }


    /**
     * todo
     */
    //% blockId="zkm_get_goertzel" block="get goertzel %index"
    export function getGoertzelValue(index: number): number {
        return getGoertzel(index)
    }

    //% shim=zkm::getGoertzel
    export function getGoertzel(index: number): number { return 23 }

}
