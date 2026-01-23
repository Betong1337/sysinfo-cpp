# Makefile för sysinfo-projektet

# Compiler och flags
CXX := g++
CXXFLAGS := -g -std=c++20 -Wall -Wextra -Wpedantic -I./src

# Output-program
TARGET := sysinfo

# Sökvägar
SRC_DIR := src

# Alla cpp-filer i src och underkataloger
SRCS := $(wildcard $(SRC_DIR)/*.cpp) \
        $(wildcard $(SRC_DIR)/cpu/*.cpp) \
        $(wildcard $(SRC_DIR)/gpu/*.cpp) \
        $(wildcard $(SRC_DIR)/os/*.cpp) \
        $(wildcard $(SRC_DIR)/core/*.cpp) \
		$(wildcard $(SRC_DIR)/ram/*.cpp) \
		$(wildcard $(SRC_DIR)/hostname/*.cpp) \
		$(wildcard $(SRC_DIR)/uptime/*.cpp)

# Objektfiler
OBJS := $(SRCS:.cpp=.o)

# Standardmål
all: $(TARGET)

# Länka ihop objektfilerna till programmet
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Kompilera cpp till objektfiler
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rensa upp objektfiler och program
clean:
	rm -f $(OBJS) $(TARGET)

# Kör programmet direkt
run: $(TARGET)
	./$(TARGET)
