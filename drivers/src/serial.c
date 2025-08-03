#include "serial.h"

// AVR UART register definitions 
#define UDR0 (*(volatile unsigned char *)0xC6)
#define UCSR0A (*(volatile unsigned char *)0xC0)
#define UCSR0B (*(volatile unsigned char *)0xC1)
#define UCSR0C (*(volatile unsigned char *)0xC2)
#define UBRR0H (*(volatile unsigned char *)0xC5)
#define UBRR0L (*(volatile unsigned char *)0xC4)

#define RXEN0 4
#define TXEN0 3
#define UCSZ00 1
#define UCSZ01 2
#define UDRE0 5

// Initialize UART
void Serial_init(unsigned long baud) {
  unsigned int ubrr = (16000000UL / (16UL * baud)) - 1;
  UBRR0H = (ubrr >> 8) & 0xFF;
  UBRR0L = ubrr & 0xFF;

  UCSR0B = (1 << TXEN0);                  // Enable transmitter only
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 8-bit data, 1 stop, no parity
}

// Send a single character
void Serial_writeChar(char c) {
  while (!(UCSR0A & (1 << UDRE0)))
    ; // Wait for buffer empty
  UDR0 = c;
}

// Send a string
void Serial_writeString(const char *str) {
  while (*str) {
    Serial_writeChar(*str++);
  }
}

// Send integer (simple decimal)
void Serial_writeInt(int value) {
  char buffer[7];
  int i = 0;

  if (value < 0) {
    Serial_writeChar('-');
    value = -value;
  }

  if (value == 0) {
    Serial_writeChar('0');
    return;
  }

  while (value > 0 && i < 6) {
    buffer[i++] = (value % 10) + '0';
    value /= 10;
  }
  while (i > 0) {
    Serial_writeChar(buffer[--i]);
  }
}

// Send newline
void Serial_newline(void) {
  Serial_writeChar('\r');
  Serial_writeChar('\n');
}
