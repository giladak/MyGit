
#ifndef DYNAMIC_VECTOR_H
#define DYNAMIC_VECTOR_H



#include <stdio.h>  /*printf*/


#define EMPTY 0
#define FACTOR 2


typedef struct dynamic_vector vector_t;







/* description: a function that intilaizes a dynamic vector

	arguments:
	- the capacity of the dynamic vector
	- the size of the inserted elements
	
	return value: a pointer to the dynamic_vector struct
*/ 	


vector_t *DVectorCreate(size_t capacity, size_t element_size);


/* description: a function that inserts a element to the dynamic_vector/
	if the number of elements inserts is equaled to the current capacity, the function will double the memory for the program

	arguments:
	- a pointer to a element to insert
	- a pointer to the vector
	
	return value: no return value
*/ 	

void DVectorPushBack(vector_t *vector, const void *element);

/* description: a function that deduces a element from the vector

	arguments:
	- a pointer to the vector
	
	return value: no return value
*/ 	


void DVectorPopBack(vector_t *vector);


/* 
	description: a function that represents a element from a given index

	arguments:
	- a pointer to the vector
	- the index the user wants to view. the index count starts from 0 (0 is the first elements index).
	
	return value: a void pointer to the given element
*/ 	



void *DVectorGetAt(const vector_t *vector, size_t index);


/* description: a function that reserve more space for the vector

	arguments:
	- a pointer to the vector
	- the desired capacity
	
	return value: returns 0 in sucsses and 1 in failure
*/

int DVectorReserve(vector_t *vector, size_t capacity);


/* description: a function that deduces the size of the vetor in half, the function will do so in condittion that this action wont delete non-poped elements from the vector

	arguments:
	- a pointer to the vector
	- the desired capacity
	
	return value: returns 0 in sucsses and 1 in failure
*/



int DVectorShrink(vector_t *vector);

/* description: a function that frees all the allocated memory

	arguments:
	- a pointer to the vector
	
	return value: no return value
*/ 	


void DVectorDestroy(vector_t *vector);

/* description: a function that gives the user the size of the vector

	arguments:
	- a pointer to the vector
	
	return value: the current size of the vector
*/ 	

size_t DVectorSize(const vector_t *vector);

/* description: a function that gives the capacity of the vector

	arguments:
	- a pointer to the vector
	
	return value: the current size of the vector
*/ 	


size_t DVectorCapacity(const vector_t *vector);



#endif  /*dynamic_vector*/









