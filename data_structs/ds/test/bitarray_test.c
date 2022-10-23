/*
	dev: Gilad Kahn
	review: 
	status: 
*/


#include <stdio.h>  /*printf*/
#include <stdlib.h> /*size_t*/
#include <assert.h> /*assert*/
#include <string.h> /*strcmp*/
#include "bitarray.h"

#define BYTE_NUM sizeof(bitarray_t) * __CHAR_BIT__
#define UNUSED(x) (void)(x)
#define BINARY_BASE 2
#define NULL_BYTE '\0'
#define MAX_BYTE 256
#define BYTES_IN_LONG 8
#define BYTE_BITS 8

void TestBitArrayMirror (void);
void TestBitArraySetBitOn (void);
void TestBitArraySetBitOff (void);
void TestBitArrayFlipBit (void);
void TestBitArraySetAllOn(void);
void TestBitArraySetAllOff(void);
void TestBitArrayGetBit (void);
void TestBitArrayCountBitsOn(void);
void TestBitArrayCountBitsOff(void);
void TestBitArrayToString(void);
void TestBitArrayRotateLeft(void);
void TestBitArrayRotateRight(void);
void TestBitArraySetBit (void);



int main ()
{		
	TestBitArraySetBitOff ();
	TestBitArraySetBitOn();
	TestBitArrayFlipBit();
	TestBitArraySetAllOn();
	TestBitArraySetAllOff();
	TestBitArrayGetBit ();
	TestBitArrayCountBitsOn();
	TestBitArrayCountBitsOff();
	TestBitArrayToString ();
	TestBitArrayMirror ();
	TestBitArrayRotateLeft();
	TestBitArrayRotateRight();
	TestBitArraySetBit();
	
	
	printf ("%lu \n", (0xFFFFFFFFFFFFFFFF));
	
	
	
	return(0);
}

void TestBitArrayCountBitsOff(void)
{
	printf ("TestBitArrayCountBitsOff:\n");
		
	if(0 != BitArrayCountBitsOff(0xFFFFFFFFFFFFFFFF))
	{
		printf ("error in test 1 \n");
	}
	
	if((size_t)1 != BitArrayCountBitsOff(0x7FFFFFFFFFFFFFFF))
	{
		printf ("error in test 2 \n");
	}
	
	if((size_t)57 != BitArrayCountBitsOff(254))
	{
		printf ("error in test 3 \n");
	}
	
	if((size_t)61 != BitArrayCountBitsOff(7))
	{
		printf ("error in test 4 \n");
	}
	
	if((size_t)64 != BitArrayCountBitsOff(0))
	{
		printf ("error in test 5 \n");
	}
}

void TestBitArraySetBit (void)
{
	printf ("TestBitArraysetBit:\n");	
	
	if(10 != BitArraySetBit(11, 0, 0))
	{
		printf ("error in test 1 \n");
	}
	
	if(1 != BitArraySetBit(0, 0, 1))
	{
		printf ("error in test 2 \n");
	}
	 	
	if(148 != BitArraySetBit(20, 7, 1))
	{
		printf ("error in test 3 \n");
	}
	
	if(0x7FFFFFFFFFFFFFFF != BitArraySetBit(0xFFFFFFFFFFFFFFFF, 63, 0))
	{
		printf ("error in test 4 \n");
	}
}




void TestBitArrayCountBitsOn(void)
{
	printf ("TestBitArrayCountBitsOn:\n");
		
	if(64 != BitArrayCountBitsOn(0xFFFFFFFFFFFFFFFF))
	{
		printf ("error in test 1 \n");
	}
	
	if((size_t)63 != BitArrayCountBitsOn(0x7FFFFFFFFFFFFFFF))
	{
		printf ("error in test 2 \n");
	}
	
	if((size_t)7 != BitArrayCountBitsOn(254))
	{
		printf ("error in test 3 \n");
	}
	
	if((size_t)3 != BitArrayCountBitsOn(7))
	{
		printf ("error in test 4 \n");
	}
	
	if((size_t)0 != BitArrayCountBitsOn(0))
	{
		printf ("error in test 5 \n");
	}
}




