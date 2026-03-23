#include <Arduino.h>
#include <math.h>
#include "timemanager.h"

#define FREQ_EPS 1e-6

static float         sampl_freq;   // Hz
static unsigned long samplT;       // microseconds
static unsigned long lastT;        // microseconds
static uint8_t       flag;

void beginSampler(float freq) {
  sampl_freq = freq;
  if ( sampl_freq > MAXF ) 
  { sampl_freq = MAXF; flag = FREQTOOHIGH; } // se la frequenza richiesta è oltre la frequenza plausibile, la flag si alza e viene forzata la frequenza massima
  else flag = NOMINAL;
  
  if ( fabs(sampl_freq) < FREQ_EPS ) 
  { sampl_freq = 0; flag = BYPASS; samplT = 0; return; }    // se mando come input 0, praticamente sto chiedendo che il sampling time sia massimo
  
  if ( sampl_freq < -FREQ_EPS ) 
  { sampl_freq = min(fabs(sampl_freq), MAXF); flag = NEGATIVEFREQ; }
  
  samplT     = (unsigned long)( 1e6/sampl_freq ); // tempo di attesa in microseconds
  lastT      = micros();
}

bool sample() {
  if (flag == BYPASS) return true;
  unsigned long now = micros();
  if ( (unsigned long)(now - lastT) >= samplT ) { // questo cast serve per evitare overflow (non che il programma andrà mai per più di 70 minuti ma mai dire mai)
    lastT = now;
    return true;
  }
  return false;
}

int   returnFlag()              {   return flag;         }
float returnSamplingFrequency() {   return sampl_freq;   }

unsigned long time_now()             {   return samplT; }

