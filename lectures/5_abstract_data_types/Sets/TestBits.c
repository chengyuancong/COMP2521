// BitS union

#include <stdlib.h>
#include <stdio.h>

#define NBITS 64
#define NWORDS (NBITS/32)

typedef unsigned int Word;

typedef Word BitS[NWORDS];

void BitUnion(BitS a, BitS b, BitS c);
void BitInsert(BitS a, int i);
void BitDelete(BitS a, int i);
char getBit(BitS a, int i);

BitS a, b, c;

// a: 0010101010100001100110100101100100101001...
// b: 1101000010010000000100100000010001001000...
// c':1111101010110001100110100101110101101001...

void BitIntersect(BitS a, BitS b, BitS c)
{
	int i;

	for (i = 0; i < NWORDS; i++) {
		c[i] = a[i] & b[i];
	}
}


void BitUnion(BitS a, BitS b, BitS c)
{
	int i;

	for (i = 0; i < NWORDS; i++) {
		c[i] = a[i] | b[i];
	}
}

void BitInsert(BitS a, int i)
{
	int whichWord = i/32;
	int whichBit  = i%32;

	a[whichWord] = a[whichWord] | (1 << whichBit);
//OR
//	a[whichWord] |= (1 << whichBit);
}

void BitDelete(BitS a, int i)
{
	int whichWord = i/32;
	int whichBit  = i%32;
/*
    00000001
    00000100  << 2
    11111011  ~

    11111011  mask
    10101100  &
    --------
    10101000
*/
	a[whichWord] = a[whichWord] & (~(1 << whichBit));
/*
OR
	a[whichWord] &= (~(1 << whichBit));
*/ 
}

void BitSPrint(BitS a)
{
	int i;
	for(i=0; i<NBITS; i++){
		printf("%c", getBit(a, i) );
	}
	printf("\n");
}


void BitSReset(BitS a)
{
	int i;
	for(i=0; i<NWORDS; i++){
		a[i] = 0;
	}
	printf("\n");
}

char getBit(BitS a, int i)
{
	int whichWord = i/32;
	int whichBit  = i%32;

	Word w  = a[whichWord] & (1 << whichBit);	
	if(w > 0 ) {
		return '1';
	}
 	else {
		return '0';
	}
}

char getBitWord(Word w, int whichBit)
{
	Word w1  = w & (1 << whichBit);	
	if(w1 > 0 ) {
		return '1';
	}
 	else {
		return '0';
	}
}

void WordPrint(Word w)
{
	int i;
	for(i=31; i>=0; i--){
		printf("%c", getBitWord(w, i) );
	}
	printf("\n");
}


int main(int argc, char *argv[])
{
	BitS s1, s2, s3, s4;

	BitSReset(s1);
	BitSReset(s2);

	BitInsert(s1, 2);
	printf("> Set s1: \n");
	BitSPrint(s1);

	BitInsert(s2, 8);
	printf("> Set s2: \n");
	BitSPrint(s2);

	BitUnion(s1, s2, s3);	
	printf("> Set s3 (s1 union s2): \n");
	BitSPrint(s3);

	BitIntersect(s1, s2, s4);
	printf("> Set s4 (s1 intersect s2): \n");
	BitSPrint(s4);

/*
	The following code is provided to experiment with bitwise 
 	operations ..  
*/
	printf("\n\n *** Experimenting with bitwise operations! \n");
	printf("	for more, see the source code! \n\n");
	Word x = 1;
	WordPrint(x);

	printf("\n");
	x = x >>  2; 
	WordPrint(x);

	Word z = 0xFF; 
	WordPrint(z);
	z = x & 0xFF; 
	WordPrint(z);

	WordPrint(0xF0F);

	return EXIT_SUCCESS;
}





