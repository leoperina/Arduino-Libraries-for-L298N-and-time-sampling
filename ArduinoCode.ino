#include "encoder.h"
#include "timemanager.h"
#include "controller.h"
#include "motordriver.h"
#include "accelerometer.h"


enum DATATYPE : uint8_t {
  TYPE_INT,
  TYPE_UINT,
  TYPE_FLOAT,
  TYPE_DOUBL,
  TYPE_UINT8,
  TYPE_ULONG,
  TYPE_BOOL
};

//_______________________________accelerometer
// MPU6050 mpu(Wire);

//_______________________________debug sampler
unsigned long last_sample, this_sample;
float dT;


// ______________________________encoder
// constexpr uint8_t ENC_A = 2;
// constexpr uint8_t ENC_B = 3;
// float theta_enc;

// ______________________________controllore
// #define CONTROLPIN 11
// PID_t controller;
// float theta_err, theta_dot_err, theta_ddot_err;
// float control;
// uint8_t control_digital;

// ______________________________motore
#define IN1 8
#define IN2 7
#define EN  6
Motor_t motor;

void setup() {
  Serial.begin(115200);
  Serial.println("Setup is beginning.");
  pinMode(LED_BUILTIN, OUTPUT);

  // _______________________________________inizializzazione accelerometro
  // Wire.begin();
  // mpu.begin();
  // mpu.calcGyroOffsets(true);
  // ... e la parte di controlli
  // theta_err      = 0;
  // theta_dot_err  = 0;
  // theta_ddot_err = 0;


  // _______________________________________inizializzazione encoder
  // begin_encoder(ENC_A, ENC_B);
  // theta_enc = 0;

  // _______________________________________inizializzazione controllore
  // controller = beginPID(2, 1, 0.01, 5); // P, I, D, maxcontrol
  // pinMode(CONTROLPIN, OUTPUT);

  // _______________________________________inizializzazione motore
  motor = beginMotor(EN, IN1, IN2);

  // _______________________________________inizializzazione sampler
  this_sample = millis();
  last_sample = this_sample;

  beginSampler(10); // Hz
  Serial.println("Sampler initialization status: ");
  float samplfreq = returnSamplingFrequency();
  switch(returnFlag()) {
    case NOMINAL:        Serial.println("Nominal"); break;
    case FREQTOOHIGH:    Serial.print  ("Warning - requested frequency too high, new freq is"); Serial.print(samplfreq); Serial.println(" Hz"); break;
    case NEGATIVEFREQ:   Serial.print  ("Warning - requested frequency is negative, new freq is"); Serial.print(samplfreq); Serial.println(" Hz"); break;
    case BYPASS:         Serial.print  ("Nominal - Bypass request is detected, sample() will be bypassed"); break;
    default: 
      Serial.println("Error - returnFlag() returned unexpected value, aborting the program");  
      while(1) {blink();}; 
    break;
  }
  Serial.println("Setup complete...");
  delay(1000);
}


void loop() {
  // lettura encoder (con interrupts, lettura encoder ecc)
  // theta_enc = update_theta();
  // theta_enc *= 180 / PI;
  // Sampler
  if( sample() ) {
    // qui tutto il codice che voglio eseguire quando lo slot di sampling è attivo

    // ::::: READ ACCELEROMETER :::::
    // mpu.update();
    // readrotstatealong(&theta_err, &theta_dot_err, &theta_ddot_err, 3, mpu);

    // printForCSV("theta_enc", &theta_enc, TYPE_FLOAT);
    // this_sample = micros();
    // printToPlotter("theta_enc", &theta_enc, TYPE_FLOAT);
    // printToPlotter("now", &this_sample, TYPE_ULONG);
    // printToPlotter("last", &last_sample, TYPE_ULONG);


    // ::::::: SAMPLER :::::::
    
    dT =  1000000.0f / ( this_sample - last_sample );
    last_sample = this_sample;
    // Serial.println(dT);
    // printToPlotter("Sample frequency|", &dT, TYPE_FLOAT);
    // printForCSV("sampl_freq", &dT, TYPE_FLOAT);

    
    writeSpeed(&motor, 255, MOTOR_FORWARD);
    printToPlotter("Motor Requested output", 255, TYPE_INT);

    // uint8_t ref_speed = 200 * sin(millis() / 1000.0f); // do come reference una generica onda sinusoidale
    // printToPlotter("ref_speed", &ref_speed, TYPE_FLOAT);
    // writeSpeed(&motor, ref_speed, MOTOR_FORWARD);

    // Serial.print("flag:");
    // Serial.println(returnFlag());
    // writeSpeed(&motor, 1, (ref_speed > 0) ? MOTOR_FORWARD : MOTOR_BACKWARD); // il segno FUNZIONA!!!!!!!!
    
  }
}

void blink() {
  // ciclo 1
  digitalWrite(LED_BUILTIN, HIGH);
  delay(200);
  digitalWrite(LED_BUILTIN, LOW);
  delay(100);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(200);
  digitalWrite(LED_BUILTIN, LOW);

  delay(500);

  digitalWrite(LED_BUILTIN, HIGH);
  delay(200);
  digitalWrite(LED_BUILTIN, LOW);
  delay(100);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(200);
  digitalWrite(LED_BUILTIN, LOW);

  delay(500);
}


