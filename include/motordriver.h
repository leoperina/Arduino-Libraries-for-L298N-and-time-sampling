#ifndef MOTORDRIVER_H
#define MOTORDRIVER_H

// questa libreria è fatta AD HOC PER L298N!!!! NON per altre schede motore

typedef enum : uint8_t {
  MOTOR_FORWARD,
  MOTOR_BACKWARD
}MotorDir_t;

typedef struct Motor {
  uint8_t en;
  uint8_t in1, in2;
}Motor_t;

Motor_t beginMotor(uint8_t en, uint8_t in1, uint8_t in2);
void writeSpeed(Motor_t* motor, uint8_t speed, MotorDir_t direction);

#endif
