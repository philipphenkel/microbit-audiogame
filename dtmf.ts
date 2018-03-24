
namespace zkm {

    export enum DtmfPin {
        P0 = AnalogPin.P0,
        P1 = AnalogPin.P1,
        P2 = AnalogPin.P2,
    }

   /**
    * Starts a custom sensor service. The handler must call ``setSensorTemperature`` 
    * to update the temperature sent to the service.
    * @pin value to send over serial, eg. DtmfPin.P0
    */
    //% blockId=zkm_start_dtmf block="start process from pin %dtmfPin1 and %dtmfPin2 "
    export function startProcess(dtmfPin1: DtmfPin, dtmfPin2: DtmfPin) {
        startDtmfService(dtmfPin1, dtmfPin2)
    }

    //% shim=zkm::startDtmfService
    export function startDtmfService(dtmfPin1: number, dtmfPin2: number): void { return }

    /**
     * todo
     */
    //% blockId="zkm_playTone" block="playtone  %tone for %duration ms"
    export function play(tone: number, duration: number): void {
        return playTone(tone, duration);
    }

    //% shim=zkm::playTone
    export function playTone(tone: number, duration: number): void { }


}