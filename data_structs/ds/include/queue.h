/**************************************************************************

	dev : Gilad Kahn
	rev: Yaniv Sne + Alon Levy
	status: approved
	date: 11.1.22
*******************************************************************/	



#ifndef ILRD_QUEUE_H
#define ILRD_QUEUE_H

#include <stddef.h> /*size_t*/

typedef struct queue queue_t;



/*
	creates a Queue
	recives nothing
	retruns pointer to created Queue
	complexity O(1)
*/
queue_t *QueueCreate();


/*
	free a Queue
	recives pointer to queue
	retruns void
	complexity O(N)
*/
void QueueDestroy(queue_t *queue);


/*
	tells if a queue is empty
	recives pointer to queue
	retruns empty 0; not empty 1
	complexity O(1)
*/	
int QueueIsEmpty(const queue_t *queue);


/*
	push an element to end of queue
	recives pointer to queue and pointer to data
	retruns pointer to the queue
	complexity O(N)
*/
	
int QueueEnqueue(queue_t *queue, void *data);

/*
	poop an elelment out of the end of queue
	recives pointer to queue and pointer to data
	retruns void
	complexity O(1)
*/	
void QueueDequeue(queue_t *queue);

/*
	tells number of elements in queue
	recives pointer to queue
	retruns number of elements in queue
	complexity O(N)
*/	
size_t QueueSize(const queue_t *queue);

/*
	shows first elemet of Queue
	recives pointer to queue
	retruns pointer to data
	complexity O(1)
*/
void *QueuePeek(const queue_t *queue);

/*
	conects two queues
	recives pointer to queue and added queue
	retruns pointer to queue
	complexity O(N)
*/
queue_t *QueueAppend(queue_t *dest, queue_t *src);


#endif /* ILRD_QUEUE_H*/

