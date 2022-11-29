#ifndef UTILITIES_H
#define UTILITIES_H

#include <stdio.h>

#define WORD_SIZE sizeof(size_t)
#define BYTE_BITS 8
#define BYTE_MAX 255
#define NULL_BYTE 1
#define ENDIANESS (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)? 1 : 0
#define CHAR_NUM 127
#define ASCII_NINE 9
#define ASCII_ZERO '0'
#define ASCII_Z 36
#define NEGETIVE -1
#define NEGETIVE_CHAR 45
#define BASE_TEN 10
#define MAX_BYTE 256
#define BYTES_IN_LONG 8
#define HALF_OF(x) (x / 2)
#define POINTER_SIZE sizeof(void *)




#define ON 1
#define OFF 0 


#define TRUE 1
#define FALSE 0 

#define FAIL 1
/*
#define SUCCESS 0
*/

#define FULL 1
#define EMPTY 0


#define MAX(a, b)   ((a > b)?a:b) 
#define MAXTHREE(a, b, c)    ((a > b && a > c) ? a : (b > c) ? b : c )
#define SIZEOF_TYPE(x) (size_t)((x *)0 + 1)
#define SIZEOF_VAR(type) (char*)(&type+1)-(char *)(&type)
#define TIME_CHECK(s) begin = clock(); s ; end = clock();time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

#define UNUSED(x) (void)x





/***********************functions***********************/





#endif /*UTILITIES_H*/








