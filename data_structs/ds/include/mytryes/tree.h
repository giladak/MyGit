#ifndef ILRD_BINARY_TREE
#define ILRD_BINARY_TREE

#include <stddef.h> /*size_t*/



typedef binary_tree bin_tree_t;
typedef binary_tree_node bt_node_t;


struct binary_tree_node
{
	void *data;
	bt_node_t *prev;
	bt_node_t *right;
	bt_node_t *left;
}



struct binary_tree
{
	bt_node_t *root;
}



/*************************************************************************************************************************
** creates the linked list

** Return value: pointer to list. In failure returns NULL.
**
** Complexity: o(1) ***********************************************************************************************************/
bin_tree_t *BinaryTreeCreate();



/*************************************************************************************************************************
** frees all the memory in the linked list

** Complexity: o(1) ***********************************************************************************************************/
void BinaryTreeDestroy(bt_node_t *list);



/*************************************************************************************************************************
** Return value: 1 - empty, 0 - not empty.
**
** Complexity: o(1) ***********************************************************************************************************/
int BinaryTreeIsEmpty(const bt_node_t *list);




/*************************************************************************************************************************
** Return value: the first iterator.
**
** Complexity: o(1) ***********************************************************************************************************/

dll_iterator_t BinaryTreeBegin(const bt_node_t *list); /*return first validy iterator (not dummy)*/





/*************************************************************************************************************************
** Return value: the size of the list.
**
** Complexity: o(1) ***********************************************************************************************************/

size_t BinaryTreeSize(const bt_node_t *list);





/*************************************************************************************************************************
** Return value: the last iterator (the dummy iterator)
**
** Complexity: o(1) ***********************************************************************************************************/
dll_iterator_t BinaryTreeEnd(const bt_node_t *list); 



/*************************************************************************************************************************
** Return value: the next iterator.
**
** Complexity: o(1) ***********************************************************************************************************/

dll_iterator_t BinaryTreeNext(const dll_iterator_t iterator);


/*************************************************************************************************************************
** Return value: the prv iterator.
**
** Complexity: o(1) ***********************************************************************************************************/

dll_iterator_t BinaryTreePrev(const dll_iterator_t iterator);


 /*
	a function that compers two adresses of iterators
	arguments :
	iterator1 - for comparison
	iterator2 - for comparison
	return value: 1 if equal, 0 if not
*/

int BinaryTreeSameIter(const dll_iterator_t iterator1,const dll_iterator_t iterator2);

/*
	a function that presents the value in a iterator
	arguments: 
	iterator - a pointer to the iterator
	return value: the adress of the value of the iterator
*/


void *BinaryTreeGetData(const dll_iterator_t iterator);

/*
	a function that inserts a iterator to the list
	arguments : 
	iterator - a pointer to the next iterator
	data - a pointer to the data the user wansts to add
	return value: a pointer to the new iterator
*/

dll_iterator_t BinaryTreeInsertBefore(const dll_iterator_t iterator, void *data);



/*
	a function that removes a node from the list
	arguments : a pointer to the iterator
	return value: no return value
*/

dll_iterator_t BinaryTreeRemove(dll_iterator_t iterator); /*return the next node*/



/*
	a function that implements a action an all nodes
	arguments :
	from - the node the function will starts its action from
	to - the node the function will finish its action
	action_func - a pointer to afunction to implement a desired action on all nodes
	param - a parameter for the action_func
	
	return value: in succsess function returns 0, in failure returns the value the failed action fun returns
*/

int BinaryTreeForEach(dll_iterator_t from, dll_iterator_t to, int (*action_func)(void *data, void *param), void *param);

/*
	a function that searches for desired nodes
	arguments :
	from - the node the function will starts its action from
	to - the node the function will finish its action
	match_func - a function to implement compatison of any kind
	param - a parameter for the match_func
	
	return value: in succsess function returns desird node pointer, in failure returns last node
*/


dll_iterator_t BinaryTreeFind(dll_iterator_t from, dll_iterator_t to, int (*match_func)(const void *data, const void *param),const void *param);











#endif /*ILRD_QUEUE*/


