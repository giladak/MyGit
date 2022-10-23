/**************************************************************************

	dev : Gilad Kahn
	rev: Vitali
	status: approved
	date: 18.1.22
*******************************************************************/	


#include <stdio.h>  /*size_t, for, while*/
#include <stdlib.h> /*malloc, free*/
#include <assert.h> /*assert*/

#include "sorted_list.h"
#include "p_queue.h"


priority_queue_t *PriorityQueueCreate(int(*cmp)(const void* data1, const void* data2))
{
	priority_queue_t *new_queue = NULL;
	
	assert (cmp);
	
	new_queue = (priority_queue_t *)malloc(sizeof(priority_queue_t));
	
	if (NULL == new_queue)
	{
		return(NULL);
	}
	
	 
	new_queue -> list = SortedLinkedListCreate(cmp);
	
	if (NULL == new_queue -> list)
	{	
		free (new_queue);
		return(NULL);
	}
	
	new_queue -> cmp = cmp;
	
	return (new_queue);
}


void PriorityQueueDestroy(priority_queue_t *queue)
{
	assert(queue);
	
	SortedLinkedListDestroy(queue -> list);
	
	queue -> list = NULL;
	
	free (queue);
}

size_t PriorityQueueSize(const priority_queue_t *queue)
{
	assert(queue);
	
	return (SortedLinkedListSize(queue -> list));
}

int PriorityQueueIsEmpty(const priority_queue_t *queue)
{
	assert(queue);
	
	return (SortedLinkedListIsEmpty(queue -> list));
}


int PriorityQueueEnqueue(priority_queue_t *queue, void *data)
{
	sorted_list_iterator_t new_node;
	
	new_node = SortedLinkedListInsert(queue -> list, data);

	if(new_node.doubly_iter == SortedLinkedListEnd(queue -> list).doubly_iter)
	{
		return(1);
	}

	return (0);
}

/************************Dequeue*********************/

void *PriorityQueueDequeue(priority_queue_t *queue)
{
	void *data = NULL;
	
	data = SortedLinkedListPopFront(queue -> list);

	return(data);
}

void *PriorityQueuePeek(const priority_queue_t *queue)
{
	void *data = NULL;
	
	assert (queue);
	
	data = SortedLinkedListGetData(SortedLinkedListBegin(queue -> list));
	
	return(data);
}



void PriorityQueueClear(priority_queue_t *queue)
{
	assert (queue);
	
	while (1 != PriorityQueueIsEmpty(queue))
	{
		PriorityQueueDequeue(queue);
	}
}


void *PriorityQueueErase(priority_queue_t *queue, int (*match_func)(const void *data, const void *param), const void *param)
{
	void *data = NULL;
	sorted_list_iterator_t for_remove;
	
	assert(match_func);
	assert(queue);
	
	for_remove = SortedLinkedListFindIf(SortedLinkedListBegin(queue -> list), SortedLinkedListEnd(queue -> list), match_func,param);
	
	if (SortedLinkedListEnd(queue -> list).doubly_iter == for_remove.doubly_iter)
	{
		return(NULL);
	}
	
	data = SortedLinkedListGetData(for_remove);
	
	SortedLinkedListRemove(for_remove);
	
	return(data);
}




