

	
#ifndef SORTED_LINKED_LIST_H
#define SORTED_LINKED_LIST_H

#include "doubly_linked_list.h"


typedef struct sorted_list sorted_list_t; 
typedef struct sorted_list_iterator sorted_list_iterator_t; 




struct sorted_list_iterator 
{
    dll_iterator_t doubly_iter;
    #ifndef NDEBUG
    sorted_list_t *list;
    #endif
    
};




/*
 	description: a function that creates a new sorted linked list
 	compare function - a function that will guide the sorting of the array, will return 0 in sucsess any other answer in failure.	
 	Return value: the function returns a pointer to the new sorted list
 	Complexity: o(1) 

*/

sorted_list_t *SortedLinkedListCreate(int(*cmp)(const void* data1, const void* data2));

/*
	description: a function that destroys the sorted list
	
	arguments: the list that requries destraction
	
	Return value: non

 Complexity: o(n) 
*/
void SortedLinkedListDestroy(sorted_list_t *list);


/*
	description: a function that check if the list is empty
	
	arguments: the list
	
	Return value: 1 if empty 0 if not

 	Complexity: o(1) 
*/


int SortedLinkedListIsEmpty(const sorted_list_t *list);

/*
	description: a function that gives the user the begining iterator of the list
	
	arguments: the list
	
	Return value: the iterator of the begining of the list

 	Complexity: o(1) 
*/
sorted_list_iterator_t SortedLinkedListBegin(const sorted_list_t *list); /*return first validy iterator (not dummy)*/

/*
	description: a function that gives the user the end iterator of the list
	
	arguments: the list
	
	Return value: the iterator of the end of the list

 	Complexity: o(1) 
*/
size_t SortedLinkedListSize(const sorted_list_t *list);/*call for each*/


/*
** Return value: 
**
** Complexity: o() 
*/
sorted_list_iterator_t SortedLinkedListEnd(const sorted_list_t *list); 



/*
** Return value:
**
** Complexity: o(1) 
*/
sorted_list_iterator_t SortedLinkedListNext(const sorted_list_iterator_t iterator);

/*
** Return value: 
**
** Complexity: o() 
*/

sorted_list_iterator_t SortedLinkedListPrev(const sorted_list_iterator_t iterator);

/*
** Return value: 
**
** Complexity: o(1) 
*/
sorted_list_iterator_t SortedLinkedListInsert(sorted_list_t *list, void *data);

/* 
	given arguments: 
	returns: 
**
** Complexity: o() 
*/

int SortedLinkedListForEach(sorted_list_iterator_t from, sorted_list_iterator_t to, int (*action_func)(void *data, void *param), void *param);

/** 
	given arguments: 
	returns: 
	complexity O()
	
*/
int SortedLinkedListSameIter(const sorted_list_iterator_t iterator1,const sorted_list_iterator_t iterator2);


/*
	
	given arguments: 
	returns: 
	complexity O()

*/
void *SortedLinkedListGetData(const sorted_list_iterator_t iterator);
	

/*


	
	given arguments: 
	returns: 
	complexity O()

*/

sorted_list_iterator_t SortedLinkedListRemove(sorted_list_iterator_t iterator); /*return the next node*/


/*
	
	given arguments:
	returns: 
	complexity O()
*/

void *SortedLinkedListPopBack(sorted_list_t *list);

/*
	
	given arguments: 
	returns: 
	complexity O()

*/

void *SortedLinkedListPopFront(sorted_list_t *list);

/*

	
	given arguments: 
	return: 
	complexity O()
*/

sorted_list_iterator_t SortedLinkedListFindIf(sorted_list_iterator_t from, sorted_list_iterator_t to, int (*match_func)(const void *data, const void *param),const void *param); 										





/*
	merge list src to dest.
	given arguments: dest and src list - sorted lists
	return: non
	complexity O(N+M)

*/

void SortedLinkedListMerge(sorted_list_t *dest, sorted_list_t *src);/*reuse splice*/


/*
	
	given arguments: 
	return: 
	complexity O(N)

*/

sorted_list_iterator_t SortedLinkedListFind(sorted_list_t *list,sorted_list_iterator_t from, sorted_list_iterator_t to, const void *data); 	




#endif /*SORTED_LINKED_LIST_H*/
















