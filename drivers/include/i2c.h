#ifndef I2C_H
#define I2C_H

#include <stdint.h>

// ==========================
// I2C Configuration
// ==========================
#define F_CPU 16000000UL  // 16 MHz CPU clock
#define I2C_FREQ 100000UL // 100 kHz I2C speed

// ==========================
// Timeout config
// ==========================
#define I2C_TIMEOUT 50000 
#define I2C_OK 0
#define I2C_TIMEOUT_ERR 1

// ==========================
// TWI Register Definitions
// ==========================
#define TWBR (*(volatile uint8_t *)0xB8)  // TWI Bit Rate Register
#define TWSR (*(volatile uint8_t *)0xB9)  // TWI Status Register
#define TWAR (*(volatile uint8_t *)0xBA)  // TWI (Slave) Address Register
#define TWDR (*(volatile uint8_t *)0xBB)  // TWI Data Register
#define TWCR (*(volatile uint8_t *)0xBC)  // TWI Control Register
#define TWAMR (*(volatile uint8_t *)0xBD) // TWI Address Mask Register

// TWCR bits
#define TWINT 7
#define TWEA 6
#define TWSTA 5
#define TWSTO 4
#define TWEN 2

// ==========================
// Function Prototypes
// ==========================

void I2C_init(uint32_t scl_freq);
uint8_t I2C_start(uint8_t address);
void I2C_stop(void);
uint8_t I2C_write(uint8_t data);
uint8_t I2C_read_ack(uint8_t *data);
uint8_t I2C_read_nack(uint8_t *data);

uint8_t I2C_write_register(uint8_t dev_addr, uint8_t reg, uint8_t data);
uint8_t I2C_read_registers(uint8_t dev_addr, uint8_t reg, uint8_t *data,
                           uint8_t length);

#endif


