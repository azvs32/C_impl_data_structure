# Makefile for my_data_structures project 
#
# make
# make clean

CC = gcc
CFLAGS = -Iinclude
SRC = main.c src/azvs_base.c src/azvs_queue.c src/azvs_stack.c src/azvs_list.c
OBJ = main

all: $(OBJ)

$(OBJ): $(SRC)
	$(CC) -o $(OBJ) $(SRC) $(CFLAGS)

clean:
	rm -f $(OBJ)