void TestBitArrayGetBit (void)
{
	printf ("TestBitArrayGetBit:\n");	
	
	if(1 != BitArrayGetBit(11, 1))
	{
		printf ("error in test 1 \n");
	}
	
	if(0 != BitArrayGetBit(10, 1))
	{
		printf ("error in test 2 \n");
	}
	 	
	if(0 != BitArrayGetBit(20, 1))
	{
		printf ("error in test 3 \n");
	}
	
	if(1 != BitArrayGetBit(1, 1))
	{
		printf ("error in test 4 \n");
	}
}

void TestBitArraySetAllOn(void)
{
	printf ("TestBitArraySetAllOn:\n");
		
	if((size_t)-1 != BitArraySetAllOn(5))
	{
		printf ("error in test 1 \n");
	}
	
	if((size_t)-1 != BitArraySetAllOn(10))
	{
		printf ("error in test 2 \n");
	}
}


void TestBitArraySetAllOff(void)
{
	printf ("TestBitArraySetAllOff:\n");
		
	if((size_t)0 != BitArraySetAllOff(5))
	{
		printf ("error in test 1 \n");
	}
	
	if((size_t)0 != BitArraySetAllOff(10))
	{
		printf ("error in test 2 \n");
	}
}


void TestBitArrayMirror (void)
{	

	printf ("TestBitArrayMirror:\n");
	
	if (0x0F0000000000000F != BitArrayMirror(0xF0000000000000F0))
	{	
		printf ("error in test 1 \n");
				
	}
	
	if (0x00000FF000000000 != BitArrayMirror(0x00000000FF00000))
	{
		printf ("error in test 2 \n");
	}
	
	if (0 != BitArrayMirror(0))
	{
		printf ("error in test 3\n");
	}
	
	
	if (0x00000000FFFF0000 != BitArrayMirror(0x0000FFFF00000000))
	{
		printf ("error in test 4\n");
	}
}



void TestBitArraySetBitOn(void)
{

	printf ("TestBitArraySetBitOn:\n");	
	
	if(17 != BitArraySetBitOn(1, 4))
	{
		printf ("error in test 1 \n");
	}
	
	if(64 != BitArraySetBitOn(0, 6))
	{
		printf ("error in test 2 \n");
	}
	 	
	if(1 != BitArraySetBitOn(0, 0))
	{
		printf ("error in test 3 \n");
	}
	
	if(2 != BitArraySetBitOn(0, 1))
	{
		printf ("error in test 3 \n");
	}
	
	if(0x0800000000000001 != BitArraySetBitOn(1, 59))
	{
		printf ("error in test 4 \n");
	}
	
	 	
} 
void TestBitArraySetBitOff (void)
{
	printf ("TestBitArraySetBitOff:\n");	
	
	if(3 != BitArraySetBitOff(19, 4))
	{
		printf ("error in test 1 \n");
	}
	
	if(0 != BitArraySetBitOff(64, 6))
	{
		printf ("error in test 2 \n");
	}
	 	
	if(0 != BitArraySetBitOff(0, 5))
	{
		printf ("error in test 3 \n");
	}
	
	if(0x000000007FFFFFFF != BitArraySetBitOff(0x00000000FFFFFFFF, 31))
	{
		printf ("error in test 4 \n");
	}
}

void TestBitArrayFlipBit (void)
{
	printf ("TestBitArrayFlipBit:\n");	
	
	if(17 != BitArrayFlipBit(1, 4))
	{
		printf ("error in test 1 \n");
	}
	
	if(1 != BitArrayFlipBit(65, 6))
	{
		printf ("error in test 2 \n");
	}
	 	
	if(1 != BitArrayFlipBit(0, 0))
	{
		printf ("error in test 3 \n");
	}
	
	if(0 != BitArrayFlipBit(1, 0))
	{
		printf ("error in test 4 \n");
	}
	
	if(0x000000000FFFFFF0 != BitArrayFlipBit(0x000000000FFFFFF1, 0))
	{
		printf ("error in test 5 \n");
	}
	
	if(0x1000000000000000 != BitArrayFlipBit(0, 60))
	{
		printf ("error in test 6 \n");
	}
}


