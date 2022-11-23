#include <string.h>  /*memcpy*/
#include <stdlib.h> /*size_t*/
#include <assert.h> /*assert*/

typedef unsigned char BYTE_t;

struct dynamic_vector
{
	size_t element_size;
	size_t capacity;
	size_t size;
	BYTE_t* start_vector;
	
};


#include "dvector.h"




vector_t *DVectorCreate(size_t capacity, size_t element_size)
{
	vector_t *vector = NULL;
	
	assert (EMPTY < element_size);	
	vector = (void *)malloc(sizeof(vector_t));
	
	if (NULL == vector)
	{
		return (NULL);
	}
	
	vector -> element_size = element_size;
	vector -> capacity = capacity;
	vector -> size = EMPTY;
	vector -> start_vector = (void *)malloc((element_size*capacity));
	
	if (NULL == vector -> start_vector)
	{
		free (vector);
		
		return (NULL);
	}
	
	return (vector);
}


void DVectorPushBack(vector_t *vector, const void *element)
{	
	assert (NULL != vector && NULL != element);
	
	if ((vector -> size) == (vector -> capacity))
	{
		DVectorReserve(vector, (vector -> capacity)*FACTOR);
	}


	memcpy(((vector -> start_vector) + (vector -> size)*(vector -> element_size)), element, (vector -> element_size));
	
	if (NULL == vector)
	{
		--(vector -> size);
	}
	
	++(vector -> size);
}

void *DVectorGetAt(const vector_t *vector, size_t index)
{
	assert (NULL != vector);	
	
	return ((vector -> start_vector) + index*(vector -> element_size)); 
}



void DVectorPopBack(vector_t *vector)
{	
	assert (NULL != vector);
	
	--(vector -> size);
}




int DVectorReserve(vector_t *vector, size_t capacity)
{	
	BYTE_t* temp_ptr = NULL; 

	assert (NULL != vector);
	
	temp_ptr = 	(BYTE_t*)realloc((vector -> start_vector), (vector -> element_size)*capacity);
	
	if (NULL == temp_ptr)
	{
		
		temp_ptr = (BYTE_t*)malloc((vector -> element_size)*capacity);
				
		if (NULL == temp_ptr)
		{
			return(1);
		}
		
		memcpy(temp_ptr, vector -> start_vector, vector -> size);
		free (vector -> start_vector);
	} 
	
	(vector -> capacity) = capacity;
	(vector -> start_vector) = temp_ptr;
	
	return (0);
}



int DVectorShrink(vector_t *vector)
{	
	int answer = 0;

	assert (NULL != vector);
	
	if (((vector -> capacity)/FACTOR) < (vector -> size))
	{
		return (0);
	}
	
	answer = DVectorReserve(vector, (vector -> capacity)/FACTOR);

	return (answer);
}


void DVectorDestroy(vector_t *vector)
{
	assert (NULL != vector);
	
	free(vector -> start_vector);
	
	vector -> start_vector = NULL;
	
	free(vector);
}


size_t DVectorSize(const vector_t *vector)
{
	assert (NULL != vector);
	
	return (vector -> size);
}

size_t DVectorCapacity(const vector_t *vector)
{
	assert (NULL != vector);	
	
	return (vector -> capacity);
}













