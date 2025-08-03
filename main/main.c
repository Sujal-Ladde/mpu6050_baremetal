#include "i2c.h"
#include "mpu6050.h"
#include "serial.h"

int main(void) {
  Serial_init(9600); // Initialize UART
  I2C_init(100000);  // Initialize I2C at 100kHz
  MPU6050_init();    // Initialize MPU6050

  int16_t ax = 0, ay = 0, az = 0, gx = 0, gy = 0, gz = 0;

  while (1) {
    MPU6050_read_accel(&ax, &ay, &az);
    MPU6050_read_gyro(&gx, &gy, &gz);

    Serial_writeString("Accel: ");
    Serial_writeInt(ax);
    Serial_writeString(", ");
    Serial_writeInt(ay);
    Serial_writeString(", ");
    Serial_writeInt(az);
    Serial_newline();

    Serial_writeString("Gyro: ");
    Serial_writeInt(gx);
    Serial_writeString(", ");
    Serial_writeInt(gy);
    Serial_writeString(", ");
    Serial_writeInt(gz);
    Serial_newline();
    Serial_newline();
    Serial_newline();

    for (volatile long int i = 500000; i--;)
      ;
  }
}
