#include "i2c.h"
#include "serial.h"

static uint8_t I2C_wait_for_flag(void) {
  uint32_t counter = 0;
  while (!(TWCR & (1 << TWINT))) {
    if (counter++ > I2C_TIMEOUT) {
      Serial_writeString("I2C Timeout Error\r\n");
      return I2C_TIMEOUT_ERR;
    }
  }
  return I2C_OK;
}

void I2C_init(uint32_t scl_freq) {
  TWSR = 0x00; // Prescaler = 1
  TWBR = ((F_CPU / scl_freq) - 16) / 2;
  TWCR = (1 << TWEN); // Enable TWI
}

uint8_t I2C_start(uint8_t address) {
  TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
  if (I2C_wait_for_flag() != I2C_OK)
    return I2C_TIMEOUT_ERR;

  TWDR = address;
  TWCR = (1 << TWINT) | (1 << TWEN);
  if (I2C_wait_for_flag() != I2C_OK)
    return I2C_TIMEOUT_ERR;

  return I2C_OK;
}

void I2C_stop(void) {
  TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
  uint32_t counter = 0;
  while (TWCR & (1 << TWSTO)) {
    if (counter++ > I2C_TIMEOUT) {
      Serial_writeString("I2C STOP Timeout\r\n");
      break;
    }
  }
}

uint8_t I2C_write(uint8_t data) {
  TWDR = data;
  TWCR = (1 << TWINT) | (1 << TWEN);
  if (I2C_wait_for_flag() != I2C_OK)
    return I2C_TIMEOUT_ERR;
  return I2C_OK;
}

uint8_t I2C_read_ack(uint8_t *data) {
  TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
  if (I2C_wait_for_flag() != I2C_OK)
    return I2C_TIMEOUT_ERR;
  *data = TWDR;
  return I2C_OK;
}

uint8_t I2C_read_nack(uint8_t *data) {
  TWCR = (1 << TWINT) | (1 << TWEN);
  if (I2C_wait_for_flag() != I2C_OK)
    return I2C_TIMEOUT_ERR;
  *data = TWDR;
  return I2C_OK;
}

uint8_t I2C_write_register(uint8_t dev_addr, uint8_t reg, uint8_t data) {
  if (I2C_start((dev_addr << 1) | 0) != I2C_OK)
    return I2C_TIMEOUT_ERR;
  if (I2C_write(reg) != I2C_OK)
    return I2C_TIMEOUT_ERR;
  if (I2C_write(data) != I2C_OK)
    return I2C_TIMEOUT_ERR;
  I2C_stop();
  return I2C_OK;
}

uint8_t I2C_read_registers(uint8_t dev_addr, uint8_t reg, uint8_t *data,
                           uint8_t length) {
  if (I2C_start((dev_addr << 1) | 0) != I2C_OK)
    return I2C_TIMEOUT_ERR;
  if (I2C_write(reg) != I2C_OK)
    return I2C_TIMEOUT_ERR;

  if (I2C_start((dev_addr << 1) | 1) != I2C_OK)
    return I2C_TIMEOUT_ERR;

  for (uint8_t i = 0; i < length; i++) {
    if (i == (length - 1)) {
      if (I2C_read_nack(&data[i]) != I2C_OK)
        return I2C_TIMEOUT_ERR;
    } else {
      if (I2C_read_ack(&data[i]) != I2C_OK)
        return I2C_TIMEOUT_ERR;
    }
  }
  I2C_stop();
  return I2C_OK;
}
