// findMax1.c ... find max value in an array
// Written by John Shepherd, July 2015

#include <stdlib.h>
#include <stdio.h>

int findMax(int *a, int N);

int main(int argc, char **argv)
{
	int i, N, max, *array;

	// assumes argv[1] is digits
	N = (argc < 2) ? 100 : atoi(argv[1]);

	if ((array = malloc(N*sizeof(int))) == NULL) {
		fprintf(stderr, "Couldn't allocate a[%d]\n",N);
		exit(EXIT_FAILURE);
	}
	for (i = 0; i < N; i++) {
		array[i] = random()%1000;
	}

	if (N < 1)
		max = -1;
	else
		max = findMax(array, N);

	printf("Max = %d\n", max);
	return EXIT_SUCCESS;
}

int findMax(int a[], int N)
{
	int i, max;
	max = a[0];
	for (i = 0; i < N; i++) {
		if (a[i] > max) {
			max = a[i];
		}
	}
	return max;
}
