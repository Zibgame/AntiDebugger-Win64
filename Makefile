NAME = antidebug

BUILD_DIR = build
SRC_DIR = src
INC_DIR = include
EXAMPLES_DIR = src/examples

CXX = g++
CXXFLAGS = -Wall -Wextra -O2 -I$(INC_DIR)

SRC = $(shell dir /B /S $(SRC_DIR)\*.cpp | findstr /V "\\examples\\")
OBJ = $(SRC:.cpp=.o)

LIB = $(BUILD_DIR)/lib$(NAME).a

EXAMPLES = $(wildcard $(EXAMPLES_DIR)/*.cpp)
EXAMPLES_BIN = $(patsubst $(EXAMPLES_DIR)/%.cpp,$(BUILD_DIR)/%.exe,$(EXAMPLES))

clean_obj:
	@del /Q /S *.o 2>nul

all: $(BUILD_DIR) $(LIB) clean_obj examples

$(BUILD_DIR):
	mkdir $(BUILD_DIR) 2>nul || exit 0

# compile
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# lib
$(LIB): $(OBJ)
	ar rcs $@ $^
	ranlib $@

# examples
examples: $(EXAMPLES_BIN)

$(BUILD_DIR)/%.exe: $(EXAMPLES_DIR)/%.cpp $(LIB)
	$(CXX) $(CXXFLAGS) $< -L$(BUILD_DIR) -l$(NAME) -o $@

clean:
	@del /Q /S *.o 2>nul
	@if exist $(BUILD_DIR) rmdir /S /Q $(BUILD_DIR)

re: clean all