# Project Title

## Table of Contents

- [About](#about)
- [Installation](#installations)
- [Usage](#usage)

## About <a name = "about"></a>

This project is a bare-metal MPU6050 driver implementation for the Arduino Uno (ATmega328P), developed without using any built-in Arduino libraries such as Wire.h. It features a custom I²C (TWI) driver for low-level communication with the MPU6050 sensor, enabling direct register-level control of the accelerometer and gyroscope. The driver is designed with a robust timeout mechanism that prevents the microcontroller from hanging if the sensor becomes unresponsive or if there are I²C bus errors, and it provides clear error messages over UART for debugging. The project is modular, with separate source and header files for I²C, MPU6050, UART (serial), and delay handling, and it includes a Makefile for efficient building and uploading. By working at the register level and using a clean, organized directory structure, this project serves as a strong example of bare-metal programming, hardware abstraction, and structured embedded systems development.

link to video explaination : https://drive.google.com/drive/folders/1vTVz_2X0--4YY_oLV6PIBIgr4yCNfo3T?usp=sharing


## Installation <a name = "installations"></a>

How to Build and Upload

1. Run install.sh to install all required dependencies (e.g., avr-gcc and avrdude).

2. Check the port to which your Arduino is connected.

3. Navigate to the debug folder and open the Makefile. Update the ARDUINO_PORT variable with the correct port.

```
./install.sh

```

## Usage <a name = "usage"></a>

Navigate to the debug folder and build the project by running:

```
 make build 

```

Upload the compiled firmware to the Arduino:

```
 make upload 

```
Clean:

```
 make clean 
 
```
Open the serial monitor to view the output messages.


