#ifndef CONTROLLER_H
#define CONTROLLER_H

//::::: PARTE 1 controllo PID :::::
#define DEF_MAX_INT 1  // valore ad cazzum, questo si riferisce al termine integrativo (pid.ie) NON termine di controllo (pid.ie * pid.i)
#define DEF_MAX_OUT 5  // default massimo out, si riferisce al termine di controllo (pid.p*err + pid.d*z*err + pid.i/z * err)
typedef struct PID {
  float p;   // proportional coeff
  float i;   // integral     coeff
  float d;   // derivative   coeff
  float e;   // error at this time
  float le;  // error at last time
  float ie;  // integral control
  unsigned long lastT; // last time evaluation
  float MAXINT; // saturatore dell'integrale per evitare problemi
  float MAXOUT; // saturatore dell'output, se il controllo è oltre un certo valore viene bloccato
  uint8_t state;
}PID_t;

// inizializzazione
PID_t beginPID(float P, float I, float D);
PID_t beginPID(float P, float I, float D, float MAXOUT);
PID_t beginPID(float P, float I, float D, float MAXOUT, float MAXINT);


uint8_t returnstate(float P, float I, float D);
enum PIDState : uint8_t {
  STATE_P        ,
  STATE_PD       ,
  STATE_PI       ,
  STATE_PID      ,
  STATE_ANORMAL  , // con anormal si intendono i seguenti casi: P = 0, I non è il più piccolo, D > P
  STATE_NEGATIVE
};

// controllo
float returnControl(PID_t* pid, float err);

// conversione PID ad Arduino
int controlToDigital(float control, float min, float max); // converte control nell'intervalo [min, max] a 0, 255

//:::::::::::::::::::::::::::::::::
#endif
