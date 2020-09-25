// apply Collatz's process to command line argument ... COMP9024 17s2
#include <stdio.h>
#include <stdlib.h>

void collatz(int n) {
   printf("%d\n", n);
   while (n != 1) {
      if (n % 2 == 0)
	 n = n / 2;
      else
	 n = 3*n + 1;
      printf("%d\n", n);
   }
}

int main(int argc, char *argv[]) {
   if (argc != 2) {
      printf("Usage: %s [number]\n", argv[0]);
      return 1;
   }
   int n = atoi(argv[1]);
   if (n > 0)
      collatz(n);
   return 0;
}
