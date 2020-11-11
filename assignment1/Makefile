# Makefle for Ass1

CC = gcc
CFLAGS = -Wall -Werror -std=c11 -g

all: test_Ass1

invertedIndex.o: invertedIndex.c invertedIndex.h

test_Ass1: test_Ass1.c invertedIndex.o

clean: 
	rm -f *.o test_Ass1