
#include <stdio.h>  /*printf*/
#include <stdlib.h> /*size_t*/
#include <stddef.h> /*size_t*/
#include <assert.h> /*assert*/
#include <string.h> /*memcpy*/
#include <unistd.h> /*ssize_t*/
#include "cbuffer.h"
#include "utilities.h"


#define BYTE char
#define OFFSETOF(TYPE, ELEMENT) ((size_t)&(((TYPE *)0)->ELEMENT))




struct circular_buffer 
{   
    size_t size;
    size_t capacity;
    size_t read_head; 
    char buffer[1]; 
    
};


/**************************CBufferCreate*****************************************/

cbuff_t *CBufferCreate(size_t capacity)
{
	cbuff_t *new_buffer = (cbuff_t *)malloc(OFFSETOF(cbuff_t, buffer) + capacity);
	
	if (NULL == new_buffer)
	{
		return (NULL);
	}
	
	new_buffer -> size = 0;
	new_buffer -> capacity = capacity;
	new_buffer -> read_head = 0;
	
	return (new_buffer);
}


/**************************CBufferDestroy*****************************************/

void CBufferDestroy(cbuff_t *buffer)
{
	assert(buffer);
	
	free(buffer);
}

/**************************CBuffeCBufferIsEmptyrWrite*****************************************/


int CBufferIsEmpty(const cbuff_t *buffer)
{
	assert(buffer);	
	
	return (buffer -> size == 0);
}


/**************************CBufferWrite*****************************************/

ssize_t CBufferWrite(cbuff_t *buffer, const void *src, size_t count)
{
	size_t pre_end = 0;
	size_t post_end = 0;
	size_t write_index = 0;
	char* u_src = (char*)src;
	
	
	write_index = ((buffer -> size) + (buffer -> read_head)) % (buffer -> capacity);
	
	assert(src);
	assert(buffer);	
	
	if (count > CBufferFreeSpace(buffer))
	{
		count = CBufferFreeSpace(buffer);
	}
	
	pre_end = (buffer -> capacity) - write_index;
	
	if (count > pre_end)
	{
		post_end = count - pre_end;
		
		memcpy (&(buffer -> buffer[write_index]), u_src, pre_end);
		
		u_src += pre_end;
		
		memcpy (buffer -> buffer, u_src, post_end);
	}
	
	else
	{
		memcpy (&(buffer -> buffer[write_index]), u_src, count);
	}	 
	
	(buffer -> size) += count;
	
	return(count);
}

/**************************CBufferRead*****************************************/


ssize_t CBufferRead(cbuff_t *buffer, void *dest, size_t count)
{	

	size_t pre_end = 0;
	size_t post_end = 0;
	char *u_dest = (char*)dest;
	
	assert(dest);
	assert(buffer);
	
	
	if (count > (buffer -> size))
	{
		count = (buffer -> size);
	}
	
	
	pre_end = (buffer -> capacity) - (buffer -> read_head);
	
	if (count > pre_end)
	{
		post_end = count - pre_end;
		
		memcpy (u_dest, &(buffer -> buffer[buffer -> read_head]), pre_end);
		
		 u_dest += pre_end;
		
		memcpy (u_dest ,buffer -> buffer, post_end);
	}
	
	else
	{	
		memcpy (u_dest, &(buffer -> buffer[buffer -> read_head]), count);
	}	
	
	
	(buffer -> size) -= count;
	(buffer -> read_head) = ((buffer -> read_head) + count) % (buffer -> capacity) ;
	
	
	if (0 == (buffer -> size))
	{
		(buffer -> read_head) = 0;
	}
	
	return (count);
}


/**************************CBufferSiz*****************************************/

size_t CBufferSiz(const cbuff_t *cbuffer)
{
	assert (cbuffer);
	
	return (cbuffer -> size);
}



/**************************CBufferFreeSpace*****************************************/

size_t CBufferFreeSpace(const cbuff_t *cbuffer)
{
	assert (cbuffer);
	
	return ((cbuffer -> capacity) - (cbuffer -> size));
}








