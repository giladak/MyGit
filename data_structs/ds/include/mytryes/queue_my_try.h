#ifndef ILRD_QUEUE
#define ILRD_QUEUE

#include <stddef.h> /*size_t*/

typedef struct queue queue_t;

typedef struct q_node q_node_t;


struct queue
{
	q_node *head;
	q_node *tail;
}


struct q_node
{
	void *data;
	q_node next_node; 
}


/*creates a dummy nide and points it to NULL*/

queue *QueueCreate();

/*  Destroys a given queue.
	arguments: queue to be destroyed.
	no return value. */

void QueueDestroy(queue_t *queue);

/*  removes a element from the head. */
	
q_node *Dequeue (queue_t *queue);

/*  add a element to the tail of the queue. */
	
q_node *Enqueue (queue_t *queue, const void *element);

/*  checks weather the queue is empty */
	
int QueueIsEmpty(const queue_t *queue);


/*  shoecases the element in the head */
	
void *QueuePeek(const queue_t *queue);

/*  Returns the size of the orginal capacity of the stack .
	return used space. */
	
/*  add a element to the head of the queue. */
	
q_node *append (queue_t *dest, queue_t *src);
q_node *append (queue_t *front, queue_t *rear);
 
#endif /*ILRD_QUEUE*/