void printForCSV(const char* name, void* x, uint8_t TYPE) {
  Serial.print(name);
  Serial.print(",");
  switch(TYPE) {
    case TYPE_INT  : Serial.println( *(int*)           x ); break;
    case TYPE_UINT : Serial.println( *(unsigned int*)  x ); break;
    case TYPE_FLOAT: Serial.println( *(float*)         x ); break;
    case TYPE_DOUBL: Serial.println( *(double*)        x ); break;
    case TYPE_UINT8: Serial.println( *(uint8_t*)       x ); break;
    case TYPE_ULONG: Serial.println( *(unsigned long*) x ); break;
    case TYPE_BOOL : Serial.println( *(bool*)          x ); break;
    default:         Serial.println( *(double*)        x ); break;
  }
}

void printToPlotter(const char* varname, void* x, uint8_t TYPE) {
  // plots in the Arduino standard so that it can be plotted in the plotter

  Serial.print(varname);
  Serial.print(":");
  switch(TYPE) {
    case TYPE_INT  : Serial.println( *(int*)           x ); break;
    case TYPE_UINT : Serial.println( *(unsigned int*)  x ); break;
    case TYPE_FLOAT: Serial.println( *(float*)         x ); break;
    case TYPE_DOUBL: Serial.println( *(double*)        x ); break;
    case TYPE_UINT8: Serial.println( *(uint8_t*)       x ); break;
    case TYPE_ULONG: Serial.println( *(unsigned long*) x ); break;
    case TYPE_BOOL : Serial.println( *(bool*)          x ); break;
    default:         Serial.println( *(double*)        x ); break;
  }
  // Serial.println(*x);
}




/*
// calcolo dell'errore e del voltaggio di controllo
    theta_err = returntheta_ref() - theta_enc;
    control   = returnControl(&controller, theta_err);
    Serial.print("control:");
    Serial.println(control);
*/






/*
void loop() {
  writeSpeed(&motor, 255, MOTOR_FORWARD);
  Serial.print("throttle:");
  Serial.println(255);
  delay(500);
  writeSpeed(&motor, 20, MOTOR_FORWARD);
  Serial.print("throttle:");
  Serial.println(20);
  delay(1000);
}
*/






// //===== variables for the encoder
// #define pinA 4
// #define pinB 7
// #define dtheta 2*PI / 600 // depending on the fact that the encoder is 600 PPR (rad)
// // As and Bs state the last and current state of A. As[0] & Bs[0] get overwritten with As[1] & Bs[1] at the end of each loop. pin = HIGH (true), pin = LOW (false)
// bool As[2];
// bool Bs[2];
// // enc_state states the current encoder state, which can be standby (0), waiting to increase (1) or waiting to decrease (2)
// enum ENC {
//   STDBY = 0,
//   WAIT_PLUS = 1,
//   WAIT_MINS = 2
// };
// uint8_t enc_state;
// double theta;


// // sampling time 
// int freq = 50;
// float targetT = 1000.0f/freq; // ms
// unsigned long beginT   = 0;   // at the end of each loop Arduino waits the difference to complete a loop in 'targetT'
// unsigned long dT       = 0;


// // functions
// double checkEncoder(bool* As, bool* Bs, uint8_t enc_state);


// void setup() {
//   Serial.begin(9600);

//   //pin initialization
//   pinMode(pinA, INPUT);
//   pinMode(pinB, INPUT);

//   // state initialization
//   for(int i = 0; i < 2; i++){
//     As[i] = false;
//     Bs[i] = false;
//   }
//   enc_state = 0;
//   theta = 0;
// }


// void loop() {
//   // time stuff
//   beginT = millis();
//   // write over the 'last As, Bs' spots
//   As[0] = As[1];
//   Bs[0] = Bs[1];

//   // checking the Encoder

//   // again, time stuff to match the wanted frequency
//   dT = millis() - beginT;
//   if (dT - targetT > 0) {
//     delay( targetT - (millis() - beginT) ); // waiting the right amount of time, if there is to spare
//   }
// }


// double checkEncoder(bool* As, bool* Bs, uint8_t* enc_state) {
//   bool A  = digitalRead(pinA);
//   bool B  = digitalRead(pinB);
//   bool lA = As[0];
//   bool lB = Bs[0];

//   if ( *enc_state == STDBY ) {
//     if ( !A && !B  ) return 0; // still standby, nothing read
//     if ( A  && !lA ) { (*enc_state) = WAIT_PLUS; return 0; } // just read something, but I'm still waiting for the other signal, I know that when it comes I have to add
//     if ( B  && !lB ) { (*enc_state) = WAIT_MINS; return 0; }
//   }
//   else if ( *enc_state == WAIT_PLUS ) { // in this condition I know I already read A == HIGH, I am waiting for B
//     if ( B  ) { (*enc_state) = STDBY; return dtheta; }
//     if ( !A ) { (*enc_state) = STDBY; return 0; } // something went wrong and A became 0 before B was read
//   }
//   else if ( *enc_state == WAIT_MINS ) { // in this condition I know I already read A == HIGH, I am waiting for B
//     if ( A  ) { (*enc_state) = STDBY; return -dtheta; }
//     if ( !B ) { (*enc_state) = STDBY; return 0; } // something went wrong and A became 0 before B was read
//   }
//   As[1] = A;
//   Bs[1] = B;
// }




