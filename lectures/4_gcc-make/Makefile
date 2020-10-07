rbt : brackets.o Stack.o
	gcc -o rbt brackets.o Stack.o

brackets.o : brackets.c Stack.h
	gcc -Wall -Werror -c brackets.c

Stack.o : Stack.c Stack.h
	gcc -Wall -Werror -c Stack.c

clean : 
	rm -f *.o rbt 

