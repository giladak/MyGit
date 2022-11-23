


#include <stdio.h>  /*printf*/
#include <stdlib.h> /*size_t*/
#include <stddef.h> /*NULL*/
#include <string.h> /*memcmp*/

#include "sorted_list.h"
#include "p_queue.h"

static void PriorityQueuePrint(priority_queue_t *list);
int IsNum(const void *a, const void *num)
{
	if (*(int*)num == *(int*)a)
	{
		return (0);	
	}

	return (1);
}

int Add(void *a, void *b)
{	
	*(int*)a += *(int*)b;
	
	return (0);
} 


int Compare(const void *data1, const void *data2)
{	
	 int answer = *(int*)data2 - *(int*)data1;
	
	if (answer < 0)
	{
		return (-1);
	}
	
	if (answer > 0)
	{
		return (1);
	}
	
	return (0);
}




/*
	if (  != )
	{
		printf ("error in test 1 \n");
	}
	
	if (  != )
	{
		printf ("error in test 2 \n");
	}
	
	if (  != )
	{
		printf ("error in test 3 \n");
	}   
*/


void PriorityQueueTests (void)
{
	priority_queue_t *test = NULL;
	
	int a = 1;
	int b = 2;
	int c = 3;
	
	char A = 'A';
	 	
	printf ("Priority Queue Tests: \n");

/**************check if create worked****************/

	test = PriorityQueueCreate(Compare);
	
	if (1  != PriorityQueueIsEmpty(test))
	{
		printf ("error in Create test 1 \n");
	}
	
	if (0  != PriorityQueueSize(test))
	{
		printf ("error in Create test 2 \n");
	}


	/**************check if Enqueue and Dequeue worked*************/
	
	PriorityQueueEnqueue(test, &b);
	PriorityQueueEnqueue(test, &A);
	PriorityQueueEnqueue(test, &a);
	PriorityQueueEnqueue(test, &c);

	PriorityQueuePrint(test);


	if (4  != PriorityQueueSize(test))
	{
		printf ("error in Enqueue test 1 \n");
	}
	
	if (a  != *(int*)PriorityQueueDequeue(test))
	{
		printf ("error in Enqueue test 2 \n");
	}
	
	if (b  != *(int*)PriorityQueueDequeue(test))
	{
		printf ("error in Enqueue test 3 \n");
	}   
	
	if (c  != *(int*)PriorityQueuePeek(test))
	{
		printf ("error in Enqueue test 4 \n");
	}   
	
	/**************check if clear worked*************/
	
	PriorityQueueClear(test);
	
	if (0  != PriorityQueueSize(test))
	{
		printf ("error in Clear test 2 \n");
	}

	
	/**************Erase ****************/
	
	PriorityQueueEnqueue(test, &b);
	PriorityQueueEnqueue(test, &A);
	PriorityQueueEnqueue(test, &a);
	PriorityQueueEnqueue(test, &c);
	
	PriorityQueueErase(test, IsNum, &a);



	if (3  != PriorityQueueSize(test))
	{
		printf ("error in Erase test 1 \n");
	}
	
	PriorityQueueDequeue(test);
	
	if (c  != *(int*)PriorityQueueDequeue(test))
	{
		printf ("error in Erase test 2 \n");
	}   
	
	
	/**************Destroy and free memory ****************/
	
	
	PriorityQueueDestroy(test);
}





int main()
{
	PriorityQueueTests();	
		
	
	return(0);
}




static void PriorityQueuePrint(priority_queue_t *list)
{
	sorted_list_iterator_t runner = SortedLinkedListBegin (list -> list);
	sorted_list_iterator_t end = SortedLinkedListEnd(list -> list);
	
	while (1 != SortedLinkedListSameIter(runner,end))
	{
		printf ("%d \n", *(int*)SortedLinkedListGetData(runner));
		
		runner = SortedLinkedListNext(runner);
	}
		
}



