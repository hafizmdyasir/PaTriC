BUILD_DIR=build
CONFIG_FILE = $(BUILD_DIR)/config.mk

# Reload configuration from build/config.mk if it exists
-include $(CONFIG_FILE)

CXX ?= g++
PREFIX ?= /usr/local
CXXFLAGS ?= -std=c++17 -O3 -Wall -fPIC -I./include

# Add OpenMP support and include path for PATRIC headers
CXXFLAGS += -I$(PREFIX)/include/patric -fopenmp

# Check for USE_SI_UNITS and define it
ifeq ($(SI_UNITS),1)
	CXXFLAGS += -DUSE_SI_UNITS
endif

# Check for precision
ifeq ($(HIGH_PRECISION),1)
	CXXFLAGS += -DHIGH_PRECISION
else ifeq ($(LOW_PRECISION),1)
	CXXFLAGS += -DLOW_PRECISION
endif

# Check for debug mode
ifeq ($(DEBUG),1)
	CXXFLAGS += -g -O0
endif

TARGET = $(BUILD_DIR)/patric
CORE_LIB = $(BUILD_DIR)/libpatriccore.a

CORE_SRCS = src/integrator.cpp src/misc.cpp src/vector3d.cpp src/plotter.cpp src/fields.cpp src/initial_condition.cpp src/validation.cpp
CORE_OBJS = $(addprefix $(BUILD_DIR)/, $(notdir $(CORE_SRCS:.cpp=.o)))
MAIN_SRC = src/main.cpp
MAIN_OBJ = $(BUILD_DIR)/main.o

all: $(TARGET)

# Ensure the build directory exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Automatically generate build_config.h from Makefile variables
include/build_config.h:
	@echo "Generating build configuration..."
	@echo "#pragma once" > $@
	@echo "#define RUNTIME_CXX \"$(CXX)\"" >> $@
	@echo "#define RUNTIME_CXXFLAGS \"$(CXXFLAGS)\"" >> $@
	@echo "#define INSTALL_PREFIX \"$(PREFIX)\"" >> $@

# 2. Ensure build_config.h exists before compiling main.o
$(MAIN_OBJ): $(MAIN_SRC) include/build_config.h | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Build the Core Library archive inside build/
$(CORE_LIB): $(CORE_OBJS) | $(BUILD_DIR)
	ar rcs $@ $^

# Build the Main Application inside build/
$(TARGET): $(MAIN_OBJ) $(CORE_LIB) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(MAIN_OBJ) $(CORE_LIB) -o $@ -ldl

# Pattern rule to compile source files directly into build/
$(BUILD_DIR)/%.o: src/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) include/build_config.h $(CONFIG_FILE)
	@echo "Cleaned build artifacts."

install: all
	@echo "\nInstalling to $(PREFIX)..."
	mkdir -p $(PREFIX)/bin
	mkdir -p $(PREFIX)/include/patric
	mkdir -p $(PREFIX)/lib
	
	cp $(TARGET) $(PREFIX)/bin/
	cp include/*.h $(PREFIX)/include/patric/
	cp include/build_config.h $(PREFIX)/include/patric/
	cp $(CORE_LIB) $(PREFIX)/lib/
	@echo "\nInstallation complete!"

uninstall:
	rm -f $(PREFIX)/bin/patric
	rm -rf $(PREFIX)/include/patric
	rm -f $(PREFIX)/lib/libpatriccore.a
	@echo "Uninstallation complete."

.PHONY: all clean install uninstall