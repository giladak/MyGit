
#include <stdio.h>  /*printf*/
#include <stdlib.h> /*size_t*/
#include <assert.h> /*assert*/
#include "singly_linked_list.h"
#include "queue.h"
#include "utilities.h"

#define LIST_CREATE   SinglyLinkedListCreate
#define LIST_COUNT    SinglyLinkedListCount
#define LIST_IS_EQUAL SinglyLinkedListIsEqual
#define LIST_INSERT   SinglyLinkedlistInsert
#define LIST_END      SinglyLinkedListEnd
#define LIST_BEGIN    SinglyLinkedListBegin
#define LIST_REMOVE   SinglyLinkedListRemove
#define LIST_GET      SinglyLinkedListGetData
#define LIST_DESTROY  SinglyLinkedListDestroy
#define LIST_APPEND   SinglyLinkedListAppend




struct queue /*in c file*/
{
	sll_t *list;
};

struct singly_linked_list
{
	sll_iterator_t head;
};  
 
struct singly_linked_list_iterator
{
	void *data;
	struct  singly_linked_list_iterator *next_iterator;
};

/************************QueueCreate********************************************/	

queue_t *QueueCreate()
{	
	queue_t *new_queue = (queue_t *)malloc (sizeof(queue_t));
	
	if (NULL == new_queue)
	{
		return (NULL);
	}
	
	new_queue -> list = LIST_CREATE();
	
	if (NULL == new_queue -> list)
	{
		free (new_queue);
		return (NULL);
	}
	
	return (new_queue);
}

	/************************QueueDestroy********************************************/	

void QueueDestroy(queue_t *queue)
{	
	assert (NULL != queue);
	
	LIST_DESTROY(queue -> list);
	
	free (queue);
}
	
		/************************QueueIsEmpty********************************************/	
	
int QueueIsEmpty(const queue_t *queue)
{	
	assert (NULL != queue);
	
	return (LIST_IS_EQUAL(LIST_BEGIN(queue -> list), LIST_END(queue -> list)));
}

			/************************QueueEnqueue********************************************/	

int QueueEnqueue(queue_t *queue, void *data)
{
	sll_iterator_t temp = LIST_INSERT(LIST_END(queue -> list) ,data);
	
	assert (NULL != queue);
	assert (NULL != data);
	
	if (temp == LIST_END(queue -> list))
	{
		return (1); 
	}
	
	return (0);
}	
	
	/************************QueueDequeue********************************************/

void QueueDequeue(queue_t *queue)
{	
	assert(queue);
	assert(queue -> list);

	LIST_REMOVE(LIST_BEGIN(queue -> list));
}
	
		/************************QueueSize********************************************/
	
size_t QueueSize(const queue_t *queue)
{	
	assert(queue);
	assert(queue -> list);	
	
	return(LIST_COUNT(queue -> list));
}
	
			/************************QueuePeek********************************************/
	
void *QueuePeek(const queue_t *queue)
{
	assert(queue);
	assert(queue -> list);
	
	return(LIST_GET(LIST_BEGIN(queue -> list)));
}
	
				/************************QueueAppend********************************************/
	
queue_t *QueueAppend(queue_t *dest, queue_t *src)
{	
	assert (src);
	assert (dest);

	LIST_APPEND(dest -> list, src -> list);
	
	return (dest);
}



