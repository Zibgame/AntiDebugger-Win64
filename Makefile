NAME = antidebug
BUILD_DIR = build
SRC_DIR = src
INC_DIR = include
EXAMPLES_DIR = src/examples

CXX = g++
CXXFLAGS = -Wall -Wextra -O2 -I$(INC_DIR)

SRC = $(wildcard $(SRC_DIR)/*.cpp)
EXAMPLES = $(wildcard $(EXAMPLES_DIR)/*.cpp)

LIB = $(BUILD_DIR)/lib$(NAME).a
EXAMPLES_BIN = $(patsubst $(EXAMPLES_DIR)/%.cpp,$(BUILD_DIR)/%.exe,$(EXAMPLES))

all: $(BUILD_DIR) $(LIB) examples

$(BUILD_DIR):
	mkdir $(BUILD_DIR) 2>nul || exit 0

# build lib
$(LIB):
	$(CXX) $(CXXFLAGS) -c $(SRC)
	ar rcs $(LIB) $(notdir $(SRC:.cpp=.o))
	del /Q *.o 2>nul

# build examples
examples: $(EXAMPLES_BIN)

$(BUILD_DIR)/%.exe: $(EXAMPLES_DIR)/%.cpp $(LIB)
	$(CXX) $(CXXFLAGS) $< -L$(BUILD_DIR) -l$(NAME) -o $@

clean:
	@if exist $(BUILD_DIR) rmdir /S /Q $(BUILD_DIR)
	@del /Q *.o 2>nul

re: clean all