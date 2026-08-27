CXX := g++
CXXFLAGS := -g -std=c++20 -Wall -Wextra -Wpedantic -I./src -lcurl

TARGET := sysinfo
SRC_DIR := src

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
	PLATFORM_DIR := $(SRC_DIR)/platform/linux
	LDFLAGS :=
endif

ifeq ($(UNAME_S),Darwin)
	PLATFORM_DIR := $(SRC_DIR)/platform/mac
	LDFLAGS :=
endif

ifeq ($(OS),Windows_NT)
	PLATFORM_DIR := $(SRC_DIR)/platform/windows
	LDFLAGS := -lole32 -loleaut32 -lwbemuuid
endif

COMMON_SRCS := $(shell find $(SRC_DIR) -name "*.cpp" ! -path "$(SRC_DIR)/platform/*")
PLATFORM_SRCS := $(shell find $(PLATFORM_DIR) -name "*.cpp")
SRCS := $(COMMON_SRCS) $(PLATFORM_SRCS)

OBJS := $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

PREFIX := /usr/local
BINDIR := $(PREFIX)/bin
DATADIR := $(PREFIX)/share/sysinfo
CONFIG := config
ASCIIARTDIR := $(DATADIR)/asciiart

install: $(TARGET)
	@echo "Installing $(TARGET) to $(BINDIR)"
	install -Dm755 $(TARGET) $(BINDIR)/$(TARGET)
	@echo "Installing config to $(DATADIR)/config"
	install -Dm644 $(CONFIG) $(DATADIR)/config
	@echo "Installing ascii-art to $(ASCIIARTDIR)"
	install -d $(ASCIIARTDIR)
	install -m644 src/asciiart/*.txt $(ASCIIARTDIR)/

WINPREFIX := C:/Program Files/sysinfo
WINBINDIR := $(WINPREFIX)
WINDATADIR := $(WINPREFIX)/asciiart

install_windows: $(TARGET)
	@echo "Installing $(TARGET) to $(WINBINDIR)"
	mkdir -p "$(WINBINDIR)"
	cp $(TARGET) "$(WINBINDIR)/"
	@echo "Installing ascii-art to $(WINDATADIR)"
	mkdir -p "$(WINDATADIR)"
	cp src/asciiart/*.txt "$(WINDATADIR)/"
	@echo "Installation complete. You can now run sysinfo from any terminal."

print:
	@echo "Platform dir: $(PLATFORM_DIR)"
	@echo "Sources:"
	@echo "$(SRCS)"
	@echo "Linker flags: $(LDFLAGS)"