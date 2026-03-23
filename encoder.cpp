#include <Arduino.h>

#include "encoder.h"

volatile long count;   // conteggio encoder
static float theta;           // angolo effettivo theta
static uint8_t pinA, pinB;    // pin A, pin B


void begin_encoder(uint8_t pinA_, uint8_t pinB_) {
  count = 0;
  theta = 0;
  pinA = pinA_;
  pinB = pinB_;
  pinMode(pinA, INPUT_PULLUP);
  pinMode(pinB, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(pinA), ISR_A, RISING);
}

void ISR_A() {
  // direzione data dallo stato di B
  if (digitalRead(pinB) == LOW)
    count++;
  else
    count--;
}

float update_theta() {
  static long last_count = 0;
  noInterrupts();
  long c = count;
  interrupts();
  if ( c != last_count ) {
    theta        = count * DTHETA;
    last_count   = c;
  }
  return theta;
}
