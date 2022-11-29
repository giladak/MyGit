	
#ifndef BINART_TREE_H
#define BINART_TREE_H

#include <stddef.h> /*size_t*/



typedef struct binary_tree binary_tree_t;                  /*in the header- tree*/
typedef struct binary_tree_node *binary_tree_iterator_t; /*in the header*/




/*************************************************************************************************************************
 Return value: pointer to tree.
**
** Complexity: o(1) 
***********************************************************************************************************/
binary_tree_t *BinaryTreeCreate(int (*cmp)(const void *data1, const void *data2, const void *param), void *param);

/*************************************************************************************************************************
** Complexity: o(n) 
************************************************************************************************************************/
void BinaryTreeDestroy(binary_tree_t *tree);


/*************************************************************************************************************************
** Return value: 1 - empty, 0 - not empty.
**
** Complexity: o(1) 
***********************************************************************************************************/
int BinaryTreeIsEmpty(const binary_tree_t *tree);


/*************************************************************************************************************************
** Return value: the first iterator.
**
** Complexity: o(1) 
***********************************************************************************************************/

binary_tree_iterator_t BinaryTreeBegin(const binary_tree_t *tree); /*return first validy iterator (not dummy)*/

	

/*************************************************************************************************************************
** Return value: the size of the tree.
**given arguments: tree
**returns: the size of tree(number of nodes));
** Complexity: o(n) 
***********************************************************************************************************/

size_t BinaryTreeSize(const binary_tree_t *tree);/*call for each*/





/*************************************************************************************************************************
** Return value: the last iterator (the dummy iterator)
**
** Complexity: o(1) 
***********************************************************************************************************/
binary_tree_iterator_t BinaryTreeEnd(const binary_tree_t *tree); /*what is end?*/



/*************************************************************************************************************************
** Return value: the next iterator.
**
** Complexity: o(1) 
***********************************************************************************************************/

binary_tree_iterator_t BinaryTreeNext(const binary_tree_iterator_t iterator);


/*************************************************************************************************************************
** Return value: the prv iterator.
**
** Complexity: o(1) 
***********************************************************************************************************/

binary_tree_iterator_t BinaryTreePrev(const binary_tree_iterator_t iterator);
/***************************************************************************************************************
** Return value: the insert iterator.
**
** Complexity: o(1) 


requirment: if fail return stab
**************************************************************************************************/
binary_tree_iterator_t BinaryTreeInsert(binary_tree_t *tree, void *data);

/*************************************************************************************************************************
** execuate a given function on a tree ( giving starting and ending point ) using a specific paramater.
	given arguments: start and ending points ('from' and 'to'(not including to)), function address, paramater.
	returns: return 1 for for True and 0 for False.
	
**
** Complexity: o(n) 
***************************************************************************************************************************/
int BinaryTreeForEach(binary_tree_iterator_t from, binary_tree_iterator_t to, int (*action_func)(void *data, void *param), void *param);

/*************************************************************************************************************************
** checks if two iterators are the same one
	given arguments: two iterators
	returns: TRUE (1) or FALSE (0)
	complexity O(1)
	
***************************************************************************************************************************/

int BinaryTreeIterIsEqual(const binary_tree_iterator_t iterator1,const binary_tree_iterator_t iterator2);


/*************************************************************************************************************************

	return the value (data) of a specific iterator.
	given arguments: iterator.
	returns: the value (data) of a given iterator.
	complexity O(1)

***************************************************************************************************************************/

void *BinaryTreeGetData(const binary_tree_iterator_t iterator);

/*************************************************************************************************************************

	

	remove a given iterator from a tree
	given arguments: pointer to iterator
	returns: return the next iterator
	complexity O(1)

***************************************************************************************************************************/
void BinaryTreeRemove(binary_tree_iterator_t iterator); /*return the next node*/


/*************************************************************************************************************************

	

	checks if a paramater is in the tree.
	given arguments: start and ending points ('from' and 'to'(not including to)), function address, paramater to check.
	return: if paramater is in the tree, returns the address of iterator, if not return the ending point(to)
	complexity O(N)

***************************************************************************************************************************/
binary_tree_iterator_t BinaryTreeFind(const binary_tree_t *tree, const void *data); 										


/*************************************************************************************************************************/

	




#endif /*BINART_TREE_H*/
















