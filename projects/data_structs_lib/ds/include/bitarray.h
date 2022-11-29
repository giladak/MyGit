#ifndef ILRD_BIT_ARRAY
#define ILRD_BIT_ARRAY

typedef long unsigned int bitarray_t;  

/*
func action: the func sets a bit in a given index
func gets:  
-array of bits.
-index to set.
return value: the bit-array with the new change.
*/
bitarray_t BitArraySetBitOn(bitarray_t bits, size_t index);

/*
func action: the func turns of a bit in a given index
func gets: 
-array of bits.
-index to turn off.
return value: the bit-array with the new change.
*/

bitarray_t BitArraySetBitOff(bitarray_t bits, size_t  index);


/*
func action: the func turns of a bit in a given index to a given value
func gets: 
-array of bits.
-index of bit.
-status - the value you you want to assign .
return value: the bit-array with the new change.
*/

bitarray_t BitArraySetBit(bitarray_t bits, size_t index, int status);

/*
func action: the func gives the user the value of a bit in a given index
func gets: 
-array of bits.
-index of bit.
return value: the bit-array with the new change.
*/

int BitArrayGetBit(bitarray_t bits, size_t index);

/*
func action: the func turns off a bit in a given index
func gets: 
-array of bits.
-index to set.
return value: the bit-array with the new change.
*/

bitarray_t BitArraySetBitOff(bitarray_t bits, size_t  index);

/*
func action: the func sets on all bits
func gets: 
-array of bits.
return value: the bit-array with the new change.
*/
bitarray_t BitArraySetAllOn(bitarray_t bits);

/*
func action: the func sets off all bits
func gets: 
bits- array of bits.
return value: the bit-array with the new change.
*/
bitarray_t BitArraySetAllOff(bitarray_t bits);

/*
func action:  counts the sets bits on.
func gets: 
bits- array of bits.
return value:  the function return the number of sets bits.
*/
size_t BitArrayCountBitsOn(bitarray_t bits);

/*
func action: counts the sets bits off.
func gets: 
-arr- array of bits.
return value:  the function return the number of sets bits.
*/
size_t BitArrayCountBitsOff(bitarray_t bits);

/*
func action: the func shift the bit to left 
func gets: 
bits- array of bits.
shift- shift 'shift' times.
return value: the bit-array with the new change.
*/
bitarray_t BitArrayRotateLeft(bitarray_t bits, size_t shift);

/*
func action: the func shift the bit to right 
func gets: 
bits- array of bits.
shift- shift 'shift' times.
return value: the bit-array with the new change.
*/
bitarray_t BitArrayRotateRight(bitarray_t bits, size_t shift);

/*
func action: the func switch the bits. 0 to 1, 1 to 0. 
func gets: 
bits- array of bits.
return value: the bit-array with the new change.
*/

bitarray_t BitArrayFlipBit(bitarray_t bits, size_t index);

/*
func action: the function reverses the bitarray. 
func gets: 
bits- array of bits.
return value: the bit-array with the new change.
*/

bitarray_t BitArrayMirror(bitarray_t bits);

/*
func action: converts a bitarray to a 64-length string. 
func gets: 
bits- array of bits.
buffer - a memory location for the answer, must contain 64 avaliable bytes.
return value: the string that represnts the bit.
*/


char *BitArrayToString(bitarray_t bits, char *buffer);


#endif /*ILRD_BIT_ARRAY*/








