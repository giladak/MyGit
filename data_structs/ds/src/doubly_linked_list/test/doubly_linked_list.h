
#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H


#include <stdlib.h> /*size_t*/


typedef struct doubly_linked_list_node dll_node_t;   /*in the .c file.  dll == doubly linked lised */
typedef struct doubly_linked_list dll_t; /*in the header*/
typedef struct doubly_linked_list_node* dll_iterator_t; /*in the header*/




/*************************************************************************************************************************
** Return value: pointer to list.
**
** Complexity: o(1) ***********************************************************************************************************/
dll_t *DoublyLinkedListCreate();



/*************************************************************************************************************************
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

int DoublyLinkedListSize(const dll_t *list);





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


int DoublyLinkedListSameIter(const dll_iterator_t iterator1,const dll_iterator_t iterator2);

void *DoublyLinkedListGetData(const dll_iterator_t iterator);

dll_iterator_t DoublyLinkedListInsertBefore(const dll_iterator_t iterator, void *data);

dll_iterator_t DoublyLinkedListPushFront(dll_t *list, void *data); /*return the new pushed node*/

dll_iterator_t DoublyLinkedListPushBack(dll_t *list, void *data); /*return the new pushed node*/

dll_iterator_t DoublyLinkedListRemove(dll_iterator_t iterator); /*return the next node*/

void *DoublyLinkedListPopBack(dll_t *list);/*return the data that wasin the poped node */

void *DoublyLinkedListPopFront(dll_t *list);

int DoublyLinkedListForEach(dll_iterator_t from, dll_iterator_t to, int (*action_func)(void *data, void *param), void *param);

dll_iterator_t DoublyLinkedListFind(dll_iterator_t from, dll_iterator_t to, int (*match_func)(const void *data, const void 										*param),const void *param);

int DoublyLinkedListMultiFind(dll_iterator_t from, dll_iterator_t to, int (*match_func)(void *data, void *param),
				 			 void *param, dll_t *out_list);

dll_iterator_t DoublyLinkedListSplice(dll_iterator_t where, dll_iterator_t from, dll_iterator_t to); /*copy before where.
 																									return the last copied 																											iterator which is one before to*/


#endif /*DOUBLY_LINKED_LIST_H*/


















