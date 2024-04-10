LDLIBS=-lpcap
CC=g++
CFLAGS=-g -Wall
SRC_DIR=src
BIN_DIR=bin

# Define source and header files
SOURCES=$(wildcard $(SRC_DIR)/*.cpp)
HEADERS=$(wildcard $(SRC_DIR)/*.h)

# Generate object file names by replacing src directory and .cpp extension with bin directory and .o extension
OBJS=$(patsubst $(SRC_DIR)/%.cpp,$(BIN_DIR)/%.o,$(SOURCES))

# Default target
all: $(BIN_DIR)/send-arp

# Pattern rule for compiling .cpp to .o
$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files to create the final executable
$(BIN_DIR)/send-arp: $(OBJS)
	$(CC) $(CFLAGS) $^ $(LDLIBS) -o $@

# Create bin directory if it does not exist
$(OBJS): | $(BIN_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Clean rule to remove binaries and object files
clean:
	rm -rf $(BIN_DIR)
