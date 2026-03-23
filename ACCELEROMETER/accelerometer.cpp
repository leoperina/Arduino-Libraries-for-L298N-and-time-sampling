#include "accelerometer.h"


void readrotstatealong(float* p, float* v, float*a, uint8_t axis, MPU6050 mpu) { 
  // p, v, a are the pointers where the value is saved, axis is 1:3 depending on what is asked: [rotx, roty, rotz]
  // note that p, v, a are respectively angle, angular velocity and angular acceleration
  switch(axis) {
    case 1: (*p) = mpu.getAngleX(); (*v) = mpu.getGyroAngleX(); (*a) = mpu.getGyroX(); break;
    case 2: (*p) = mpu.getAngleY(); (*v) = mpu.getGyroAngleY(); (*a) = mpu.getGyroY(); break;
    case 3: (*p) = mpu.getAngleZ(); (*v) = mpu.getGyroAngleZ(); (*a) = mpu.getGyroZ(); break;
    default: return;
  }
}



