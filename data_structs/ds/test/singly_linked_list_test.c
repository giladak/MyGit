/**************************************************************************

	dev : Gilad Kahn
	rev: Daniel Gabay
	status: approved
	date: 10.1.22
*******************************************************************/

#include <stdio.h>  /*printf*/
#include <stdlib.h> /*size_t*/
#include "singly_linked_list.h"


struct singly_linked_list
{
	sll_iterator_t head;
	
};   

struct singly_linked_list_iterator
{
	void *data;
	struct  singly_linked_list_iterator *next_iterator;
};


int Add(void *a, void *b)
{	
	*(int*)a += *(int*)b;
	
	return (0);
} 

int IsNum(const void *a, void *num)
{
	if (*(int*)num == *(int*)a)
	{
		return (0);
	}

	return (1);
}





void TestSinglyLinkedList1 (void)
{
	sll_t *test = NULL;
	sll_iterator_t first_node = NULL;
	sll_iterator_t second_node = NULL;
	sll_iterator_t third_node = NULL;
	sll_iterator_t forth_node = NULL;
	
	sll_iterator_t next_node = NULL;
	sll_iterator_t test_node_copy = NULL;
	
	
	int five = 5;
	int seven = 7;
	int ten = 10;
	char A = 'A';
		
	printf ("linked list test function 1: \n");
	
	test = SinglyLinkedListCreate();
	
	if (NULL == (sll_iterator_t)(test -> head))
	{
		printf ("error in create function, test 1: \n");
	}
	
	if (0 != SinglyLinkedListIsEqual(SinglyLinkedListBegin(test), SinglyLinkedListEnd(test)))
	{
		printf ("error in End/Begin/IsEqual function, test 1: \n");
	}
	
	next_node = test -> head;
	
	first_node = SinglyLinkedlistInsert(next_node ,&five);
	next_node = first_node -> next_iterator;
	
	second_node = SinglyLinkedlistInsert(next_node ,&seven);
	next_node = second_node -> next_iterator;
	
	third_node = SinglyLinkedlistInsert(next_node ,&ten);
	next_node = third_node -> next_iterator;

	if (ten != *(int *)SinglyLinkedListGetData(third_node))
	{
		printf ("error in Insert / GetData function, test 1: \n");
	}

	SinglyLinkedListForEach(first_node, next_node, Add, &five); 
	
	
	if (ten /*15*/!= *(int *)SinglyLinkedListGetData(third_node))
	{
		printf ("error in ForEach function, test 1: \n");
		printf ("%d\n", *(int *)SinglyLinkedListGetData(third_node));
				printf ("%d\n",(ten+five));
	}
	
	
	SinglyLinkedListSetData(third_node, &ten);
	
	if (ten != *(int *)SinglyLinkedListGetData(third_node))
	{
		printf ("error in Insert / GetData function, test 2: \n");
	}


	if (3 != SinglyLinkedListCount(test))
	{
		printf ("error in Count function, test 1: \n");
	}
	

	test_node_copy = first_node;
	

	
	forth_node = SinglyLinkedlistInsert(next_node ,&A);
	
	if (A != *(char *)SinglyLinkedListGetData(forth_node))
	{
		printf ("error in Insert / GetData function, test 3: \n");
	}
	
	
	next_node = next_node -> next_iterator;
	
	test_node_copy = LinkedListFind(first_node, next_node, IsNum, &seven);
	
	if (0 != SinglyLinkedListIsEqual(second_node, test_node_copy))
	{
		printf ("error in Find/IsEqual function, test 1: \n");
	}
	

	if (4 != SinglyLinkedListCount(test))
	{
		printf ("error in Count function, test 2: \n");
	}
	
	
	SinglyLinkedListRemove(third_node);
	if (3 != SinglyLinkedListCount(test))
	{
		printf ("error in Count function, test 3: \n");
	}
	
	if (0 != SinglyLinkedListIsEqual (third_node, SinglyLinkedListNext(second_node)))
	{
		printf ("error in remove function and Next, test 2: \n");
		printf("%d\n", *(int*)SinglyLinkedListGetData(second_node));
		printf("%d\n", *(int*)SinglyLinkedListGetData(SinglyLinkedListNext(second_node)));
		printf("%c\n", *(char*)SinglyLinkedListGetData(third_node));
	}

	
	SinglyLinkedListDestroy(test);	
}








int main()
{
	TestSinglyLinkedList1();
	
	
	return (0);	
}

/*


	while(test_node_copy -> next_iterator != NULL)
	{
		printf ("data = %d \n", *(int*)(test_node_copy -> data));
		 	
		test_node_copy = test_node_copy -> next_iterator;
	}
	*/


