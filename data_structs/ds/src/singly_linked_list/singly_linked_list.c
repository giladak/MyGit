

#include <stdio.h>  /*printf*/
#include <stdlib.h> /*size_t*/
#include <assert.h> /*assert*/
#include "singly_linked_list.h"

#define UNUSED(x) (void)(x)

struct singly_linked_list
{
	sll_iterator_t head;
	
};   

struct singly_linked_list_iterator
{
	void *data;
	struct  singly_linked_list_iterator *next_iterator;
};




sll_t *SinglyLinkedListCreate()
{
	sll_t *list = (sll_t*)malloc(sizeof(sll_t));
	sll_iterator_t dummy_node = NULL;
	
	if (NULL == list)
	{
			return (NULL);
	}
	
	
	dummy_node = (sll_iterator_t)malloc(sizeof(struct singly_linked_list_iterator));
	
	if (NULL == dummy_node)
	{	
		free (list);
		return (NULL);
	}	
		
	list -> head = dummy_node;
	dummy_node -> data = NULL;
	dummy_node -> next_iterator = NULL;
	
	return (list);
}



int SinglyLinkedListIsEqual(const sll_iterator_t iterator1, const sll_iterator_t iterator2)
{	
	assert(NULL != iterator1);
	assert(NULL != iterator2);
		
	
	if (iterator1 == iterator2)
	{
		return(0);
	}
	
	return(1);
}


sll_iterator_t SinglyLinkedListBegin(const sll_t *list)
{
	assert (NULL != list);		
		
	return (list -> head);	
}


sll_iterator_t SinglyLinkedListEnd(const sll_t *list)
{
	sll_iterator_t cur_iterator = list -> head;
	
	assert(list);	
	
	while(NULL != cur_iterator -> next_iterator)
	{
		cur_iterator = cur_iterator -> next_iterator;
	}
	
	return (cur_iterator);
}


sll_iterator_t LinkedListFind(sll_iterator_t from, sll_iterator_t to, int(*match_func)(const void *data, void *param), void *param) 
{	
	sll_iterator_t runner = from;
	int is_found = 1;

	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != match_func);
	assert(NULL != param);
	
	while(runner != to)
	{
		is_found = (*match_func)(runner -> data, param);
		if(0 == is_found)
		{
			return (runner);
		}
		 
		runner = runner -> next_iterator;
	}
	
	return (to);
}


void SinglyLinkedListDestroy(sll_t *list)
{
	
	sll_iterator_t runner = list -> head;
	sll_iterator_t next = runner;
	
	assert (list);
	
	while (NULL != runner)
	{
		next = runner -> next_iterator;
		
		free (runner);
		
		runner = next;
		
	}
	
	runner = NULL;
	next = NULL;
	
	free (list);
}


int SinglyLinkedListForEach(sll_iterator_t from, sll_iterator_t to, int(*action_func)(void *data, void *param),void *param)		
{
	sll_iterator_t runner = from;
	int is_sucsess = 0;
	
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != action_func);
	assert(NULL != param);
	
	while(runner != to && 0 == is_sucsess)
	{
		is_sucsess = (*action_func)(runner -> data, param);
		runner = runner -> next_iterator;
	}
	
	return (is_sucsess);
} 



static int CountFunc (void *void_iterator, void *param)
{	
	UNUSED(void_iterator);
	
	assert(NULL != void_iterator);
	assert(NULL != param);
	
	++*(int*)param;
		
	return (0);
}



 
size_t SinglyLinkedListCount(const sll_t *list)
{
	size_t count = 0; 
	
	assert (list);
	
	SinglyLinkedListForEach(list -> head ,SinglyLinkedListEnd(list) ,CountFunc, &count);
	
	return(count);
}

void SinglyLinkedListRemove(sll_iterator_t iterator)
{	
	sll_iterator_t temp = iterator -> next_iterator;
	
	assert(NULL != iterator);
	
	iterator -> data = iterator -> next_iterator -> data;
	iterator -> next_iterator = iterator -> next_iterator -> next_iterator;
	
	free (temp);
}


sll_iterator_t SinglyLinkedlistInsert(sll_iterator_t iterator ,void *data)
{
	sll_iterator_t new_iterator = (sll_iterator_t)malloc(sizeof(struct singly_linked_list_iterator));
	new_iterator -> data = iterator -> data;
	new_iterator -> next_iterator = iterator -> next_iterator;
	
	assert(NULL != iterator);
	assert(NULL != data);
	
	if (NULL == new_iterator)
	{	
		return (SinglyLinkedListEnd((sll_t*)iterator));
	}

	iterator -> data = data;
	iterator -> next_iterator = new_iterator;
	
	return (iterator);
}

void SinglyLinkedListSetData(sll_iterator_t iterator, void *data)
{	
	assert (NULL != iterator && NULL != data);
	
	iterator -> data = data;
}


void *SinglyLinkedListGetData(const sll_iterator_t iterator)
{
	assert (NULL != iterator);

	return (iterator -> data);
}


sll_iterator_t SinglyLinkedListNext(const sll_iterator_t iterator)
{
	assert (NULL != iterator);
	
	return (iterator -> next_iterator);
}

sll_t *SinglyLinkedListAppend(sll_t *dest, sll_t *src)
{
	sll_iterator_t connection = SinglyLinkedListBegin(dest);
	sll_iterator_t temp =  SinglyLinkedListEnd(dest);
	
	assert (src);
	assert (dest);
	
	while (NULL != connection -> next_iterator -> next_iterator)
	{
		connection = connection -> next_iterator;
	}
	
	connection -> next_iterator = src -> head;
	
	src -> head = temp;
	
	return (dest);
}


/*
int CountFunc2 (void *void_iterator, void *param)
{	
	size_t count = 0;
	sll_iterator_t iterator = (sll_iterator_t) void_iterator;
	
	UNUSED(param);
	
	
	while (NULL != iterator -> next_iterator)
	{
		iterator = iterator -> next_iterator;
		++count;
	}
	
	return ((int)count);
}*/
