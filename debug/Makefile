
# ===========================
# hyprix assignment
# ===========================
PROJECT_NAME = main

ARDUINO_PORT = /dev/ttyACM0 # HI PLEASE CHANGE THIS TO THE PORT YOUR ARDUINO IS CONNECTED TO
AVRDUDE_BAUDRATE = 115200

# Directories
MAIN_DIR = ../main
DRIVERS_SRC_DIR = ../drivers/src
DRIVERS_INC_DIR = ../drivers/include
BUILD_DIR = bin
HEX_DIR = hex
DRIVER_OBJ_DIR = drivers
MAIN_OBJ_DIR = main

# Source files
MAIN_SRC = $(wildcard $(MAIN_DIR)/*.c)
DRIVERS_SRC = $(wildcard $(DRIVERS_SRC_DIR)/*.c)
SRC = $(MAIN_SRC) $(DRIVERS_SRC)

# Object files (replace .c with .o and put in BUILD_DIR)
OBJ = $(SRC:%.c=$(BUILD_DIR)/%.o)

# Output files
ELF_FILE = $(BUILD_DIR)/$(PROJECT_NAME).elf
HEX_FILE = $(HEX_DIR)/$(PROJECT_NAME).hex

# ===========================
# AVR Toolchain
# ===========================
AVR_GCC = avr-gcc
AVR_OBJCOPY = avr-objcopy
AVRDUDE = avrdude

# Compiler flags
CFLAGS = -Wall -Os -g -mmcu=atmega328p -DF_CPU=16000000UL \
         -I$(MAIN_DIR) -I$(DRIVERS_INC_DIR)

# Linker flags
LDFLAGS = -mmcu=atmega328p

# avrdude flags
AVRDUDE_FLAGS = -p m328p -c arduino -P $(ARDUINO_PORT) -b $(AVRDUDE_BAUDRATE) -D -U flash:w:$(HEX_FILE):i

# ===========================
# Targets
# ===========================

# Default target
all: build

# Build project
build: $(HEX_FILE)
	@echo "####Build complete!####"

# Create HEX file
$(HEX_FILE): $(ELF_FILE)
	@echo "Creating HEX file: $@"
	@mkdir -p $(HEX_DIR)
	$(AVR_OBJCOPY) -O ihex -R .eeprom $< $@

# Link object files into ELF
$(ELF_FILE): $(OBJ)
	@echo " Linking: $@"
	@mkdir -p $(BUILD_DIR)
	$(AVR_GCC) $(LDFLAGS) $^ -o $@ -lm

# Compile .c into .o
$(BUILD_DIR)/%.o: %.c
	@echo " Compiling $< -> $@"
	@mkdir -p $(dir $@)
	$(AVR_GCC) -c $(CFLAGS) $< -o $@

# Upload to Arduino
upload: $(HEX_FILE)
	@if [ -z "$(ARDUINO_PORT)" ]; then \
		echo " No Arduino detected! Please connect your board."; \
	else \
		echo "Uploading $^ to Arduino on $(ARDUINO_PORT)"; \
		$(AVRDUDE) $(AVRDUDE_FLAGS) || echo "⚠ Upload failed. Check board/reset/permissions."; \
	fi

# Clean build files
clean:
	@echo "🧹 Cleaning project"
	rm -rf $(BUILD_DIR) $(HEX_DIR) $(MAIN_OBJ_DIR) $(DRIVER_OBJ_DIR)

.PHONY: all build upload clean
