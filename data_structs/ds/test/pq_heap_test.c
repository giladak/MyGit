/**************************************************************************

	dev : 
	rev:
	status: 
	date: 
*****************************************************************************/	


#include <stdio.h>  /*printf*/
#include <stdlib.h> /*size_t*/
#include <stddef.h> /*NULL*/
#include <string.h> /*memcmp*/

#include "heap.h"
#include "pq_heap.h"




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


void PriorityQueueHeapTests (void)
{
	pq_heap_t *test = NULL;
	
	int a = 1;
	int b = 2;
	int c = 3;
	int A = 10;
	 	
	printf ("Priority Queue Tests: \n");

/**************check if create worked****************/

	test = PriorityQueueHeapCreate(Compare);
	
	if (1  != PriorityQueueHeapIsEmpty(test))
	{
		printf ("error in Create test 1 \n");
	}
	
	if (0  != PriorityQueueHeapSize(test))
	{
		printf ("error in Create test 2 \n");
	}


	/**************check if Enqueue and Dequeue worked*************/
	
	PriorityQueueHeapEnqueue(test, &b);
	PriorityQueueHeapEnqueue(test, &a);
	PriorityQueueHeapEnqueue(test, &c);
	PriorityQueueHeapEnqueue(test, &A);

	PrintHeap(test->heap);
	
	if (4  != PriorityQueueHeapSize(test))
	{
		printf ("error in Enqueue test 1 \n");
	}
	

	if (a  != *(int*)PriorityQueueHeapDequeue(test))
	{
		printf ("error in Enqueue test 2 \n");
	}
	

	if (b  != *(int*)PriorityQueueHeapDequeue(test))
	{
		printf ("error in Enqueue test 3 \n");
	}  
	
	
	if (c  != *(int*)PriorityQueueHeapPeek(test))
	{
		printf ("error in Enqueue test 4 \n"); 
	}   
	
	/*************check if clear worked*************/
	
	PriorityQueueHeapClear(test);
	
	if (0  != PriorityQueueHeapSize(test))
	{
		printf ("error in Clear test 2 \n");
	}

	
	/**************Erase ****************/
	
	PriorityQueueHeapEnqueue(test, &b);
	PriorityQueueHeapEnqueue(test, &A);
	PriorityQueueHeapEnqueue(test, &a);
	PriorityQueueHeapEnqueue(test, &c);
	
	PriorityQueueHeapErase(test, IsNum, &a);


	if (3  != PriorityQueueHeapSize(test))
	{
		printf ("error in Erase test 1 \n");
	}
	
	PriorityQueueHeapDequeue(test);
	
	if (b  != *(int*)PriorityQueueHeapDequeue(test))
	{
		printf ("error in Erase test 2 \n");
	}   
	
	
	/**************Destroy and free memory ****************/
	
	
	PriorityQueueHeapDestroy(test);
}





int main()
{
	PriorityQueueHeapTests();	
		
	
	return(0);
}




