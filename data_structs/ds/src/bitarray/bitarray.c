/*
	dev: Gilad Kahn
	review: Alon Levy
	status: approved
	date: 3.1.22 
*/


#include <stdio.h>  /*printf*/
#include <stdlib.h> /*size_t*/
#include <assert.h> /*assert*/
#include "bitarray.h"
#define BYTE_NUM sizeof(bitarray_t) * __CHAR_BIT__
#define UNUSED(x) (void)(x)
#define BINARY_BASE 2
#define NULL_BYTE '\0'
#define MAX_BYTE 256
#define BYTES_IN_LONG 8
#define BYTE_BITS 8


	static unsigned char set_on_table[256] = {0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,  1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,  1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,  2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,  3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8};



/*
	dev: Gilad Kahn
	review: Alon Levy
	status: approved
	date: 3.1.22 
*/

bitarray_t BitArraySetBitOn(bitarray_t bits, size_t index)
{	
	assert (BYTE_NUM > index); 	
	
	bits = bits | (size_t)1 << (index);
	
	return(bits);
}



/*
	dev: Gilad Kahn
	review: Alon Levy
	status: approved
	date: 3.1.22 
*/

bitarray_t BitArraySetBit(bitarray_t bits, size_t index, int status)
{	
	assert (BYTE_NUM > index);
	assert (status == 0 || status == 1);	
	
	bits = bits | (size_t)status << (index);
	
	status ^= 1;
	
	bits = bits & (~((size_t)status << (index)));
	
	return(bits);
}



/*
	dev: Gilad Kahn
	review: Alon Levy
	status: approved
	date: 3.1.22 
*/
bitarray_t BitArraySetBitOff(bitarray_t bits, size_t  index)
{	
	assert (BYTE_NUM > index);	
	
	bits = bits & (~((size_t)1 << (index)));
	
	return(bits);
}

/*
	dev: Gilad Kahn
	review: Alon Levy
	status: approved
	date: 3.1.22 
*/
bitarray_t BitArrayFlipBit(bitarray_t bits, size_t index)
{	
	assert (BYTE_NUM > index);	
	
	bits = bits ^ ((size_t)1 << (index));
	
	return(bits);
}


/*
	dev: Gilad Kahn
	review: Alon Levy
	status: approved
	date: 3.1.22 
*/
bitarray_t BitArraySetAllOn(bitarray_t bits)
{	
	bits |= 0xFFFFFFFFFFFFFFFF;
	
	return(bits);
}


/*
	dev: Gilad Kahn
	review: Alon Levy
	status: approved
	date: 3.1.22 
*/

int BitArrayGetBit(bitarray_t bits, size_t index)
{	
	assert (BYTE_NUM > index);	
		
	bits =  1 & (bits >> (index - 1));
	
	return (bits); 
}

/*
	dev: Gilad Kahn
	review: Alon Levy
	status: approved
	date: 3.1.22 
*/
bitarray_t BitArraySetAllOff(bitarray_t bits)
{	
	bits = 0;
		
	return(bits);
}

/*
	dev: Gilad Kahn
	review: Alon Levy
	status: approved
	date: 3.1.22 
*/
size_t BitArrayCountBitsOn(bitarray_t bits)
{	
	size_t count = 0;
	size_t i = 0;

	for (i = 0; i < BYTES_IN_LONG; ++i)
		{	
		
			/*we isolate every byte and count its sets with a lut*/
		
			count += set_on_table[bits&(0x000000FF)]; /*000000011111111*/
			
			bits >>= BYTE_BITS;
		}
	return (count);
}




/*
	dev: Gilad Kahn
	review: Alon Levy
	status: approved
	date: 3.1.22 
*/
size_t BitArrayCountBitsOn2(bitarray_t bits)
{	
	size_t count = 0;
	
	while (0 != bits)
	{
     	bits = bits & (bits - 1);    
     	++count;			
	}
	
	return(count);	
}


/*
	dev: Gilad Kahn
	review: Alon Levy
	status: approved
	date: 3.1.22 
*/
size_t BitArrayCountBitsOff(bitarray_t bits)
{
	size_t result = BYTE_NUM - BitArrayCountBitsOn(bits);
	
	return (result);
}


/*
	dev: Gilad Kahn
	review: Alon Levy
	status: approved
	date: 3.1.22 
*/
char *BitArrayToString(bitarray_t bits, char *buffer)
{
	
	int i = BYTE_NUM - 1;
	int remainder = 0;
	char ascii_char[2] = "01";
	buffer [BYTE_NUM] = NULL_BYTE;
	
	while (0 <= i)
	{ 
		remainder = bits % BINARY_BASE;
		buffer[i] =  ascii_char[remainder];
		
		--i;
		bits /= BINARY_BASE;
	}
	
	return(buffer);
}



/*
	dev: Gilad Kahn
	review: Alon Levy
	status: approved
	date: 3.1.22 
*/
unsigned char ByteMirror (unsigned char n)
{
	n = (n & 170) >> 1 | (n & 85) << 1;	
	n = (n & 204) >> 2 | (n & 51) << 2;	 	
	n = (n & 240) >> 4 | (n & 15) << 4;  

	return (n);
}


/*
	dev: Gilad Kahn
	review: Alon Levy
	status: approved
	date: 3.1.22 
*/
bitarray_t BitArrayMirror(bitarray_t bits)
{
	size_t i;
	bitarray_t temp = bits;
	bitarray_t result = 0;

	static int mirrorlut [MAX_BYTE]; 

/****we intilize a lut ****/	
		
	for (i = 0; i < MAX_BYTE; ++i)
	{
		mirrorlut [i] = ByteMirror(i);
	}
	
	
/****we assign the relevant values to a byte in a time ****/	
	
	for (i = 0; i < BYTES_IN_LONG; ++i)
	{	
		temp = bits;
		/*we isolate every byte and reverse it with the lut*/
		
		temp = temp >> (i*BYTE_BITS);
		temp = temp & 0x000000FF; 
		temp = mirrorlut[temp];
		
		/*we assign the reversed byte to the right location*/
		
		result |= temp << ((BYTES_IN_LONG - i - 1)*BYTE_BITS);
	}
	
	return (result);
}


/*
	dev: Gilad Kahn
	review: Alon Levy
	status: approved
	date: 3.1.22 
*/

bitarray_t BitArrayRotateLeft(bitarray_t bits, size_t shift)
{	
	assert (BYTE_NUM > shift); 		
	
	bits = bits << shift | bits >> (BYTE_NUM - shift); 
	
	return  (bits);
}


/*
	dev: Gilad Kahn
	review: Alon Levy
	status: approved
	date: 3.1.22 
*/
bitarray_t BitArrayRotateRight(bitarray_t bits, size_t shift)
{
	assert (BYTE_NUM > shift);

	bits = bits >> shift | bits << (BYTE_NUM - shift); 
	
	return  (bits);
}





