/*
	dev : Gilad Kahn
	rev : 
	status: approved
	date: 10.2.22
*/


#include <stdio.h> /*for*/
#include <stdlib.h> /*malloc*/
#include <assert.h> /*assert*/
#include <string.h> /*memcpy*/

#include "binary_tree.h"
#include "utilities.h"

#define TREE_HEAD sizeof(binary_tree_t)
#define NODE_SIZE sizeof(binary_tree_node_t)

#define PREV 0
#define NEXT 1
#define EQUAL 2

#define TREE_PARAM *(int*)tree->param



/*
typedef struct binary_tree binary_tree_t;                
typedef struct binary_tree_node *binary_tree_iterator_t;
*/

typedef struct binary_tree_node binary_tree_node_t;

enum child_node_side
{
    LEFT = 0,
    RIGHT = 1,
    NUM_OF_SIDES = 2
};


struct binary_tree_node
{
   void *data;
   binary_tree_node_t *sides[NUM_OF_SIDES];
   binary_tree_node_t *parent;
};     
                                                 
struct binary_tree 
{
    binary_tree_node_t root_stab; 
    void *param;
    int (*cmp)(const void *data1, const void *data2, const void *param);
};


static int ActionFuncCount(void *data, void *param);
static binary_tree_node_t *IteratorToNode(binary_tree_iterator_t iterator);
static binary_tree_iterator_t NodeToIterator (binary_tree_node_t *node);
static binary_tree_node_t *CreateNode(void *data, binary_tree_node_t *right ,binary_tree_node_t *left, binary_tree_node_t *parent);
static binary_tree_node_t *GoToNode(const void *data, const binary_tree_t *tree);
static binary_tree_node_t *GoToRootStab(const binary_tree_t *tree);
static binary_tree_node_t *GoLeft(binary_tree_node_t *node);
static int CheckParentSide(binary_tree_node_t *node);
static void DestroyNode(binary_tree_node_t *node);

static binary_tree_node_t *ClingToSide(binary_tree_node_t *node, size_t side);
static binary_tree_node_t *MoveInOrder(binary_tree_node_t *node, size_t direction);
static binary_tree_node_t *InsertToNode(binary_tree_node_t *parent_node,void *data, size_t side);
static void ConnectNodes(binary_tree_node_t *parent_node,binary_tree_node_t *child_node, size_t side);
static int IsLeaf(binary_tree_node_t *node);
static int HasOneChild(binary_tree_node_t *node);
static int CheckOneChildSide(binary_tree_node_t *node);
static int ConvertToDirection(int cmpare_function_answer);

/**********************************Create********************************/


binary_tree_t *BinaryTreeCreate(int(*cmp)(const void *data1, const void *data2, const void *param), void *param)
{
    binary_tree_t *new_tree = NULL;

    assert(cmp);

    new_tree = (binary_tree_t *)malloc(TREE_HEAD);

    if (NULL == new_tree)
    {
        return (NULL);
    }

    new_tree -> cmp = cmp;
    new_tree ->param = param;
    new_tree ->root_stab.data = NULL;
    new_tree ->root_stab.parent = NULL;
    new_tree->root_stab.sides[RIGHT] = NULL;
    new_tree->root_stab.sides[LEFT] = NULL;

    return (new_tree);
}

/**********************************IsEmpty********************************/


int BinaryTreeIsEmpty(const binary_tree_t *tree)
{
    assert(tree);

    return(NULL == tree->root_stab.sides[LEFT]);
}

/**********************************Begin********************************/


binary_tree_iterator_t BinaryTreeBegin(const binary_tree_t *tree)
{
    binary_tree_node_t *runner = NULL;
    binary_tree_iterator_t answer;

    assert(tree);

    runner = GoToRootStab(tree);

    runner = ClingToSide(runner, LEFT);
    
    answer = NodeToIterator(runner);

    return(answer);
}


static binary_tree_node_t *GoToRootStab(const binary_tree_t *tree)
{
    binary_tree_node_t *root_stab = NULL;

    assert(tree);

    root_stab = (binary_tree_node_t*)&tree->root_stab;

    return(root_stab);
}

/**********************************GetData********************************/


void *BinaryTreeGetData(const binary_tree_iterator_t iterator)
{   
    assert(iterator);

    return (iterator->data);
}


/**********************************Insert********************************/

