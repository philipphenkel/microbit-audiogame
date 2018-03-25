/* DTMF encoder (Dual Tone Generator) for a Phone Dialer
 *  Created by David Dubins, May 13th, 2016.
 *  Released into the public domain.
 *
 * SETUP:
 * - Connect Pins 12 and 13 to the + speaker terminal, each through their own 240 Ohm resistor
 * - Connect a 4.7 uF capacitor between the + and - terminals of the speaker
 * - Connect speaker GND to Arduino GND
 * - Connect a momentary switch to Pin 8, and the other side of the switch to GND
 */

 #include "dtmf.h"

// frequencies adopted from: https://en.wikipedia.org/wiki/Dual-tone_multi-frequency_signaling
int DTMFTones[13][2] = {
    {941, 1336}, // frequencies for touch tone 0
    {697, 1209}, // frequencies for touch tone 1
    {697, 1336}, // frequencies for touch tone 2
    {697, 1477}, // frequencies for touch tone 3
    {770, 1209}, // frequencies for touch tone 4
    {770, 1336}, // frequencies for touch tone 5
    {770, 1477}, // frequencies for touch tone 6
    {852, 1209}, // frequencies for touch tone 7
    {852, 1336}, // frequencies for touch tone 8
    {852, 1477}, // frequencies for touch tone 9
    {941, 1209}, // frequencies for touch tone *
    {941, 1477}, // frequencies for touch tone #
    {0, 0}       // pause
};

DTMF::DTMF(int pin1, int pin2)
{
  this->pin1 = pin1;
  this->pin2 = pin2;

  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
}

void DTMF::playDTMF(int digit, int duration)
{
    boolean tone1state = false;
    boolean tone2state = false;
    int tone1delay = (500000 / DTMFTones[digit][0]) - 10; // calculate delay (in microseconds) for tone 1 (half of the period of one cycle). 10 is a fudge factor to raise the frequency due to sluggish timing.
    int tone2delay = (500000 / DTMFTones[digit][1]) - 10; // calculate delay (in microseconds) for tone 2 (half of the period of one cycle). 10 is a fudge factor to raise the frequency due to sluggish timing.
    unsigned long tone1timer = micros();
    unsigned long tone2timer = micros();
    unsigned long timer = millis(); // for timing duration of a single tone
    if (digit == 12)
    {
        delay(1000); // one second delay if digit is 12
    }
    else
    {
        while (millis() - timer < duration)
        {
            if (micros() - tone1timer > tone1delay)
            {
                tone1timer = micros();    // reset the timer
                tone1state = !tone1state; // toggle tone1state
                digitalWrite(this->pin1, tone1state);
            }
            if (micros() - tone2timer > tone2delay)
            {
                tone2timer = micros();    // reset the timer
                tone2state = !tone2state; // toggle tone2state
                digitalWrite(this->pin2, tone2state);
            }
        }
        digitalWrite(this->pin1, LOW);
        digitalWrite(this->pin2, LOW);
    }
}
