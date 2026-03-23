#include <Arduino.h>
#include "motordriver.h"

Motor_t beginMotor(uint8_t en, uint8_t in1, uint8_t in2) {
  Motor_t motor = {en, in1, in2};
  pinMode(en,  OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  return motor;
}

void writeSpeed(Motor_t* motor, uint8_t speed, MotorDir_t direction) {
  if (speed == 0) {
    // motore spento
    digitalWrite(motor->in1, LOW);
    digitalWrite(motor->in2, LOW);
    analogWrite(motor->en, 0);
    return;
  }
  if (direction == MOTOR_FORWARD) {
    digitalWrite(motor->in1, HIGH);
    digitalWrite(motor->in2, LOW );
  }else if (direction == MOTOR_BACKWARD) {
    digitalWrite(motor->in1, LOW );
    digitalWrite(motor->in2, HIGH);
  } else {
    digitalWrite(motor->in1, LOW);
    digitalWrite(motor->in2, LOW);
    speed = 0;
  }

  analogWrite(motor->en, speed);
}




