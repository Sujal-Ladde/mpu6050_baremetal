#!/bin/bash

# ==============================
# AVR Toolchain Installer Script
# ==============================

echo "=============================="
echo " AVR Toolchain Installation"
echo "=============================="

# Update package list
sudo apt update

# Install AVR GCC, avrdude, and dependencies
sudo apt install -y gcc-avr binutils-avr avr-libc avrdude make

# Check if installation was successful
if ! command -v avr-gcc &> /dev/null || ! command -v avrdude &> /dev/null; then
    echo "AVR tools installation failed!"
    exit 1
fi

echo "AVR tools installed successfully."

# Find avr-gcc binary path
AVR_PATH=$(dirname "$(command -v avr-gcc)")

# Add to PATH if not already there
if [[ ":$PATH:" != *":$AVR_PATH:"* ]]; then
    echo "Adding $AVR_PATH to PATH..."
    echo "export PATH=\$PATH:$AVR_PATH" >> ~/.bashrc
    source ~/.bashrc
else
    echo "AVR toolchain path already in PATH"
fi

# Verify versions
echo
echo "avr-gcc version:"
avr-gcc --version

echo
echo "avrdude version:"
avrdude -v | head -n 3

echo
echo "Installation complete. You may need to open a new terminal for PATH changes to apply."
