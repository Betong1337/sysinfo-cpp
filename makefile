# Compiler och flags
CXX := g++
CXXFLAGS := -g -std=c++20 -Wall -Wextra -Wpedantic -I./src

# Output-program
TARGET := sysinfo
SRC_DIR := src

# --- Detect platform directory ---
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
	PLATFORM_DIR := $(SRC_DIR)/platform/linux
endif

ifeq ($(UNAME_S),Darwin)
	PLATFORM_DIR := $(SRC_DIR)/platform/mac
endif

ifeq ($(OS),Windows_NT)
	PLATFORM_DIR := $(SRC_DIR)/platform/windows
endif

# --- Collect source files ---
COMMON_SRCS := $(shell find $(SRC_DIR) -name "*.cpp" ! -path "$(SRC_DIR)/platform/*")
PLATFORM_SRCS := $(shell find $(PLATFORM_DIR) -name "*.cpp")

SRCS := $(COMMON_SRCS) $(PLATFORM_SRCS)

# --- Object files ---
OBJS := $(SRCS:.cpp=.o)

# --- Build rules ---
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

# --- Install ---
PREFIX := /usr/local
BINDIR := $(PREFIX)/bin
DATADIR := $(PREFIX)/share/sysinfo/asciiart

install: $(TARGET)
	@echo "Installing $(TARGET) to $(BINDIR)"
	install -Dm755 $(TARGET) $(BINDIR)/$(TARGET)
	@echo "Installing ascii-art to $(DATADIR)"
	install -d $(DATADIR)
	install -m644 src/asciiart/*.txt $(DATADIR)/

# --- Debug helper ---
print:
	@echo "Platform dir: $(PLATFORM_DIR)"
	@echo "Sources:"
	@echo "$(SRCS)"