binary_tree_iterator_t BinaryTreeInsert(binary_tree_t *tree, void *data)
{
    binary_tree_node_t *parent_node = NULL;
    binary_tree_node_t *new_node = NULL;
    binary_tree_iterator_t new_iterator;


    assert(tree);
    assert(data);

    parent_node = GoToNode(data, tree);
    
    assert(EQUAL != TREE_PARAM);

    new_node = InsertToNode(parent_node, data, TREE_PARAM);

    new_iterator = NodeToIterator(new_node);

    return(new_iterator);
}




/*******************************Find******************************************/

binary_tree_iterator_t BinaryTreeFind(const binary_tree_t *tree, const void *data)
{
    binary_tree_node_t *requested_node = NULL;
    binary_tree_iterator_t answer;

    assert(tree);
    assert(data);

    requested_node = GoToNode(data, tree);

    if (EQUAL != TREE_PARAM)
    {
        return(NULL);
    }

    answer = NodeToIterator(requested_node);

    return(answer);
}										



/**********************************Remove********************************/

void BinaryTreeRemove(binary_tree_iterator_t iterator) /*return the next node*/
{                  
    binary_tree_node_t *runner = NULL;
    binary_tree_node_t *next_node = NULL;
    binary_tree_node_t *next_node_child = NULL;
    int runner_side = 0;
    int grandson_side = 0;

    runner = IteratorToNode(iterator);
    runner_side = CheckParentSide(runner);

    if (TRUE == IsLeaf(runner))
    {   
        runner->parent->sides[runner_side] = NULL;
    }

    else if(TRUE == HasOneChild(runner))
    {
        grandson_side = CheckOneChildSide(runner);
        ConnectNodes(runner->parent, runner->sides[grandson_side], runner_side);
    }

    else
    {
        next_node = IteratorToNode(BinaryTreeNext(iterator));

        /*case 1, the next node is the son*/

        if (next_node == runner->sides[RIGHT])
        {   
            ConnectNodes(runner->parent, next_node, RIGHT);
            ConnectNodes(next_node, GoLeft(runner), LEFT);
        }

        /*case , the next node is a grandsonson*/

        else
        {   
            next_node_child = next_node->sides[RIGHT];
            ConnectNodes(next_node->parent, next_node_child, LEFT);

            ConnectNodes(runner->parent, next_node, runner_side);
            ConnectNodes(next_node, runner->sides[LEFT], LEFT);
            ConnectNodes(next_node, runner->sides[RIGHT], RIGHT);
        }
    }

    DestroyNode(runner);
}


static binary_tree_node_t *IteratorToNode(binary_tree_iterator_t iterator)
{
    binary_tree_node_t *node = iterator;

    return(node);
}

static binary_tree_iterator_t NodeToIterator (binary_tree_node_t *node)
{
    binary_tree_iterator_t iterator = node;

    return (iterator);
}


static binary_tree_node_t *CreateNode(void *data, binary_tree_node_t *right, binary_tree_node_t *left, binary_tree_node_t *parent)
{
    binary_tree_node_t *new_node = (binary_tree_node_t *)malloc(NODE_SIZE);

    new_node -> data = data;
    new_node-> parent = parent;

    new_node->sides[LEFT] = left;
    new_node->sides[RIGHT] = right;

    return(new_node);
}


static binary_tree_node_t *GoToNode(const void *data, const binary_tree_t *tree)
{
    binary_tree_node_t *runner = NULL;
    int answer = 0;

    assert(data);
    assert(tree);

    runner = GoToRootStab(tree);
    TREE_PARAM = LEFT;

    while (NULL != runner->sides[TREE_PARAM] && EQUAL != TREE_PARAM)
    {
        runner = runner->sides[TREE_PARAM];

        answer = (*tree->cmp)(data, runner->data, NULL);
        TREE_PARAM = ConvertToDirection(answer);
    }
    return(runner);
}


static binary_tree_node_t *GoLeft(binary_tree_node_t *node)
{
    return(node->sides[LEFT]);
}


static int CheckParentSide(binary_tree_node_t *node)
{

    assert(node);

    if (node == node->parent->sides[LEFT])
    {
        return(LEFT);
    }

    return(RIGHT);
}


/**********************************Next********************************/

binary_tree_iterator_t BinaryTreeNext(const binary_tree_iterator_t iterator)
{
    return(MoveInOrder(iterator, NEXT));  
}


