#ifndef TIMEMANAGER_H
#define TIMEMANAGER_H

#define MAXF 100 * 1000.0f             // basically 100 kHz or Tsample = 10 microseconds. Realistically much more than useful but if you REALLY have a faster board modify this

extern float         sampl_freq;    // Hz
extern unsigned long samplT;        // microseconds
extern unsigned long lastT;         // microseconds
extern uint8_t       flag;          // it is the way you inteface with the library, the value of "flag" is a value among SamplerState values

enum SamplerState : uint8_t {
  NOMINAL      , // all good, frequency is within bounds
  FREQTOOHIGH  , // frequency is too high, MAXF will be used instead
  NEGATIVEFREQ , // frequency is negative. If lower (in module) then MAXF I just remove the sign, otherwise I use MAXF
  BYPASS         // basically I'm using the max possible frequency allowed by the board. It's exactly the same as not using the library and just letting the board live its course.

void            beginSampler(float freq);    // used in the setup() functions
bool            sample();                    // used in the loop()
int             returnFlag();                // used for debug or setup checks
float           returnSamplingFrequency();   
unsigned long   time_now();                  // internal function, ideally never used outside, it asks the board for the time at the moment

#endif
