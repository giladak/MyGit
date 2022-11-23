
#include <stdio.h>  /*printf*/
#include <stdlib.h> /*malloc*/
#include <stddef.h> /*size_t*/
#include <string.h> /*memcpy*/
#include <unistd.h> /*ssize_t*/
#include <assert.h> /*assert*/

#include "cbuffer.h"
#include "utilities.h"



struct circular_buffer 
{   
    size_t size;
    size_t capacity;
    size_t read_head; 
    char buffer[1]; 
    
};




void CbufferTests (void)
{
	cbuff_t *test = NULL;
	
	int a = 5;
	int b = 10;
	size_t capacity = 20;
	
	char A = 'A';
	char B = 'B';
	char*string = "hello_world_today_";
	
	char buffer_copy[20] = {0};	
	 	
	printf ("Cbuffer Tests: \n");

	/*******check if created *********/
	
	test = CBufferCreate(capacity);
	
	if (NULL == test)
	{
		printf ("error in create test 1 \n");
	}
	
	if (1 != CBufferIsEmpty(test) && capacity != CBufferFreeSpace(test))
	{
		printf ("error in frre space / IsEmpty test 1 \n");
	}
	
	/*******check if write and read sucseeds *********/
	
		
	CBufferWrite(test, &a, sizeof(int));
	CBufferWrite(test, &b, sizeof(int));	
	
	if (0 != memcmp(test -> buffer, &a, sizeof (int)))
	{
		printf ("error in write test 1 \n");
		
		printf ("%d \n", a);
	}

	CBufferRead(test, buffer_copy, sizeof (int));
	
	if (0 != memcmp(buffer_copy, &a, sizeof (int)))
	{
		printf ("error in read test 1 \n");
		
		printf ("%d \n", *(int*)(test -> buffer));
		printf ("%d \n", *(int*)(buffer_copy));
	}
	
	
	if (4 != CBufferSiz(test))
	{
		printf ("error in cbuffersiz test 1 \n");
	}
	
	
	CBufferRead(test, buffer_copy, sizeof (int));
	
	if (0 != memcmp(buffer_copy, &b, sizeof (int)))
	{
		printf ("error in read test 2 \n");
	}		
		
	/*******check if a circule can cross the end of the array*********/
	
	CBufferWrite(test, &A, sizeof (char));
	CBufferWrite(test, &B, sizeof (char));
	CBufferWrite(test, string, sizeof(char)*18);
	
	if (0 != CBufferFreeSpace(test))
	{
		printf ("error in loop test 1 \n");
	}
	
 /*******check if doesnt insert if full***************************/
	
	if (0 != CBufferWrite(test, &A, sizeof (char)))
	{
		printf ("error in block_if_full test 1 \n");
	}

	
 /***********************more tests******************************/
/*
	CBufferRead(test, buffer_copy, sizeof (char));

	if (1 != CBufferWrite(test, &A, sizeof (char)))
	{
		printf ("error in block_if_full test 2 \n");
	}
*/	
	CBufferRead(test, buffer_copy, sizeof (char));
	CBufferRead(test, buffer_copy, sizeof (char));
	CBufferRead(test, buffer_copy, sizeof (char)*18);

	
	if (0 != strncmp (string, buffer_copy, 18))
	{
			printf ("error in gap test 1 \n");
			printf ("%s \n", buffer_copy);
			printf ("%s \n", string);
	}			
	
	
	
	
	CBufferDestroy(test);
}


int main()
{
	
	CbufferTests();
	
	printf ("%d \n", BUFSIZ);


	return (0);
}



