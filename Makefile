# compiler options
LD=g++
CC=g++
CXXFLAGS=-Wall -std=c++14
LDFLAGS=-Wall -std=c++14

# directories
OBJ_DIR=./obj
BIN_DIR=./bin
INC_DIR=-I /usr/include
LIB_DIR=
LIBRARIES=-lglfw -lGLESv2
DEFINES=-DGLFW_INCLUDE_ES2

# all target
all: link
	@echo "\e[92mMaking done!\e[39m"

# link target
link: compile
	@echo "\e[92mStart linking...\e[39m"
	mkdir -p $(BIN_DIR)
	$(LD) $(LDFLAGS) $(LIB_DIR) -o $(BIN_DIR)/main \
	$(OBJ_DIR)/main.o \
	$(OBJ_DIR)/oglutils.o \
	$(OBJ_DIR)/shaders.o \
	$(OBJ_DIR)/vertFormats.o \
	$(LIBRARIES)
	@echo "\e[92mStart linking...\e[39m"

# compile target
compile: \
	$(OBJ_DIR)/main.o \
	$(OBJ_DIR)/oglutils.o \
	$(OBJ_DIR)/shaders.o \
	$(OBJ_DIR)/vertFormats.o
	@echo "\e[92mLinking done...\e[39m"

# compile sources
$(OBJ_DIR)/main.o: $(OBJ_DIR)
	$(CC) $(CXXFLAGS) $(DEFINES) $(INC_DIR) -c main.cpp -o $(OBJ_DIR)/main.o 

$(OBJ_DIR)/oglutils.o: $(OBJ_DIR)
	$(CC) $(CXXFLAGS) $(DEFINES) $(INC_DIR) -c oglutils.cpp -o $(OBJ_DIR)/oglutils.o 

$(OBJ_DIR)/shaders.o: $(OBJ_DIR)
	$(CC) $(CXXFLAGS) $(DEFINES) $(INC_DIR) -c shaders.cpp -o $(OBJ_DIR)/shaders.o 

$(OBJ_DIR)/vertFormats.o: $(OBJ_DIR)
	$(CC) $(CXXFLAGS) $(DEFINES) $(INC_DIR) -c vertFormats.cpp -o $(OBJ_DIR)/vertFormats.o 

# create folder
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	@echo "\e[92mStart compiling...\e[39m"

# run target
run:
	./bin/main

# clean target
clean:
	@echo "\e[92mClean up...\e[39m"
	rm -rf $(BIN_DIR)
	rm -rf $(OBJ_DIR)
