#ifndef RECURSIVE_TREE_H
#define RECURSIVE_TREE_H

#include <stddef.h> /*size_t*/



typedef struct recursive_tree recursive_tree_t;     
typedef struct recursive_tree_node recursive_tree_node_t;               



enum child_node_side
{
    LEFT = 0,
    RIGHT = 1,
    NUM_OF_SIDES = 2
};


struct recursive_tree_node
{
   void *data;
   recursive_tree_node_t *sides[NUM_OF_SIDES];
};     
                                                 
struct recursive_tree 
{
    recursive_tree_node_t root_stab; 
    void *param;
    int (*cmp)(const void *data1, const void *data2, const void *param);
};




/*************************************************************************************************************************
 Return value: pointer to tree.
**
** Complexity: o(1) 
***********************************************************************************************************/
recursive_tree_t *RecursiveTreeCreate(int (*cmp)(const void *data1, const void *data2, const void *param), void *param);

/*************************************************************************************************************************
** Complexity: o(n) 
************************************************************************************************************************/
void RecursiveTreeDestroy(recursive_tree_t *tree);


/*************************************************************************************************************************
** Return value: 1 - empty, 0 - not empty.
**
** Complexity: o(1) 
***********************************************************************************************************/
int RecursiveTreeIsEmpty(const recursive_tree_t *tree);


/*************************************************************************************************************************
** Return value: the first iterator.
**
** Complexity: o(1) 
***********************************************************************************************************/

void *RecursiveTreeBegin(const recursive_tree_t *tree); /*return first validy iterator (not dummy)*/

	

/*************************************************************************************************************************
** Return value: the size of the tree.
**given arguments: tree
**returns: the size of tree(number of nodes));
** Complexity: o(n) 
***********************************************************************************************************/

size_t RecursiveTreeSize(const recursive_tree_t *tree);/*call for each*/





/*************************************************************************************************************************
** Return value: the last iterator (the dummy iterator)
**
** Complexity: o(1) 
***********************************************************************************************************/
void * RecursiveTreeEnd(const recursive_tree_t *tree); /*what is end?*/




/***************************************************************************************************************
** Return value: the insert iterator.
**
** Complexity: o(1) 


requirment: if fail return stab
**************************************************************************************************/
void * RecursiveTreeInsert(recursive_tree_t *tree, void *data);

/*************************************************************************************************************************
** execuate a given function on a tree ( giving starting and ending point ) using a specific paramater.
	given arguments: start and ending points ('from' and 'to'(not including to)), function address, paramater.
	returns: return 1 for for True and 0 for False.
	
**
** Complexity: o(n) 
***************************************************************************************************************************/
int RecursiveTreeForEach(void * from_data, void * to, int (*action_func)(void *data, void *param), void *param);

/*************************************************************************************************************************
** checks if two iterators are the same one
	given arguments: two iterators
	returns: TRUE (1) or FALSE (0)
	complexity O(1)
	
***************************************************************************************************************************/

int RecursiveTreeIterIsEqual(const void *data1,const void *data2);


/*************************************************************************************************************************

	

	remove a given iterator from a tree
	given arguments: pointer to iterator
	returns: return the next iterator
	complexity O(1)

***************************************************************************************************************************/
void RecursiveTreeRemove(void *data); /*return the next node*/


/*************************************************************************************************************************

	

	checks if a paramater is in the tree.
	given arguments: start and ending points ('from' and 'to'(not including to)), function address, paramater to check.
	return: if paramater is in the tree, returns the address of iterator, if not return the ending point(to)
	complexity O(N)

***************************************************************************************************************************/
void * RecursiveTreeFind(const recursive_tree_t *tree, const void *data); 										


/*************************************************************************************************************************/

	




#endif /*BINART_TREE_H*/