void TestBitArrayToString (void)
{
	bitarray_t a = 0xFFFFFFFFFFFFFFFF;
	bitarray_t b = 0;
	bitarray_t c = 35;
	bitarray_t d = 1;
	
	
	char answer_a[64];
	char answer_b[64];
	char answer_c[64];
	char answer_d[64];
	char answer_a_copy[64] = "1111111111111111111111111111111111111111111111111111111111111111";
	char answer_b_copy[64] = "0000000000000000000000000000000000000000000000000000000000000000";
	char answer_c_copy[64] = "0000000000000000000000000000000000000000000000000000000000100011";
	char answer_d_copy[64] = "0000000000000000000000000000000000000000000000000000000000000001";
	
	
	printf ("Test BitArrayToString:\n");
	
	if (0 != strncmp(BitArrayToString(a, answer_a), answer_a_copy, 64))
	{
			printf ("error in test 1 \n");
			printf ("%s \n\n", answer_a);
			printf ("%s \n\n", answer_a_copy);
	}
	if (0 != strncmp(BitArrayToString(b, answer_b), answer_b_copy, 64))
	{
			printf ("error in test 2 \n");
			printf ("%s \n", answer_b);
	}
	if (0 != strncmp(BitArrayToString(c, answer_c), answer_c_copy, 64))
	{
			printf ("error in test 3 \n");
			printf ("%s \n", answer_c);
	}
	if (0 != strncmp(BitArrayToString(d, answer_d), answer_d_copy, 64))
	{
			printf ("error in test 4 \n");
			printf ("%s \n", answer_d);
	}
}



void TestBitArrayRotateRight(void)
{
	bitarray_t test1_ans = 0x000F00000000000F;
	bitarray_t test1 = 0x00F00000000000F0;
	bitarray_t test2_ans = 0xFFFFFFFFFFFFFFF0;
	bitarray_t test2 = 0xFFFFFFFFFFFFF0FF;
	bitarray_t test3_ans = 0x0010000000000000;
	bitarray_t test3 = 0x0000000000000010;
	bitarray_t test4_ans = 0x0000000000000000;
	bitarray_t test4 = 0x0000000000000000;
	bitarray_t test5_ans = 0x0000000000000001;
	bitarray_t test5 = 0x0000000000000002;
	
	printf ("Test BitArrayRotateRight:\n");
	
	if (test1_ans != BitArrayRotateRight(test1,4))
	{
		printf ("error in test 1 \n");
	}	
	
	if (test2_ans != BitArrayRotateRight(test2,8))
	{
		printf ("error in test 2 \n");
	}	
	
	if (test3_ans != BitArrayRotateRight(test3,16))
	{
		printf ("error in test 3 \n");
	}	
	
	if (test4_ans != BitArrayRotateRight(test4,25))
	{
		printf ("error in test 4 \n");
	}
	if (test5_ans != BitArrayRotateRight(test5,1))
	{
		printf ("error in test 5 \n");
	}	
}







void TestBitArrayRotateLeft(void)
{
	bitarray_t test1 = 0x000F00000000000F;
	bitarray_t test1_ans = 0x00F00000000000F0;
	bitarray_t test2 = 0xFFFFFFFFFFFFFFF0;
	bitarray_t test2_ans = 0xFFFFFFFFFFFFF0FF;
	bitarray_t test3 = 0x0010000000000000;
	bitarray_t test3_ans = 0x0000000000000010;
	bitarray_t test4 = 0x0000000000000000;
	bitarray_t test4_ans = 0x0000000000000000;
	bitarray_t test5 = 0x0000000000000001;
	bitarray_t test5_ans = 0x0000000000000002;
	
	printf ("Test BitArrayRotateLeft:\n");
	
	if (test1_ans != BitArrayRotateLeft(test1,4))
	{
		printf ("error in test 1 \n");
	}	
	
	if (test2_ans != BitArrayRotateLeft(test2,8))
	{
		printf ("error in test 2 \n");
	}	
	
	if (test3_ans != BitArrayRotateLeft(test3,16))
	{
		printf ("error in test 3 \n");
	}	
	
	if (test4_ans != BitArrayRotateLeft(test4,25))
	{
		printf ("error in test 4 \n");
	}
	if (test5_ans != BitArrayRotateLeft(test5,1))
	{
		printf ("error in test 5 \n");
	}	
}



