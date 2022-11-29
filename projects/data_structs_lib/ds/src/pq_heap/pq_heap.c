/**************************************************************************

	dev : Gilad Kahn
	rev: Vitali
	status: approved
	date: 18.1.22
*******************************************************************/	


#include <stdio.h>  /*size_t, for, while*/
#include <stdlib.h> /*malloc, free*/
#include <assert.h> /*assert*/

#include "heap.h"
#include "pq_heap.h"

#define START_SIZE 10

pq_heap_t *PriorityQueueHeapCreate(int(*cmp)(const void* data1, const void* data2))
{
	pq_heap_t *new_queue = NULL;
	
	assert (cmp);
	
	new_queue = (pq_heap_t *)malloc(sizeof(pq_heap_t));
	
	if (NULL == new_queue)
	{
		return(NULL);
	}
	
	 
	new_queue -> heap = HeapCreate(cmp, START_SIZE);
	
	if (NULL == new_queue -> heap)
	{	
		free (new_queue);
		return(NULL);
	}
	
	new_queue -> cmp = cmp;
	
	return (new_queue);
}

void PriorityQueueHeapDestroy(pq_heap_t *queue)
{
	assert(queue);
	
	HeapDestroy(queue->heap);
	
	queue -> heap = NULL;
	
	free (queue);
}

size_t PriorityQueueHeapSize(const pq_heap_t *queue)
{
	assert(queue);
	
	return (HeapSize(queue->heap));
}

int PriorityQueueHeapIsEmpty(const pq_heap_t *queue)
{
	assert(queue);
	
	return (HeapIsEmpty(queue->heap));
}


int PriorityQueueHeapEnqueue(pq_heap_t *queue, void *data)
{
	assert(data);

	HeapPush(queue->heap, data);

	return (0);
}

/************************Dequeue*********************/

void *PriorityQueueHeapDequeue(pq_heap_t *queue)
{
	void *data = NULL;
	
	data = PriorityQueueHeapPeek(queue);
	
	HeapPop(queue->heap);

	return(data);
}

void *PriorityQueueHeapPeek(const pq_heap_t *queue)
{	
	assert (queue);
	
	return(HeapPeek(queue->heap));
}



void PriorityQueueHeapClear(pq_heap_t *queue)
{
	assert (queue);
	
	while (1 != PriorityQueueHeapIsEmpty(queue))
	{
		PriorityQueueHeapDequeue(queue);
	}
}


void *PriorityQueueHeapErase(pq_heap_t *queue, int (*match_func)(const void *data, const void *param), const void *param)
{
	void *data = NULL;
	
	assert(match_func);
	assert(queue);
	
	data = HeapRemove(queue->heap, match_func, param);

	if (NULL == data)
	{
		return(NULL);
	}

	return(data);
}
