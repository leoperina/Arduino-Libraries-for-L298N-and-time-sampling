#ifndef TIMEMANAGER_H
#define TIMEMANAGER_H

#define MAXF 100 * 1000.0f             // basically 100 kHz, ovvero Tsample = 10 microseconds. Realistitcamente questa frequeza è già troppo alta per essere seguita, e al netto sarebbe come chiedere BYPASS

extern float         sampl_freq;    // Hz
extern unsigned long samplT;        // microseconds
extern unsigned long lastT;         // microseconds
extern uint8_t       flag;          // è il modo in cui ci si interfaccia fra l'user e la libreria. Per capire cosa è cosa vedi flags

enum SamplerState : uint8_t {
  NOMINAL      , // tutto a posto, la frequenza in input è entro i limiti
  FREQTOOHIGH  , // la frequenza richiesta è oltre la massima consentita, verrà usata MAXF
  NEGATIVEFREQ , // la frequenza in input è negativa, provo ad invertirla e usarla, se è troppo alta uso MAXF
  BYPASS         // la frequenza in input è zero. Lo prendo come un bypass a sample(), praticamente sto chiedendo la massima frequenza di campionamento possibile (rischiando però non sia costante per qual si voglia ragione)
};

void            beginSampler(float freq);
bool            sample();
int             returnFlag();
float           returnSamplingFrequency();
unsigned long   time_now();

#endif
