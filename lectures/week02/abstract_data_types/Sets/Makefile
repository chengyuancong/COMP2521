# Makefile for Set ADT

CC = gcc
CFLAGS = -Wall -Werror -g

all : ts slab

ts : testSet.o Set.o
	$(CC) -o ts testSet.o Set.o

slab : SetLab.o Set.o
	$(CC) -o slab SetLab.o Set.o

testSet.o : testSet.c Set.h
	$(CC) $(CFLAGS) -c testSet.c

SetLab.o : SetLab.c Set.h
	$(CC) $(CFLAGS) -c SetLab.c

Set.o : Set.c Set.h Bool.h

clean :
	rm -f *.o slab ts core

