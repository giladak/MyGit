	

#include <stdio.h>  /*printf*/
#include <stdlib.h> /*size_t*/
#include "queue.h"
#include "utilities.h"



void TestQueue(void)
{
	int a = 5;
	int b = 10;
	int c = 15;
	char A = 'A';
	char B = 'B';

	queue_t *test = NULL;
	queue_t *test2 = NULL;
/*
	queue_t *first = NULL;
	queue_t *second = NULL;
	queue_t *three = NULL;
	queue_t *fourth = NULL;
	queue_t *fifth = NULL;
*/	

	printf ("queue tests: \n");

	test = QueueCreate();
	
	if (NULL == test)
	{
		printf ("error in create test 1 \n");
	}

	if (EMPTY != QueueIsEmpty(test))
	{
		printf("error in is empty test 1 \n");
	}
	
	if(0 != QueueEnqueue(test, &a))
	{
		printf("error in Enqueue test 1 \n");
	}
	
	QueueEnqueue(test, &b);
	QueueEnqueue(test, &c);
	
	if (a != *(int*)QueuePeek(test))
	{
		printf("error in Enqueue / peek test 1 \n");
	}
	
	if (3 != QueueSize(test))
	{
		printf("error in size test 1 \n");
	}
	
	QueueDequeue(test);
	QueueDequeue(test);
	
	if (c != *(int*)QueuePeek(test))
	{
		printf("error in dequeue test 1 \n");
	}
	
	if (1 != QueueSize(test))
	{
		printf("error in size test 2 \n");
	}
	
	test2 = QueueCreate();
	
	QueueEnqueue(test2, &A);
	QueueEnqueue(test2, &B);
	QueueEnqueue(test2, &c);

	QueueAppend (test, test2);
	
	if (c != *(int*)QueuePeek(test))
	{
		printf("error in append test 1 \n");
	}
	
	if (4 != QueueSize(test))
	{
		printf("error in append test 2 \n");
		printf("%ld \n", QueueSize(test));
	}


	QueueDestroy(test);
	QueueDestroy(test2);
}








int main()
{
	TestQueue();
	
	return (0);	
}

/*


	while(test_node_copy -> next_iterator != NULL)
	{
		printf ("data = %d \n", *(int*)(test_node_copy -> data));
		 	
		test_node_copy = test_node_copy -> next_iterator;
	}
	*/


