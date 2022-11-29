#ifndef PRIORITY_QUEUE_HEAP_H
#define PRIORITY_QUEUE_HEAP_H

#include <stddef.h> /*size_t*/

#include "heap.h"


struct pq_heap
{
	heap_t *heap;
	int(*cmp)(const void *, const void *);
};


typedef struct pq_heap pq_heap_t;




/*************************************************************************************************************************
DESCRIPTION: creates a empty Priority Queue
	
ARGUMENTS: the comparison function of the queue
	
RETURN VALUE: the adress of the new queue
	
	
complexity: O(1)

***********************************************************************************************************/
pq_heap_t *PriorityQueueHeapCreate(int(*cmp)(const void* data1, const void* data2));



/*************************************************************************************************************************
DESCRIPTION: destroys a Priority Queue and frees all the memory
	
ARGUMENTS: the adress of the queue
	
RETURN VALUE: non
	
	
complexity: O(n)
************************************************************************************************************************/
void PriorityQueueHeapDestroy(pq_heap_t *queue);


/*************************************************************************************************************************
DESCRIPTION: adds a element to the end of the queue
	
ARGUMENTS: the adress of the queue
	
RETURN VALUE: 0 in sucsess 1 in failure
	
	
complexity: O(n)
***********************************************************************************************************/
int PriorityQueueHeapEnqueue(pq_heap_t *queue, void *data);


/*************************************************************************************************************************
DESCRIPTION: removes a element from the head of the queue
	
ARGUMENTS: the adress of the queue
	
RETURN VALUE: the adress in of the stored in the element
	
	
complexity: O(1)
***********************************************************************************************************/
void *PriorityQueueHeapDequeue(pq_heap_t *queue);


/*************************************************************************************************************************
DESCRIPTION: checks the size of the queue
	
ARGUMENTS: the adress of the queue
	
RETURN VALUE: the size of the queue
	
	
complexity: O(n)
***********************************************************************************************************/
size_t PriorityQueueHeapSize(const pq_heap_t *queue);


/*************************************************************************************************************************
DESCRIPTION: checks if the queue is empty
	
ARGUMENTS: the adress of the queue
	
RETURN VALUE: 1 uf true 0 if false
	
	
complexity: O(1)
***********************************************************************************************************/
int PriorityQueueHeapIsEmpty(const pq_heap_t *queue); 



/*************************************************************************************************************************
DESCRIPTION: clears all the elements in the list and leanes a empty list
	
ARGUMENTS: the adress of the queue
	
RETURN VALUE: non
	
	
complexity: O(n)
***********************************************************************************************************/
void PriorityQueueHeapClear(pq_heap_t *queue);


/*************************************************************************************************************************
DESCRIPTION: erases a element that is found in comparison with the compare function
	
ARGUMENTS: the adress of the queue
	- the compare function
	- a data parameter for the function
RETURN VALUE: the data of the erased element
	
	
complexity: O(n)
***********************************************************************************************************/

void *PriorityQueueHeapErase(pq_heap_t *queue, int (*match_func)(const void *data, const void *param), const void *param);




/*************************************************************************************************************************
DESCRIPTION: gives the user the data stored in the first element
	
ARGUMENTS: the adress of the queue
	
RETURN VALUE: the adress of the data stored in the first element
	
	
complexity: O(1)
***************************************************************************************************************************/
void *PriorityQueueHeapPeek(const pq_heap_t *queue);

void PriorityQueueHeapPrint(pq_heap_t *heap);





#endif /*PRIORITY_QUEUE_H*/







