/**************************************************************************

	dev : Gilad Kahn
	rev: 
	status: 
	date:
*******************************************************************/	


#include <stdio.h>  /*printf*/
#include <stdlib.h> /*size_t*/
#include <assert.h> /*assert*/
#include "doubly_linked_list.h"



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
	list -> tail.prev = NULL;
	list -> tail.data = NULL;
	
	return (list);
}












