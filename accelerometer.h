#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

#include <Wire.h>
#include <MPU6050_tockn.h>

void readrotstatealong(float* p, float* v, float*a, uint8_t axis, MPU6050 mpu);

#endif