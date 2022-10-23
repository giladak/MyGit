/**************************************************************************

	dev : Gilad Kahn
	rev: Vitali + Sara
	status: approved
	date: 16.1.22
*******************************************************************/	


#include <stdio.h>  /*printf*/
#include <stdlib.h> /*size_t*/
#include <assert.h> /*assert*/

#include "doubly_linked_list.h"


typedef struct doubly_linked_list_node dll_node_t;


struct doubly_linked_list_node  /* dll == doubly linked lised */
{
    void *data;
    struct doubly_linked_list_node *next;
    struct doubly_linked_list_node *prev;
};                                                      

struct doubly_linked_list /*the head and tail are not pointers. this way we downt need to to malloc and free*/
{
    dll_node_t head;
    dll_node_t tail;
};





dll_t *DoublyLinkedListCreate()
{
	dll_t *list = (dll_t*)malloc(sizeof(dll_t));
	
	if (NULL == list)
	{
			return (NULL);
	}
	
	list -> head.data = NULL;
	list -> head.next = &list -> tail;
	list -> tail.prev = &list -> head;
	list -> tail.next = NULL;
	list -> tail.data = NULL;
	
	return (list);
}

/**********************destroy*****************/

void DoublyLinkedListDestroy(dll_t *list)
{
	dll_node_t *runner = list -> head.next;
	dll_node_t *next = runner;
	
	assert (list);
	
	while (NULL != runner -> next)
	{
		next = runner -> next;
		
		free (runner);
		
		runner = next;
	}
	
	runner = NULL;
	next = NULL;
	
	free (list);
}


/**********************IS EMPTY*****************/

int DoublyLinkedListIsEmpty(const dll_t *list)
{
	assert (list);
	
	return(list -> head.next == &list -> tail);
}



dll_iterator_t DoublyLinkedListBegin(const dll_t *list)
{
	assert (list);

	return (list -> head.next);
}



size_t DoublyLinkedListSize(const dll_t *list)
{
	size_t count = 0;
	dll_node_t *runner = list -> head.next;
	
	assert (list);
	
	while (DoublyLinkedListEnd(list) != runner)
	{
		runner = runner -> next;
		++count;
	}
		
	return (count);
	
}



dll_iterator_t DoublyLinkedListEnd(const dll_t *list)
{
	assert (list);
	
	return ((dll_iterator_t)&(list -> tail));	
} 




dll_iterator_t DoublyLinkedListNext(const dll_iterator_t iterator)
{
	assert (iterator);
	
	return (iterator -> next);
}



dll_iterator_t DoublyLinkedListPrev(const dll_iterator_t iterator)
{
	assert (iterator);
	
	return (iterator -> prev);
}




int DoublyLinkedListSameIter(const dll_iterator_t iterator1,const dll_iterator_t iterator2)
{
	assert (iterator1);
	assert (iterator2);
	
	return (iterator1 == iterator2);
}


dll_iterator_t DoublyLinkedListInsertBefore(const dll_iterator_t iterator, void *data)
{

	dll_iterator_t new_node = (dll_iterator_t)malloc(sizeof(dll_node_t));
	
	if (NULL == new_node)
	{
		return (NULL);
	}
	
	new_node -> data = data;
	
	new_node -> next = iterator;
	new_node -> prev = iterator -> prev;
	
	iterator -> prev -> next = new_node;
	iterator -> prev = new_node;
	
	return (new_node);
}



dll_iterator_t DoublyLinkedListRemove(dll_iterator_t iterator)
{
	dll_iterator_t temp = iterator -> next;
	
	assert (iterator);	
	
	iterator -> prev -> next = iterator -> next;
	iterator -> next -> prev = iterator -> prev;
	
	free (iterator);
	
	iterator = NULL;
	
	return (temp);
}

dll_iterator_t DoublyLinkedListPushFront(dll_t *list, void *data)
{	
	dll_iterator_t new_iterator = NULL;
	
	assert(list);
	assert(data);
	
	new_iterator = DoublyLinkedListInsertBefore(DoublyLinkedListBegin(list), data);
	
	return (new_iterator);
}


dll_iterator_t DoublyLinkedListPushBack(dll_t *list, void *data)
{
	dll_iterator_t new_iterator = NULL;
	
	assert(list);
	
	new_iterator = DoublyLinkedListInsertBefore(DoublyLinkedListEnd(list), data);
	
	return (new_iterator);
}


void *DoublyLinkedListGetData(const dll_iterator_t iterator)
{
	assert (iterator);	
	
	return (iterator -> data);
}


void *DoublyLinkedListPopBack(dll_t *list)
{
	void *temp = DoublyLinkedListGetData(DoublyLinkedListEnd(list) -> prev);
	
	assert (list);

	DoublyLinkedListRemove(DoublyLinkedListEnd(list) -> prev);
	
	return (temp);
}


void *DoublyLinkedListPopFront(dll_t *list)
{
	void *temp = DoublyLinkedListGetData(DoublyLinkedListBegin(list));
	
	assert (list);

	DoublyLinkedListRemove(DoublyLinkedListBegin(list));
	
	return (temp);
}


int DoublyLinkedListForEach(dll_iterator_t from, dll_iterator_t to, int (*action_func)(void *data, void *param), void *param)
{
	dll_iterator_t runner = from;
	int is_sucsess = 0;
	
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != action_func);
	assert(NULL != param);
	
	while(runner != to)
	{
		is_sucsess = (*action_func)(runner -> data, param);
		runner = runner -> next;
		
		if (is_sucsess == 1)
		{
			return (1);
		}
	}
	
	return (is_sucsess);
}


dll_iterator_t DoublyLinkedListFind(dll_iterator_t from, dll_iterator_t to, int (*match_func)(const void *data, const void *param),const void *param)
{
	dll_iterator_t runner = from;
	int is_found = 0;

	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != match_func);
	assert(NULL != param);
	
	while(runner != to)
	{
		is_found = (*match_func)(runner -> data, param);
		
		if (0 == is_found)
		{
			return (runner); 
		}
		
		runner = runner -> next;
	}
	
	return (to);
}

int DoublyLinkedListMultiFind(dll_iterator_t from, dll_iterator_t to, int (*match_func)(const void *data,const void *param) ,const void *param, dll_t *out_list)
{
	dll_node_t* store_value = NULL;
	dll_node_t* runner = NULL;
	
	assert(NULL != from);
	assert(NULL != match_func);
	assert(NULL != out_list);
	
	while (runner != to)
	{
		runner = DoublyLinkedListFind(from, to, match_func,param);
		
		if (runner != to)
		{
			store_value = DoublyLinkedListPushBack(out_list, runner -> data);
			from = runner -> next;
		}
	
		if (store_value == NULL)
		{
			return (0);
		}
	} 
	
	return (DoublyLinkedListIsEmpty(out_list));
}



dll_iterator_t DoublyLinkedListSplice(dll_iterator_t where, dll_iterator_t from, dll_iterator_t to)
{	
	dll_iterator_t before_from = from -> prev;

	assert(from);
	assert(to);
	assert(where);

	where -> prev -> next = from;   
	from -> prev -> next = to;
	from -> prev = where -> prev; 
	
	to -> prev -> next = where;
	where -> prev = to -> prev;   
	to -> prev = before_from;
	
	
	return (where -> prev);
}









