/*
  Blinks built in pin13 LED on a 16mhz Arduino when it detects a 700 hz tone
  which is inside of 1, 2, and 3 buttons (but not the others) on your phone's keypad,
  Othwerise google for a tone generator on the web or an app for your phone.
  I like this one http://onlinetonegenerator.com/

  Frequency sampling is .. squishy business. Be prepared to mess with the
  numbers below until you get something you like.

  This work is entirely based on the Kevin Banks code found at
  http://www.embedded.com/design/embedded/4024443/The-Goertzel-Algorithm
  so full credit to him for his generic implementation and breakdown. I've
  simply massaged it into an Arduino library. I recommend reading his article
  for a full description of whats going on behind the scenes.

  The Goertzel algorithm is long standing so see
  http://en.wikipedia.org/wiki/Goertzel_algorithm for a full description.
  It is often used in DTMF tone detection as an alternative to the Fast
  Fourier Transform because it is quick with low overheard because it
  is only searching for a single frequency rather than showing the
  occurrence of all frequencies.

  If what you really want is DTMF tone detection see el_supremo's fork of
  this library at http://forum.arduino.cc/index.php/topic,121540.0.html

  To use, you'll want a microphone not unlike this electret from Sparkfun
  https://www.sparkfun.com/products/9964 with AVD plugged to A0, VCC to 5V, and GND to GND

  See Contributors.md and add yourself for pull requests
  Released into the public domain.
*/
#include "Goertzel.h"
#include "dtmf.h"
#include "sampler.h"

int sensorPin = 0;
int speakerPin1 = 1;
int speakerPin2 = 2;

int button1pin = 5;
int button2pin = 11;

int col1 = 3;
int col2 = 4;
int led = 26;

// ideally an integer of SAMPLING_FREQUENCY/N to center the bins around your content so if you're
// looking for 700hz, frequencies below and above it equally contribute. Read up on Kevin's article
// for more info.
// Nyquist says the highest frequency we can target is SAMPLING_FREQUENCY/2
const float TARGET_FREQUENCY = 700;


// This is what will trigger the led. Its INCREDIBLY squishy based on volume of your source,
// frequency, etc. You'll just need to get in your environment and look at the serial console
// to start. Then pick something that triggers pleasantly to your eye.
const float THRESHOLD = 1000;

// Again, the highest frequency we can target is SAMPLING_FREQUENCY/2. So Since Arduino is
// relatively slow in terms of audio, we sample literally as fast as we can
// This is generally around ~8900hz for a 16mhz Arduino and 4400hz for an 8mhz Arduino.
// User nicola points out these rates are for stock arduino firmware and that on a board
// by board basis you can juice the adc rates. For Arduino Uno you could move that rate up to
// 22khz by adding somthing like this to your setup:
//  _SFR_BYTE(ADCSRA) |=  _BV(ADPS2); // Set ADPS2
//  _SFR_BYTE(ADCSRA) &= ~_BV(ADPS1); // Clear ADPS1
//  _SFR_BYTE(ADCSRA) &= ~_BV(ADPS0); // Clear ADPS0
const float SAMPLING_FREQUENCY = 8900;

Sampler* sampler = new Sampler();

Goertzel goertzel1 = Goertzel(697, SAMPLING_FREQUENCY, sampler);
//Goertzel goertzel2 = Goertzel(1209, SAMPLING_FREQUENCY, sampler);
DTMF dtmf = DTMF(speakerPin1, speakerPin2);

void setup() {
  pinMode(button1pin, INPUT);
  pinMode(button2pin, INPUT);

  pinMode(speakerPin1, OUTPUT);
  pinMode(speakerPin2, OUTPUT);

  pinMode(col1, OUTPUT);
  digitalWrite(col1, LOW);
  pinMode(col2, OUTPUT);
  digitalWrite(col2, HIGH);

  pinMode(led, OUTPUT);

  Serial.begin(9600);
}

void loop()
{
  sampler->sample(sensorPin);

  float magnitude1 = goertzel1.detect();
  //float magnitude2 = goertzel2.detect();

  if(magnitude1 > THRESHOLD) { //if you're getting false hits or no hits adjust this
    digitalWrite(led, HIGH); //if found, enable led
  } else {
    digitalWrite(led, LOW); //if not found, or lost, disable led
  }

  Serial.print(magnitude1);
  //Serial.print(" - ");
  //Serial.print(magnitude2);
  Serial.println();

  if (digitalRead(button1pin) == LOW) {
    dtmf.playDTMF(0, 500);
    digitalWrite(col1, HIGH);
    digitalWrite(col2, LOW);
    digitalWrite(led, HIGH);
  } else {
    digitalWrite(col1, LOW);
    digitalWrite(col2, HIGH);
    digitalWrite(led, LOW);
  }
}
