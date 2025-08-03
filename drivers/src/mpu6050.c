#include "mpu6050.h"
#include "i2c.h"
#include "serial.h"

void MPU6050_init(void) {
  if (I2C_write_register(MPU6050_ADDR, 0x6B, 0x00) != I2C_OK)
    Serial_writeString("MPU6050 Init Error (PWR_MGMT_1)\r\n");

  I2C_write_register(MPU6050_ADDR, 0x1B, 0x00); // GYRO_CONFIG ±250 dps
  I2C_write_register(MPU6050_ADDR, 0x1C, 0x00); // ACCEL_CONFIG ±2g
  I2C_write_register(MPU6050_ADDR, 0x19, 0x07); // SMPLRT_DIV
  I2C_write_register(MPU6050_ADDR, 0x1A, 0x06); // CONFIG (DLPF)
}

uint8_t MPU6050_read_accel(int16_t *ax, int16_t *ay, int16_t *az) {
  uint8_t buffer[6];
  if (I2C_read_registers(MPU6050_ADDR, 0x3B, buffer, 6) != I2C_OK) {
    Serial_writeString("MPU6050 Accel Read Timeout\r\n");
    return I2C_TIMEOUT_ERR;
  }

  *ax = (int16_t)((buffer[0] << 8) | buffer[1]);
  *ay = (int16_t)((buffer[2] << 8) | buffer[3]);
  *az = (int16_t)((buffer[4] << 8) | buffer[5]);
  return I2C_OK;
}

uint8_t MPU6050_read_gyro(int16_t *gx, int16_t *gy, int16_t *gz) {
  uint8_t buffer[6];
  if (I2C_read_registers(MPU6050_ADDR, 0x43, buffer, 6) != I2C_OK) {
    Serial_writeString("MPU6050 Gyro Read Timeout\r\n");
    return I2C_TIMEOUT_ERR;
  }

  *gx = (int16_t)((buffer[0] << 8) | buffer[1]);
  *gy = (int16_t)((buffer[2] << 8) | buffer[3]);
  *gz = (int16_t)((buffer[4] << 8) | buffer[5]);
  return I2C_OK;
}