static binary_tree_iterator_t MoveInOrder(const binary_tree_iterator_t iterator, size_t direction)
{
    binary_tree_iterator_t answer;
    binary_tree_node_t *runner = NULL;
    int child_side = RIGHT;
    int side = RIGHT;

    if (direction == PREV)
    {
        side = LEFT;
    }

    runner = IteratorToNode(iterator);

    /*stage one check if node has any kids to his right*/

    if (NULL != runner->sides[side])
    {   
        runner = runner->sides[side];

        runner = ClingToSide(runner, (!side));
    }

    /*stage two: check if node has any ansecter to his right*/

    else
    {
        child_side = side;

        while (child_side != (!side))
        {   
            child_side = CheckParentSide(runner);

            runner = runner->parent;
        }

    }

    answer = NodeToIterator(runner);
 
    return(answer);
}

/**********************************Prev********************************/



binary_tree_iterator_t BinaryTreePrev(const binary_tree_iterator_t iterator)
{
    return(MoveInOrder(iterator, PREV));
}





/********************************End********************************/

binary_tree_iterator_t BinaryTreeEnd(const binary_tree_t *tree)
{
    binary_tree_iterator_t answer;

    /*long casting is necessery do surpass const issue*/

    answer = NodeToIterator(GoToRootStab(tree));

    return(answer);
}

/**********************************IsEqual********************************/

int BinaryTreeIterIsEqual(const binary_tree_iterator_t iterator1,const binary_tree_iterator_t iterator2)
{
    return (iterator1 == iterator2);
}




/*************************************For Each***********************************/




int BinaryTreeForEach(binary_tree_iterator_t from, binary_tree_iterator_t to, int(*action_func)(void *data, void *param), void *param)
{
    binary_tree_iterator_t runner;
    int function_return_value = 0;

    assert(action_func);

    runner = from;

    while (1 != BinaryTreeIterIsEqual(runner, to))
    {
        function_return_value = (*action_func)(BinaryTreeGetData(runner), param);

        if (0 != function_return_value)
        {
            return(function_return_value);
        }

        runner = BinaryTreeNext(runner);
    }

    return(0);
}

/******************************************Destroy*********************************************/


void BinaryTreeDestroy(binary_tree_t *tree)
{   
    binary_tree_iterator_t runner = NULL;
    binary_tree_iterator_t temp = NULL;
    binary_tree_iterator_t end = NULL;

    assert(tree);

    runner = BinaryTreeBegin(tree);
    end = BinaryTreeEnd(tree);

    while (1 != BinaryTreeIterIsEqual(runner,end))
    {
        temp = BinaryTreeNext(runner);

        BinaryTreeRemove(runner);

        runner = temp;
    }

    free(tree);
    tree = NULL;
}




/******************************************Size*********************************************/


size_t BinaryTreeSize(const binary_tree_t *tree)
{
    size_t count = 0;

    assert (tree);

    BinaryTreeForEach(BinaryTreeBegin(tree), BinaryTreeEnd(tree), ActionFuncCount, &count);

    return(count);
}



static int ActionFuncCount(void *data, void *param)
{   
	UNUSED(data);

	assert(param);

	++*(size_t*)param;
		
	return (0);
}


static binary_tree_node_t *ClingToSide(binary_tree_node_t *node, size_t side)
{
    assert(node);

    while(NULL != node->sides[side])
    {   
        node = node->sides[side];
    }

    return(node);
}


static binary_tree_node_t *InsertToNode(binary_tree_node_t *parent_node,void *data, size_t side)
{
    binary_tree_node_t *new_node = NULL;

    assert (parent_node);

    new_node = CreateNode(data, NULL, NULL, parent_node);

    parent_node->sides[side] = new_node; 

    return (new_node);
}



static void ConnectNodes(binary_tree_node_t *parent_node,binary_tree_node_t *child_node, size_t side)
{
        if (NULL != child_node)
        {
            child_node->parent = parent_node;
        }

        parent_node->sides[side] = child_node;
}


static int IsLeaf(binary_tree_node_t *node)
{
    return(NULL == node->sides[RIGHT] && NULL == node->sides[LEFT]);
}



static int HasOneChild(binary_tree_node_t *node)
{   
    return((NULL == node->sides[RIGHT] && NULL != node->sides[LEFT]) || (NULL != node->sides[RIGHT] && NULL == node->sides[LEFT]));
}


static int CheckOneChildSide(binary_tree_node_t *node)
{
    if(NULL == node->sides[RIGHT] && NULL != node->sides[LEFT])
    {
        return(LEFT);
    }

    return(RIGHT);
}





static void DestroyNode(binary_tree_node_t *node)
{
    assert(node);

    free(node);

    node = NULL;
}


static int ConvertToDirection(int compare_function_answer)
{

    if (0 < compare_function_answer)
    {
        return(RIGHT);
    }

    if (0 > compare_function_answer)
    {
        return(LEFT);
    }
    
    return(EQUAL);
}