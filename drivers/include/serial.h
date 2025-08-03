#ifndef SERIAL_H
#define SERIAL_H

#include <stdint.h>

// Initialize UART with given baud rate
void Serial_init(unsigned long baud);

// Transmit a single character
void Serial_writeChar(char c);

// Transmit a string
void Serial_writeString(const char *str);

// Transmit an integer
void Serial_writeInt(int value);

// Transmit a newline
void Serial_newline(void);

#endif
