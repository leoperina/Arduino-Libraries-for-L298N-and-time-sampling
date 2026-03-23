#include <Arduino.h>
#include "controller.h"
#define PID_EPS 1e-8

//::::: PARTE 1 controllo PID ::::::
float returnControl(PID_t* pid, float err) {
  float control = 0;
  unsigned long now = micros();
  float dT  = (now - pid->lastT) * 1e-6f;
  if (dT < PID_EPS) dT = PID_EPS;
  // aggiorno gli errori
  pid->le    = pid->e;
  pid->e     = err;
  // proportional control
  control += pid->p*pid->e;
  // derivative control
  float der = (pid->e - pid->le) / dT;
  control += pid->d*der;
  //integral control
  pid->ie += dT * (pid->e + pid->le) * 0.5f;
  pid->ie = constrain(pid->ie, -pid->MAXINT, pid->MAXINT); // anti wind up
  control += pid->i*pid->ie;
  // terminazione funzione
  pid->lastT = now; // aggiorno il tempo
  if (control > pid->MAXOUT)  return pid->MAXOUT;
  if (control < -pid->MAXOUT) return -pid->MAXOUT;
  return control;
}

PID_t beginPID(float P, float I, float D) {
  PID_t pid = {P, I, D, 0, 0, 0, micros(), DEF_MAX_INT, DEF_MAX_OUT};
  pid.state = returnstate(P, I, D);
  return pid;
}
PID_t beginPID(float P, float I, float D, float MAXOUT) {
  PID_t pid = {P, I, D, 0, 0, 0, micros(), DEF_MAX_INT, MAXOUT};
  pid.state = returnstate(P, I, D);
  return pid;
}
PID_t beginPID(float P, float I, float D, float MAXOUT, float MAXINT) {
  PID_t pid = {P, I, D, 0, 0, 0, micros(), MAXINT, MAXOUT};
  pid.state = returnstate(P, I, D);
  return pid;
}

uint8_t returnstate(float P, float I, float D) {
  if (P < 0 || I < 0 || D < 0)                                          return STATE_NEGATIVE;
  if ( fabs(P) < PID_EPS && fabs(I) < PID_EPS && fabs(D) < PID_EPS )    return STATE_ANORMAL;
  if ( fabs(P) < PID_EPS )                                              return STATE_ANORMAL;
  if ( fabs(D) < PID_EPS && fabs(I) < PID_EPS)                          return STATE_P;
  if ( fabs(D) < PID_EPS)                                               return STATE_PI;
  if ( fabs(I) < PID_EPS)                                               return STATE_PD;
  return                                                                       STATE_PID;
}

int controlToDigital(float control, float min, float max) { // converst control from (min, max) to (0, 255)
  float val  = (control - min) * (255 - 0) / (max - min);
  return constrain(round(val), 0, 255);
}

//::::::::::::::::::::::::::::::::::