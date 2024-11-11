# Makefile for my_data_structures project 
#
# make
# make clean

CC = gcc
CFLAGS = -Iinclude
SRC = main.c src/azvs_queue.c
OBJ = main

all: $(OBJ)

$(OBJ): $(SRC)
	$(CC) -o $(OBJ) $(SRC) $(CFLAGS)

clean:
	rm -f $(OBJ)
