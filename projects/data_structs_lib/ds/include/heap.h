#ifndef ILRD_Heap
#define ILRD_Heap

#include <stddef.h> /*size_t*/
#include <stddef.h>

#include "dvector.h"




typedef struct heap heap_t; /*in header*/

/*
description: creats a new Heap
 
 arguments:
 cmp- a compare function that will decide where the new data shall be inserted
 capacity: the begining capacity of the new heap

 return value: a pointer to the new Heap
 
 complexity: 0(1)
*/

heap_t *HeapCreate(int(*cmp)(const void *data1, const void *data2), size_t capacity);
/*****************************************
 
	description: destrpys a Heap
 
 arguments:
 	heap - a pointer to the new Heap

 return value: a pointer to the new Heap
 
 complexity: 0(1)

*****************************************/

void HeapDestroy(heap_t *heap);
/*****************************************
	description: removes data from the heap
 
 arguments:
 	heap - a pointer to the Heap
	is_matched - a function to define the data to be removed
	param- the parameter of the function

 return value: non
 
 complexity: 0(logn)
 *****************************************/
void *HeapRemove(heap_t *heap, int(*is_matched)(const void *data, const void *param), const void *param);
/*****************************************
 	description: adds data to the top of the heap
 
 arguments:
 	heap - a pointer to the Heap
	element - a pointer to the data the user wants to remove
	

 return value: 0 on sucsess, 1 in failure
 
 complexity: 0(1) 
 *****************************************/
int HeapPush(heap_t *heap, void *element);

/*****************************************
description: removes a element from the top of the heap
 
 arguments:
 	heap - a pointer to the Heap

 return value: non
 
 complexity: 0(1) 
 *****************************************/
void HeapPop(heap_t *heap);

/*****************************************
 description: presents the size of the heap
 
 arguments:
 	heap - a pointer to the Heap

 return value: the size of the heap
 
 complexity: 0(n) 
 *****************************************/
size_t HeapSize(const heap_t *heap);
/*****************************************
 description: check if the heap is empty
 
 arguments:
 	heap - a pointer to the Heap

 return value: the size of the heap
 
 complexity: 0(1) 
 *****************************************/
int HeapIsEmpty(const heap_t *heap);
/*****************************************
description: gives the user the data in the top of the heap
 
 arguments:
 	heap - a pointer to the Heap

 return value: the size of the heap
 
 complexity: 0(1) 
 *****************************************/
void *HeapPeek(const heap_t *heap);



void PrintHeap (const heap_t *heap);

    
 
#endif /*ILRD_Heap*/
