
# Building:
# make
# Cleaning:
# make clean

# TODO: Add automatic include file dependencies.
# TODO: Add a dependency on edits to make file.

MAKEFLAGS += -j8

OBJ_DIR=./build
SRC_DIR=./src
BIN_DIR=./bin
TARGET=$(BIN_DIR)/adsb_filter 

SRC=$(wildcard $(SRC_DIR)/*.cpp)
OBJS=$(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
CC=g++
CFLAGS=-O3 -Wall -Werror

$(TARGET):$(OBJS) | $(BIN_DIR)
	$(CC) $(LDFLAGS) $(CFLAGS) $(OBJS) -o $@

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CC) $(CFLAGS) $< -c -o $@

$(OBJ_DIR) $(BIN_DIR):
	mkdir -p $@

clean:
	$(RM) $(OBJS)
	$(RM) $(TARGET)

.PHONY: clean
