CC = gcc
CFLAGS = -Wall -Werror

bchk : brackets.o Stack.o
	gcc -o bchk brackets.o Stack.o

brackets.o : brackets.c Stack.h

Stack.o : Stack.c Stack.h Bool.h

Stack.h : Bool.h

clean :
	rm -f *.o bchk core
