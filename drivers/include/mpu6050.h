#ifndef MPU6050_H
#define MPU6050_H

#include <stdint.h>

#define MPU6050_ADDR 0x68

void MPU6050_init(void);
uint8_t MPU6050_read_accel(int16_t *ax, int16_t *ay, int16_t *az);
uint8_t MPU6050_read_gyro(int16_t *gx, int16_t *gy, int16_t *gz);

#endif
