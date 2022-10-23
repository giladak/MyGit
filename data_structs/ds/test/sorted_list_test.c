/**************************************************************************

	dev : Gilad Kahn
	rev: Vitali
	status: approved
	date: 18.1.22
*****************************************************************************/	


#include <stdio.h>  /*printf*/
#include <stdlib.h> /*size_t*/
#include <stddef.h> /*NULL*/
#include <string.h> /*memcmp*/

#include "doubly_linked_list.h"
#include "sorted_list.h"



static void SortedLinkedListPrint(sorted_list_t *list);

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


void SortedListTests (void)
{
	sorted_list_t *test = NULL;
	sorted_list_t *test2 = NULL;
	
	int param = 10;
	
	int a = 1;
	int b = 2;
	int b_copy = 2;
	int c = 3;
	int c_copy = 3;
	int e = 10;
	int f = 15;
	
	
	sorted_list_iterator_t first_node;
	sorted_list_iterator_t second_node;
	sorted_list_iterator_t third_node;
	sorted_list_iterator_t seventh_node;
	sorted_list_iterator_t find_node;
	 	
	printf ("Sorted linked list Tests: \n");

/**************check if create worked****************/

	test = SortedLinkedListCreate(Compare);
	
	if (1  != SortedLinkedListIsEmpty(test))
	{
		printf ("error in Create test 1 \n");
	}
	
	if (0  != SortedLinkedListSize(test))
	{
		printf ("error in Create test 2 \n");
	}


	if (1 != SortedLinkedListSameIter(SortedLinkedListEnd(test), (SortedLinkedListBegin(test))))
	{
		printf ("error in Create test 3 \n");
	}

	
	if (0 != SortedLinkedListSameIter(SortedLinkedListPrev(SortedLinkedListEnd(test)),  SortedLinkedListBegin(test)))
	{
		printf ("error in Create test 4 \n");
	}
	
	
	
	/********check if Insert and remove worked********/
	
	second_node = SortedLinkedListInsert(test, &b);
	first_node = SortedLinkedListInsert(test, &a);
	third_node = SortedLinkedListInsert(test, &c);
	
	if (1 != SortedLinkedListSameIter(SortedLinkedListBegin(test), first_node))
	{
		printf ("error in Insert test 1 \n");	
		printf ("%d \n", *(int*)SortedLinkedListGetData(first_node));
		printf ("%d \n", *(int*)SortedLinkedListGetData(SortedLinkedListBegin(test)));
	}
	
	if (1 != SortedLinkedListSameIter(SortedLinkedListNext(SortedLinkedListBegin(test)), second_node))
	{
		printf ("error in Insert test 2 \n");
			
	}
	
	if (1 != SortedLinkedListSameIter(SortedLinkedListPrev(third_node), second_node))
	{
		printf ("error in Insert test 3 \n");	
		
		printf ("%d \n", *(int*)SortedLinkedListGetData(second_node));
		printf ("%d \n", *(int*)SortedLinkedListGetData(SortedLinkedListPrev(second_node)));
		
	}
	
	if (*(int*)SortedLinkedListGetData(third_node) != c)
	{
		printf ("error in Insert test 4 \n");	
	}
	
	
	SortedLinkedListRemove(second_node);
	
		if (1 != SortedLinkedListSameIter(SortedLinkedListPrev(third_node), first_node))
	{
		printf ("error in remove test 1 \n");	
	}
	
	/**************check if pop worked*************/
	
	if (a != *(int*)SortedLinkedListPopFront(test))
	{
		printf ("error in popfront test 1 \n");	
	}
	
	if (c != *(int*)SortedLinkedListPopBack(test))
	{
		printf ("error in popback test 1 \n");	
	}
	
	if (1  != SortedLinkedListIsEmpty(test))
	{
		printf ("error in pop test 2 \n");
	}
	
	/**************check if for each worked*************/
	
	third_node = SortedLinkedListInsert(test, &c);
	second_node = SortedLinkedListInsert(test, &b);
	first_node = SortedLinkedListInsert(test, &a);
	
	SortedLinkedListForEach(first_node, SortedLinkedListEnd(test), Add, &param);
	
	if (*(int*)SortedLinkedListGetData(third_node) != c_copy + param)
	{
		printf ("error in For Each test 1 \n");
		printf ("%d \n", *(int*)SortedLinkedListGetData(third_node));
		printf ("%d \n", c_copy + param);
			
	}
	
	if (*(int*)SortedLinkedListGetData(second_node) != b_copy + param)
	{
		printf ("error in For Each test 2 \n");
		printf ("%d \n", *(int*)SortedLinkedListGetData(second_node));
		printf ("%d \n", b_copy + param);	
	}
	
	/**************check if find if worked*************/
	
	
	find_node = SortedLinkedListFindIf(first_node, third_node, IsNum, &b);
	
	if (1 != SortedLinkedListSameIter(second_node ,find_node))
	{
		printf ("error in find test 1 \n");
		printf ("%d \n", *(int*)SortedLinkedListGetData(second_node));
		printf ("%d \n", *(int*)SortedLinkedListGetData(find_node));
				printf ("%d \n", b);	
	}
	
	
	/******************check if find worked****************/
	
	/******************check if merge worked******************/
	
	test2 = SortedLinkedListCreate(Compare);
	
	SortedLinkedListInsert(test2, &e);
	seventh_node = SortedLinkedListInsert(test2, &a);
	SortedLinkedListInsert(test2, &f);
	
	/*printf ("test: \n");
	SortedLinkedListPrint(test);
	printf ("test2: \n");
	SortedLinkedListPrint(test2);*/
	
	SortedLinkedListMerge(test, test2);
	
	if (6  != SortedLinkedListSize(test))
	{
		printf ("error in merge test 1 \n");
		printf ("%ld \n" ,SortedLinkedListSize(test));
		printf ("%ld \n" ,SortedLinkedListSize(test2));
	}
	
	if (1 != SortedLinkedListSameIter(SortedLinkedListNext(first_node) ,seventh_node))
	{
		printf ("error in merge test 2 \n");
		SortedLinkedListPrint(test);
	}


	
	/**************Destroy and free memory ****************/
	
	SortedLinkedListDestroy(test2);
	SortedLinkedListDestroy(test);
}





int main()
{
	SortedListTests();	
		
	
	return(0);
}




static void SortedLinkedListPrint(sorted_list_t *list)
{
	sorted_list_iterator_t runner = SortedLinkedListBegin (list);
	sorted_list_iterator_t end = SortedLinkedListEnd(list);
	
	while (1 != SortedLinkedListSameIter(runner,end))
	{
		printf (" %d \n", *(int*)SortedLinkedListGetData(runner));
		
		runner = SortedLinkedListNext(runner);
	}
		
}


