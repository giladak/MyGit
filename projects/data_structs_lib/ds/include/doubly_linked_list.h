

#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H


#include <stdlib.h> /*size_t*/



typedef struct doubly_linked_list dll_t; /*in the header*/
typedef struct doubly_linked_list_node* dll_iterator_t; /*in the header*/




/*************************************************************************************************************************
** creates the linked list

** Return value: pointer to list. In failure returns NULL.
**
** Complexity: o(1) ***********************************************************************************************************/
dll_t *DoublyLinkedListCreate();



/*************************************************************************************************************************
** frees all the memory in the linked list

** Complexity: o(1) ***********************************************************************************************************/
void DoublyLinkedListDestroy(dll_t *list);



/*************************************************************************************************************************
** Return value: 1 - empty, 0 - not empty.
**
** Complexity: o(1) ***********************************************************************************************************/
int DoublyLinkedListIsEmpty(const dll_t *list);




/*************************************************************************************************************************
** Return value: the first iterator.
**
** Complexity: o(1) ***********************************************************************************************************/

dll_iterator_t DoublyLinkedListBegin(const dll_t *list); /*return first validy iterator (not dummy)*/





/*************************************************************************************************************************
** Return value: the size of the list.
**
** Complexity: o(1) ***********************************************************************************************************/

size_t DoublyLinkedListSize(const dll_t *list);





/*************************************************************************************************************************
** Return value: the last iterator (the dummy iterator)
**
** Complexity: o(1) ***********************************************************************************************************/
dll_iterator_t DoublyLinkedListEnd(const dll_t *list); 



/*************************************************************************************************************************
** Return value: the next iterator.
**
** Complexity: o(1) ***********************************************************************************************************/

dll_iterator_t DoublyLinkedListNext(const dll_iterator_t iterator);


/*************************************************************************************************************************
** Return value: the prv iterator.
**
** Complexity: o(1) ***********************************************************************************************************/

dll_iterator_t DoublyLinkedListPrev(const dll_iterator_t iterator);


 /*
	a function that compers two adresses of iterators
	arguments :
	iterator1 - for comparison
	iterator2 - for comparison
	return value: 1 if equal, 0 if not
*/

int DoublyLinkedListSameIter(const dll_iterator_t iterator1,const dll_iterator_t iterator2);

/*
	a function that presents the value in a iterator
	arguments: 
	iterator - a pointer to the iterator
	return value: the adress of the value of the iterator
*/


void *DoublyLinkedListGetData(const dll_iterator_t iterator);

/*
	a function that inserts a iterator to the list
	arguments : 
	iterator - a pointer to the next iterator
	data - a pointer to the data the user wansts to add
	return value: a pointer to the new iterator
*/

dll_iterator_t DoublyLinkedListInsertBefore(const dll_iterator_t iterator, void *data);

/*
	a function that inserts a iterator to the beginig of the list
	arguments : 
	list - a pointer to the relavent list
	data - a pointer to the data the user wansts to add
	return value: a pointer to the new iterator
*/

dll_iterator_t DoublyLinkedListPushFront(dll_t *list, void *data); 


/*
	a function that inserts a iterator to the end of the list
	arguments : 
	list - a pointer to the relavent list
	data - a pointer to the data the user wansts to add
	return value: a pointer to the new iterator
*/


dll_iterator_t DoublyLinkedListPushBack(dll_t *list, void *data);

/*
	a function that removes a node from the list
	arguments : a pointer to the iterator
	return value: no return value
*/

dll_iterator_t DoublyLinkedListRemove(dll_iterator_t iterator); /*return the next node*/

/*
	a function that removes a iterator to the end of the list
	arguments : 
	list - a pointer to the relavent list
	return value: a pointer to the new iterator
*/

void *DoublyLinkedListPopBack(dll_t *list);/*return the data that wasin the poped node */


/*
	a function that removes a iterator to the begining of the list
	arguments : 
	list - a pointer to the relavent list
	return value: a pointer to the new iterator
*/

void *DoublyLinkedListPopFront(dll_t *list);


/*
	a function that implements a action an all nodes
	arguments :
	from - the node the function will starts its action from
	to - the node the function will finish its action
	action_func - a pointer to afunction to implement a desired action on all nodes
	param - a parameter for the action_func
	
	return value: in succsess function returns 0, in failure returns the value the failed action fun returns
*/

int DoublyLinkedListForEach(dll_iterator_t from, dll_iterator_t to, int (*action_func)(void *data, void *param), void *param);

/*
	a function that searches for desired nodes
	arguments :
	from - the node the function will starts its action from
	to - the node the function will finish its action
	match_func - a function to implement compatison of any kind
	param - a parameter for the match_func
	
	return value: in succsess function returns desird node pointer, in failure returns last node
*/


dll_iterator_t DoublyLinkedListFind(dll_iterator_t from, dll_iterator_t to, int (*match_func)(const void *data, const void *param),const void *param);

/*
	a function that searches for desired nodes and stores them in seperate linked list
	arguments :
	from - the node the function will starts its action from
	to - the node the function will finish its action
	match_func - a function to implement compatison of any kind
	param - a parameter for the match_func
	out_list - a linked list to restore the found values
	
	
	return value: in succsess function returns desird node pointer, in failure returns NULL
*/

int DoublyLinkedListMultiFind(dll_iterator_t from, dll_iterator_t to, int (*match_func)(const void *data,const void *param) ,const void *param, dll_t *out_list);


/* copies sevrel elements from one dll to another
from - the first copied element
to - the copying will stop at to (to wouldnt move to the other list
where - the content will be pased before the where iterator 																									return the last copied iterator which is one before to
 																								*/

dll_iterator_t DoublyLinkedListSplice(dll_iterator_t where, dll_iterator_t from, dll_iterator_t to); 


#endif /*DOUBLY_LINKED_LIST_H*/
