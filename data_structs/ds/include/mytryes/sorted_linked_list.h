
#ifndef SORTED_LINKED_LIST_H
#define SORTED_LINKED_LIST_H


#include <stdlib.h> /*size_t*/
#include "doubly_linked_list.h"



typedef struct sorted_doubly_linked_list
{
	dll_t *sorted_list;
	int (*compare_func)(iterator a, node_t *b);
	
} sdll_list_t;


typedef struct sorted_doubly_linked_list_iterator
{
	dll_iterator_t sorted_iterator;
	
} sdll_iterator_t;

typedef (sdll_iterator_t*) sdll_node_t;



sdll_list_t *Create (int (*compare_func)(iterator a, node_t *b)); 

void *Destroy (sdll_list_t *list);



/*
	returns new inserted iterator
*/
sdll_iterator Insertion (sdll_list_t, sdll_iterator_t);






#endif /*SORTED_LINKED_LIST_H*/
