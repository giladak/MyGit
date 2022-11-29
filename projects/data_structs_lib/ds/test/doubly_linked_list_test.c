
#include <stdio.h>  /*printf*/
#include <stdlib.h> /*size_t*/
#include <stddef.h> /*NULL*/
#include "doubly_linked_list.h"





int IsNum(const void *a, const void *num)
{

	return (*(int*)num == *(int*)a);
}

int Add(void *a, void *b)
{	
	*(int*)a += *(int*)b;
	
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




void DllTests(void)
{
	dll_t *test = NULL;
	dll_t *test2 = NULL;
	
	int param = 10;
	
	int a = 1;
	int a_copy = 1;
	int b = 2;
	int c = 3;
	int d = 5;
	int d_copy = 5;
	int e = 10;
	int f = 15;
	
	char A = 'A';
	
	dll_iterator_t first_node = NULL;
	dll_iterator_t second_node = NULL;
	dll_iterator_t third_node = NULL;
	dll_iterator_t fourth_node = NULL;
	dll_iterator_t fifth_node = NULL;
	dll_iterator_t seventh_node = NULL;
	 	
	printf ("DllTests Tests: \n");

	/*******check if created *********/
	
	test = DoublyLinkedListCreate();


	if (1 != DoublyLinkedListIsEmpty(test))
	{
		printf ("error in create test 1 \n");
	}
	
	if (0  != DoublyLinkedListSize(test))
	{
		printf ("error in create test 2 \n");
	}
	
	/*******check if begin, end next and prev work propely *******/
	
	if (1 != DoublyLinkedListSameIter(DoublyLinkedListBegin(test),DoublyLinkedListEnd(test)))
	{
		printf ("error in begin test 1 \n");
	}   
	
	if (DoublyLinkedListNext(DoublyLinkedListBegin(test)) == DoublyLinkedListEnd(test))
	{
		printf ("error in begin test 2\n");
	}   
	
	
	if (DoublyLinkedListBegin(test) == DoublyLinkedListPrev(DoublyLinkedListEnd(test)))
	{
		printf ("error in begin test 3 \n");
	}  	
	
	/*******check if inserts and remove work propely *******/
	
	first_node = DoublyLinkedListInsertBefore(DoublyLinkedListEnd(test), &a);
	second_node = DoublyLinkedListInsertBefore(DoublyLinkedListEnd(test), &b);
	third_node = DoublyLinkedListInsertBefore(DoublyLinkedListEnd(test), &c);
	fourth_node = DoublyLinkedListInsertBefore(DoublyLinkedListEnd(test), &d);
	
	
	if (a != *(int *)DoublyLinkedListGetData(first_node))
	{
		printf ("error in Insert test 1 \n");
	}
	
	if (b != *(int *)DoublyLinkedListGetData(second_node))
	{
		printf ("error in Insert test 2 \n");
	}
	
	
	DoublyLinkedListRemove(third_node);
	
	if (DoublyLinkedListNext(second_node) != fourth_node)
	{
	 		printf ("error in remove test 1 \n");
	 		printf ("second = %d \n ", *(int *)DoublyLinkedListGetData(second_node));
	 		printf ("fourth = %d \n ", *(int *)DoublyLinkedListGetData(fourth_node));
	 		
	}
	
	if (3  != DoublyLinkedListSize(test))
	{
		printf ("error in remove test 2 \n");
	} 
	
	
	
	/*******check if push back and front work propely *******/	
	
	DoublyLinkedListPopBack(test);
	DoublyLinkedListPopFront(test);
	
	if (1  != DoublyLinkedListSize(test))
	{
		printf ("error in pop test 1 \n");
	} 
	
	
	first_node = DoublyLinkedListPushFront(test, &a);
	fourth_node = DoublyLinkedListPushBack(test, &d);
	
	
	if (DoublyLinkedListBegin(test) != first_node)
	{
		printf ("error in Push test 1 \n");
	}
	
	if (3  != DoublyLinkedListSize(test))
	{
		printf ("error in Push test 2 \n");
	}
	
	
	/*******check if for each works propely *******/
	
	DoublyLinkedListForEach(DoublyLinkedListBegin(test), DoublyLinkedListEnd(test), Add, &param);
	
	if ((a_copy + param) != *(int *)DoublyLinkedListGetData(first_node))
	{
		printf ("error in for each test 1 \n");
	}
	
	if ((d_copy + param) != *(int *)DoublyLinkedListGetData(fourth_node))
	{
		printf ("error in for each test 2 \n");
	}
	
	/*******************check if find works propely *******************************/
	
	
	if (first_node  != DoublyLinkedListFind(DoublyLinkedListBegin(test), DoublyLinkedListEnd(test), IsNum, &a))
	{
		printf ("error in Find test 1 \n");
		printf ("%d \n",*(int *)DoublyLinkedListGetData(first_node));
			printf ("%d \n",*(int *)DoublyLinkedListGetData(DoublyLinkedListFind(DoublyLinkedListBegin(test), DoublyLinkedListEnd(test), IsNum, &a)));
					printf ("a = %d \n",a);
		
	}
	
		if (second_node  != DoublyLinkedListFind(DoublyLinkedListBegin(test), DoublyLinkedListEnd(test), IsNum, &b))
	{
		printf ("error in Find test 2 \n");
					
					
	}
	
	/*******check if multi_find data works propely *******/
	
	DoublyLinkedListPushBack(test, &a);
	
	test2 = DoublyLinkedListCreate();
	
	
	
	DoublyLinkedListMultiFind(DoublyLinkedListBegin(test), DoublyLinkedListEnd(test), IsNum, &a, test2);	
	
		
	if (2  != DoublyLinkedListSize(test2))
	{
		printf ("error in Multi Find test 1 \n");
		printf ("%ld \n", DoublyLinkedListSize(test2));
	}

	
	/*******check if splice works propely *******/
	fifth_node = DoublyLinkedListPushBack(test2, &e);
	DoublyLinkedListPushBack(test2, &f);
	seventh_node = DoublyLinkedListPushBack(test2, &A);
	
	
	DoublyLinkedListSplice(fourth_node, fifth_node, seventh_node);
	
	if (6  != DoublyLinkedListSize(test))
	{
		printf ("error in Splice test 1 \n");
		
		printf ("size = %ld \n", DoublyLinkedListSize(test));
	}

	
	/*******check if destroyed propely ******/


	DoublyLinkedListDestroy(test);
	DoublyLinkedListDestroy(test2);
}


int main()
{
	 DllTests();
	
	return (0);
}





