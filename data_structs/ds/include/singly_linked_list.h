
#ifndef LINKED_LIST_H
#define LINKED_LIST_H



#include <stddef.h> /*size_t*/







typedef struct singly_linked_list_iterator *sll_iterator_t;   /* sll == singly linked lised */

typedef struct singly_linked_list sll_t; /* sll == singly linked list */




/*
a function the creates a linked list
arguments : the function takes no arguments
return value: a pointer to the link_list struct
*/

sll_t *SinglyLinkedListCreate();

/*
	a function that searches for desired nodes
	arguments :
	from - the node the function will starts its action from
	to - the node the function will finish its action
	match_func - a function to implement compatison of any kind
	param - a parameter for the match_func
	
	return value: in succsess function returns desird node pointer, in failure returns last node
*/

sll_iterator_t LinkedListFind(sll_iterator_t from, sll_iterator_t to, int (*match_func)(const void *data, void *param), void *param);

/*
a function that frees all the nodes
arguments : a pointer to the list
return value: no return value
*/

void SinglyLinkedListDestroy(sll_t *list);


/*
	a function that implements a action an all nodes
	arguments :
	from - the node the function will starts its action from
	to - the node the function will finish its action
	action_func - a pointer to afunction to implement a desired action on all nodes
	param - a parameter for the action_func
	
	return value: in succsess function returns 0, in failure returns the value the failed action fun returns
*/

int SinglyLinkedListForEach(sll_iterator_t from, sll_iterator_t to, int(*action_func)(void *data, void *param),void *param);


 /*
	a function that counts the number of elements in a list
	arguments : a pointer to the list
	return value: the number of elements
*/
 
size_t SinglyLinkedListCount(const sll_t *list);

 /*
	a function that removes a node from the list
	arguments : a pointer to the iterator
	return value: no return value
*/
 
void SinglyLinkedListRemove(sll_iterator_t iterator);

 /*
	a function that compers two adresses of iterators
	arguments :
	iterator1 - for comparison
	iterator2 - for comparison
	return value: 0 if equal, 1 if not
*/

int SinglyLinkedListIsEqual(const sll_iterator_t iterator1, const sll_iterator_t iterator2);


/*
	a function that inserts a iterator to the list
	arguments : 
	iterator - a pointer to the next iterator
	data - a pointer to the data the user wansts to add
	return value: a pointer to the new iterator
*/

sll_iterator_t SinglyLinkedlistInsert(sll_iterator_t iterator ,void *data); 


/*
	a function that presents the first iterator of the function
	arguments: 
	list - a pointer to the linked list
	return value: a pointer to the first iterator
*/


sll_iterator_t SinglyLinkedListBegin(const sll_t *list);  /* o(1) */


/*
	a function that presents the last iterator of the function
	arguments: 
	list - a pointer to the linked list
	return value: a pointer to the last iterator
*/

sll_iterator_t SinglyLinkedListEnd(const sll_t *list); /* o(n) */


/*
	a function that sets the value in a iterator
	arguments: 
	iterator - a pointer to the iterator
	return value: no return value
*/

void SinglyLinkedListSetData(sll_iterator_t iterator, void *data);

/*
	a function that presents the value in a iterator
	arguments: 
	iterator - a pointer to the iterator
	return value: the adress of the value of the iterator
*/

void *SinglyLinkedListGetData(const sll_iterator_t iterator);

/*
	a function that presents the next iterator in line
	arguments: 
	iterator - a pointer to the iterator
	return value: the adress of the next iterator
*/

sll_iterator_t SinglyLinkedListNext(const sll_iterator_t iterator);


/*
	a function that appends the src link list to the dest list
	arguments: 
	dest - the linked list which will receive new nodes
	src - the link list which will pass its elements and get destroyed
	return value: pointer to the dest link list
*/
sll_t *SinglyLinkedListAppend(sll_t *dest, sll_t *src);


#endif /* linked_list*/









