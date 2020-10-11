CC = gcc
CFLAGS = -Wall -Werror -g
LDFLAGS = -Wall -Werror -g

.PHONY: all
all: test_Ass1

test_Ass1: test_Ass1.o invertedIndex.o
test_Ass1.o: test_Ass1.c invertedIndex.h
invertedIndex.o: invertedIndex.c invertedIndex.h

.PHONY: clean
clean:
	-rm -f test_Ass1 test_Ass1.o invertedIndex.o