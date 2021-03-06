
namespace zkm {

    export enum DtmfPin {
        P0 = AnalogPin.P0,
        P1 = AnalogPin.P1,
        P2 = AnalogPin.P2,
    }

   /**
    */
    //% blockId=zkm_start_dtmf block="start process from pin %dtmfPin1 | and %dtmfPin2"
    export function startProcess(dtmfPin1: DtmfPin, dtmfPin2: DtmfPin) {
        startDtmfService(dtmfPin1, dtmfPin2)
    }

    //% shim=zkm::startDtmfService
    export function startDtmfService(dtmfPin1: number, dtmfPin2: number): void { return }

    /**
     * todo
     */
    //% blockId="zkm_playTone" block="playtone  %tone | for %duration | ms"
    export function play(tone: DtmfTone, duration: number): void {
        return playTone(tone, duration);
    }

    //% shim=zkm::playTone
    export function playTone(tone: DtmfTone, duration: number): void { }

    /**
    * @tone the tone, eg:DtmfTone.Tone_1
    * @handler action
    */
    //% weight=70
    //% blockId=zkm_on_tone block="on detect tone %tone"
    export function onToneDetected(tone: DtmfTone, handler: Action) {
        onTone(tone, handler)
    }

    //% shim=zkm::onTone
    export function onTone(tone: DtmfTone, handler: Action): void { return }

}
