treeLab : treeLab.o BSTree.o
	gcc -o treeLab treeLab.o BSTree.o

treeLab.o : treeLab.c BSTree.h
	gcc -Wall -Werror -c treeLab.c

BSTree.o : BSTree.c BSTree.h
	gcc -Wall -Werror -c BSTree.c
