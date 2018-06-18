# compiler options
LD=g++
CC=g++
CXXFLAGS=-Wall -Werror -std=c++14
LDFLAGS=-Wall -Werror -std=c++14

# directories
OBJ_DIR=./obj
BIN_DIR=./bin
INC_DIR=
LIB_DIR=
LIBRARIES=

all: link
	@echo "\e[92mMaking done!\e[39m"

link: compile
	@echo "\e[92mStart linking...\e[39m"
	mkdir -p $(BIN_DIR)
	$(LD) $(LDFLAGS) $(LIB_DIR) -o $(BIN_DIR)/main \
	$(OBJ_DIR)/main.o \
	$(OBJ_DIR)/sec.o \
	$(LIBRARIES)

compile: clean
	@echo "\e[92mStart compiling...\e[39m"
	mkdir -p $(OBJ_DIR)
	$(CC) $(CXXFLAGS) $(INC_DIR) -c main.cpp -o $(OBJ_DIR)/main.o
	$(CC) $(CXXFLAGS) $(INC_DIR) -c sec.cpp  -o $(OBJ_DIR)/sec.o

clean:
	@echo "\e[92mClean up...\e[39m"
	rm -rf $(BIN_DIR)
	rm -rf $(OBJ_DIR)
