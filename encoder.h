#ifndef ENCODER_H
#define ENCODER_H
#define PPR 600
#define DTHETA ( 2*PI / PPR )

extern volatile long count;   // conteggio encoder
extern float theta;           // angolo effettivo theta
extern uint8_t pinA, pinB;    // pin A, pin B

void begin_encoder(uint8_t pinA_, uint8_t pinB_);
void ISR_A();
float update_theta();

#endif