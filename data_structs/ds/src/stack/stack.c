#include <stdio.h>  /*printf*/
#include <string.h>  /*memcpy*/
#include <stdlib.h> /*size_t*/
#include <assert.h> /*assert*/
#include "stack.h"

#define EMPTY 0


stack_t *StackCreate(size_t capacity, size_t element_size)
{	
	
	stack_t *stack = NULL;	
	stack = (void *)malloc((element_size*capacity) + sizeof(stack_t)); 
	
	assert (EMPTY != capacity);
	assert (EMPTY < element_size);	
	
	stack -> element_size = element_size;
	stack -> capacity = capacity;
	stack -> size = EMPTY;
	stack -> start_stack = (char*)(stack + sizeof(stack_t));
	
	if (NULL == stack)
	{
		printf ("you don't have enough free memory \n");
	}
	
	return (stack);
}

void StackDestroy(stack_t *stack)
{	
	assert(NULL != stack);	
	
	free(stack);
}





void StackPop(stack_t *stack)
{	
	assert (NULL != stack);	
	
	--(stack -> size);
}


void StackPush(stack_t *stack, const void *element)
{	
	assert (NULL != stack && NULL != element);
		
	memcpy(((stack -> start_stack) + (stack -> size)*(stack -> element_size)), element, (stack -> element_size));

	++(stack -> size);	
}





void *StackPeek(const stack_t *stack)
{
	assert (NULL != stack);

	return ((stack -> start_stack) + ((stack -> size) - 1)*(stack -> element_size)); 
}






int StackIsEmpty(const stack_t *stack)
{	
	assert (NULL != stack);	
	
	return (EMPTY == stack -> size);
}





size_t StackSize(const stack_t *stack)
{
	assert (NULL != stack);
	
	return (stack -> size);
}




size_t StackCapacity(const stack_t *stack)
{	
	assert (NULL != stack);	
	
	return (stack -> capacity);
}



