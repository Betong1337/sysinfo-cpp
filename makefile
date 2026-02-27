CXX := g++
CXXFLAGS := -g -std=c++20 -Wall -Wextra -Wpedantic -I./src

TARGET := sysinfo
SRC_DIR := src

UNAME_S := $(shell uname -s)

COMMON_SRCS := \
	$(wildcard $(SRC_DIR)/*.cpp) \
	$(wildcard $(SRC_DIR)/core/*.cpp)

ifeq ($(UNAME_S),Linux)
	PLATFORM_SRCS := $(wildcard $(SRC_DIR)/platform/linux/*.cpp)
endif

ifeq ($(UNAME_S),Darwin)
	PLATFORM_SRCS := $(wildcard $(SRC_DIR)/platform/mac/*.cpp)
endif

ifeq ($(OS),Windows_NT)
	PLATFORM_SRCS := $(wildcard $(SRC_DIR)/platform/windows/*.cpp)
endif

SRCS := $(COMMON_SRCS) $(PLATFORM_SRCS)
OBJS := $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)