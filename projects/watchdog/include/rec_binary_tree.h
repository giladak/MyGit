	
#ifndef REC_BINART_TREE_H
#define REC_BINART_TREE_H


#include <stddef.h>

typedef struct rec_binary_tree rec_binary_tree_t;           
typedef struct rec_binary_tree_node rec_binary_tree_node_t;   /*  in C file */


typedef enum order_type   
{
    PRE_ORDER = 0,
    IN_ORDER = 1,
    POST_ORDER = 2,
    NUM_OF_ORDERS = 3
}order_type_t;



/*************************************************************************************************************************
description: creats a new binary tree
 
 arguments:
 cmp- a compare function that will decide where the new data shall be inserted
 
 return value: a pointer to the new binary tree
 
 complexity: 0(1)
**************************************************************************************************************************/
rec_binary_tree_t *RecBinaryTreeCreate(int (*cmp)(const void *data1, const void *data2));




/*************************************************************************************************************************
description: destroys binary tree
 
 arguments:
 cmp- a compare function that will decide where the new data shall be inserted
 
 return value: a pointer to the new binary tree
 
 complexity: 0(1)
**************************************************************************************************************************/
void RecBinaryTreeDestroy(rec_binary_tree_t *tree);





/*************************************************************************************************************************

**************************************************************************************************************************/
int RecBinaryTreeIsEmpty(const rec_binary_tree_t *tree);




/*************************************************************************************************************************

**************************************************************************************************************************/
size_t RecBinaryTreeCount(const rec_binary_tree_t *tree);




/*************************************************************************************************************************

**************************************************************************************************************************/
int RecBinaryTreeInsert(rec_binary_tree_t *tree, void *data);


int RecBinaryTreeInsertWithoutBalance(rec_binary_tree_t *tree, void *data);



/*************************************************************************************************************************

**************************************************************************************************************************/
int RecBinaryTreeForEach(rec_binary_tree_t *tree, int (*action_func)(void *data, void *param), void *param, order_type_t order);



/*************************************************************************************************************************

**************************************************************************************************************************/
void RecBinaryTreeRemove(rec_binary_tree_t *tree,const void *data);




/*************************************************************************************************************************

**************************************************************************************************************************/
void *RecBinaryTreeFind(const rec_binary_tree_t *tree, const void *data); 




/*************************************************************************************************************************

**************************************************************************************************************************/
size_t RecBinaryTreeHeight(const rec_binary_tree_t *tree); 





/*************************************************************************************************************************/






/*************************************************************************************************************************/



#endif /*REC_BINART_TREE_H*/




















/*
int RecBinaryTreeInsert(rec_binary_tree_t *tree, void *data)
{

    int side = 0;

    assert(tree);
    assert(data);

    parent_node = GoToNode(tree, tree->root, data, &side);

    if (NULL == parent_node)
    {
        tree->root = CreateNode(data);
        return(0);
    }

    return(InsertToNode(parent_node, data, side));
}
*/


/*
static rec_binary_tree_node_t *FindParentWithData(rec_binary_tree_t *tree, rec_binary_tree_node_t *runner, void *data, int *child_side)
{

    static rec_binary_tree_node_t *parent = NULL;
    rec_binary_tree_node_t *temp = NULL;
    int compare_answer = 0;

    assert(tree);
    assert(data);

    if (NULL == runner)
    {
        temp = parent;
        parent = NULL;
        return (temp);
    }

    compare_answer = tree->cmp(data, runner->data);

    if (0 == compare_answer)
    {
        temp = parent;
        parent = NULL;
        return (temp);
    }

    *child_side = ConvertToDirection(compare_answer);
    parent = runner;

    return (FindParentWithData(tree, runner->child[*child_side], data, child_side));
}
*/
/*

static void FindAndRemoveNode(rec_binary_tree_t *tree, rec_binary_tree_node_t *parent, int *side)
{
    int grand_child_side = 0;
    int next_node_side = 0;
    rec_binary_tree_node_t *temp = NULL;
    rec_binary_tree_node_t *next_node = NULL;
    rec_binary_tree_node_t *next_node_parent = NULL;




        if (TRUE == IsLeaf(parent->child[*side]))
        {
            FreeNode(parent->child[*side]);
            parent->child[*side] = NULL;
            UpdateHeight(parent);
        }

        else if (TWO_CHILDREN != CheckChildSides(parent->child[*side]))
        {
            grand_child_side = CheckChildSides(parent->child[*side]);
            temp = parent->child[*side]->child[grand_child_side];
            FreeNode(parent->child[*side]);
            parent->child[*side] = temp;

            UpdateHeight(parent->child[*side]);
            UpdateHeight(parent);

            parent = MakeBalanced(parent->child[*side]);

            UpdateHeight(parent->child[*side]);
            UpdateHeight(parent);
        }

        else
        {
            next_node = ClingToSide(parent->child[*side]->child[RIGHT], LEFT);
            next_node_parent = FindParentWithData(tree, parent, next_node->data, &next_node_side);
            CopyNodeData(parent->child[*side], next_node);
            FindAndRemoveNode(tree, next_node_parent, &next_node_side);
        }
}

static void UpdateHeight_2(rec_binary_tree_node_t *node);
static rec_binary_tree_node_t *FindParentWithData(rec_binary_tree_t *tree, rec_binary_tree_node_t *runner, void *data, int *child_side);
static void DecrementHeightIfNeccsery(rec_binary_tree_node_t *node);
static void FindAndRemoveNode_old(rec_binary_tree_t *tree, rec_binary_tree_node_t *parent, int *side);
static rec_binary_tree_node_t *RemoveNode(rec_binary_tree_node_t *node);



static void DecrementHeightIfNeccsery(rec_binary_tree_node_t *node)
{
    if (1 != (NodeHeight(node) - NodeHeight(node->child[LEFT])) && 1 != (NodeHeight(node) - NodeHeight(node->child[RIGHT])))
    {
        --node->height;
    }
}

*/