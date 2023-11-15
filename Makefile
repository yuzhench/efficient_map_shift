# Makefile for map_shift.cpp

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall

# Source file and executable name
SRC = map_shift.cpp
EXECUTABLE = map_shift

# Build directory
BUILD_DIR = build

# Object files
OBJ = $(BUILD_DIR)/$(SRC:.cpp=.o)

# Target: all (default target)
all: $(EXECUTABLE)

# Target: executable
$(EXECUTABLE): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Target: object files
$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Target: create build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Target: clean
clean:
	rm -rf $(BUILD_DIR) $(EXECUTABLE)

# .PHONY: targets
.PHONY: all clean

