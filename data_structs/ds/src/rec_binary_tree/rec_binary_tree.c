/*
    dev : Gilad Kahn
    rev : Nimrod Segev
    status: approved
    date: 21.2.22
*/

#include <stdio.h>  /*for*/
#include <stdlib.h> /*malloc*/
#include <assert.h> /*assert*/


#include "rec_binary_tree.h"
#include "utilities.h"

#define TREE_HEAD_SIZE sizeof(rec_binary_tree_t)
#define TREE_NODE_SIZE sizeof(rec_binary_tree_node_t)
#define EQUAL 2
#define EVEN 2
#define TWO_CHILDREN 2

enum child_node_side /*****  in C file *****/
{
    LEFT = 0,
    RIGHT = 1,
    NUM_OF_SIDES = 2
};

struct rec_binary_tree_node
{
    void *data;
    size_t height;
    rec_binary_tree_node_t *child[NUM_OF_SIDES];
};

struct rec_binary_tree
{
    rec_binary_tree_node_t *root;
    int (*cmp)(const void *data1, const void *data2);
};

/*****************assictance functions***********/

static rec_binary_tree_node_t *CreateNode(void *data);
static int ConvertToDirection(int compare_function_answer);
static rec_binary_tree_node_t *InsertToTree(rec_binary_tree_t *tree, rec_binary_tree_node_t *runner, void *data, int *sucsess);
static rec_binary_tree_node_t *GoToNode(rec_binary_tree_t *tree, rec_binary_tree_node_t *runner, void *data, int *node_side);
static rec_binary_tree_node_t *ClingToSide(rec_binary_tree_node_t *node, int side);
static void FreeNode(rec_binary_tree_node_t *node);
static int IsLeaf(rec_binary_tree_node_t *node);
static void CopyNodeData(rec_binary_tree_node_t *dest, rec_binary_tree_node_t *src);
static void DoNothing(rec_binary_tree_node_t *runner, void *param);
static int TraversePreOrder(rec_binary_tree_node_t *runner, int (*action_func)(void *data, void *param), void (*node_action_func)(rec_binary_tree_node_t *runner, void *param), void *param);
static int TraverseInOrder(rec_binary_tree_node_t *runner, int (*action_func)(void *data, void *param), void (*node_action_func)(rec_binary_tree_node_t *runner, void *param), void *param);
static int TraversePostOrder(rec_binary_tree_node_t *runner, int (*action_func)(void *data, void *param), void (*node_action_func)(rec_binary_tree_node_t *runner, void *param), void *param);
static int CheckChildSides(rec_binary_tree_node_t *node);
static rec_binary_tree_node_t * FindAndRemoveNode(rec_binary_tree_t *tree, rec_binary_tree_node_t *runner, void *data);
static int NodeBalance(rec_binary_tree_node_t *node);
static int NodeHeight(rec_binary_tree_node_t *node);
static rec_binary_tree_node_t *Rotate(rec_binary_tree_node_t *sub_tree_root, int side);
static int ConvertBalanceToSide(int balance);
static rec_binary_tree_node_t *MakeBalanced(rec_binary_tree_node_t *sub_tree_root);
static rec_binary_tree_node_t *InsertToTreeWithoutBalance(rec_binary_tree_t *tree, rec_binary_tree_node_t *runner, void *data, int *node_side, int *sucsess);
static void UpdateHeight(rec_binary_tree_node_t *node);
static int DoNothingWithData(void *data, void *param);
static void DeleteNodeForTraverse(rec_binary_tree_node_t *node, void *param);
static int ActionFuncCount(void *data, void *param);


/******************************Create*******************************/

rec_binary_tree_t *RecBinaryTreeCreate(int (*cmp)(const void *data1, const void *data2))
{
    rec_binary_tree_t *new_tree = NULL;

    assert(cmp);

    new_tree = (rec_binary_tree_t *)malloc(TREE_HEAD_SIZE);

    if (NULL == new_tree)
    {
        return (NULL);
    }

    new_tree->cmp = cmp;
    new_tree->root = NULL;

    return (new_tree);
}

/******************************Is Empty*******************************/

int RecBinaryTreeIsEmpty(const rec_binary_tree_t *tree)
{
    assert(tree);

    return (NULL == tree->root);
}

/******************************Insert*******************************/

int RecBinaryTreeInsert(rec_binary_tree_t *tree, void *data)
{
    int sucsess = 0;

    assert(tree);
    assert(data);

    tree->root = InsertToTree(tree, tree->root, data, &sucsess);
    UpdateHeight(tree->root);

    tree->root = MakeBalanced(tree->root);
    UpdateHeight(tree->root);

    return (sucsess);
}

/******************************Find*******************************/

void *RecBinaryTreeFind(const rec_binary_tree_t *tree, const void *data)
{
    rec_binary_tree_node_t *data_node = NULL;
    int side = 0;

    data_node = GoToNode((rec_binary_tree_t *)tree, tree->root, (void *)data, &side);

    if (EQUAL != side)
    {
        return (NULL);
    }

    return (data_node->data);
}

/******************************Remove*******************************/

void RecBinaryTreeRemove(rec_binary_tree_t *tree, const void *data)
{
    assert(tree);
    assert(data);


    tree->root = FindAndRemoveNode(tree, tree->root, (void *)data);
    UpdateHeight(tree->root);

    tree->root = MakeBalanced(tree->root);
    UpdateHeight(tree->root);
}

/******************************ForEach*******************************/

int RecBinaryTreeForEach(rec_binary_tree_t *tree, int (*action_func)(void *data, void *param), void *param, order_type_t order)
{
    assert(tree);
    assert(action_func);

    switch (order)
    {
    case PRE_ORDER:
        return (TraversePreOrder(tree->root, action_func, DoNothing, param));

    case IN_ORDER:
        return (TraverseInOrder(tree->root, action_func, DoNothing, param));

    case POST_ORDER:
        return (TraversePostOrder(tree->root, action_func, DoNothing, param));
    }

    return (1);
}

/******************************Count*******************************/

size_t RecBinaryTreeCount(const rec_binary_tree_t *tree)
{
    size_t count = 0;

    assert(tree);

    RecBinaryTreeForEach((rec_binary_tree_t *)tree, ActionFuncCount, &count, IN_ORDER);

    return (count);
}

/**********************************Destroy********************************/

void RecBinaryTreeDestroy(rec_binary_tree_t *tree)
{
    TraversePostOrder(tree->root, DoNothingWithData, DeleteNodeForTraverse, NULL);

    free(tree);

    tree = NULL;
}

/**********************************Height********************************/

size_t RecBinaryTreeHeight(const rec_binary_tree_t *tree)
{
    assert(tree);

    if (NULL == tree->root)
    {
        return (0);
    }

    return (tree->root->height);
}

/**************************************help funcs********************************/

static rec_binary_tree_node_t *FindAndRemoveNode(rec_binary_tree_t *tree, rec_binary_tree_node_t *runner, void *data)
{
    int side = 0;
    int compare_answer = 0;
    int grand_child_side = 0;
    rec_binary_tree_node_t *temp = NULL;
    rec_binary_tree_node_t *next_node = NULL;

    assert(tree);
    assert(data);

    if (NULL == runner)
    {
        return(NULL);
    }

    compare_answer = tree->cmp(data, runner->data);

    if (0 == compare_answer)
    {
        if (TRUE == IsLeaf(runner))
        {
            FreeNode(runner);
            return(NULL);
        }

        else if (TWO_CHILDREN != CheckChildSides(runner))
        {
            grand_child_side = CheckChildSides(runner);
            temp = runner->child[grand_child_side];
            FreeNode(runner);
            runner = NULL;
            return(temp);
        }

        else
        {
            next_node = ClingToSide(runner->child[RIGHT], LEFT);
            CopyNodeData(runner, next_node);
            runner->child[RIGHT] = FindAndRemoveNode(tree, runner->child[RIGHT],next_node->data);
            return(runner);
        }
    }    

    side = ConvertToDirection(compare_answer);

    runner->child[side] = FindAndRemoveNode(tree, runner->child[side], data); 

    UpdateHeight(runner);


    if (NULL != runner->child[side])
    {
        runner->child[side] = MakeBalanced(runner->child[side]);

        UpdateHeight(runner);
    }
    return(runner);
}

static rec_binary_tree_node_t *InsertToTree(rec_binary_tree_t *tree, rec_binary_tree_node_t *runner, void *data, int *sucsess)
{
    int compare_answer = 0;
    int node_side = 0;
    rec_binary_tree_node_t *new_node = NULL;

    if (runner == NULL)
    {
        new_node = CreateNode(data);

        if (NULL == new_node)
        {
            *sucsess = 1;
        }

        return (new_node);
    }

    compare_answer = tree->cmp(data, runner->data);

    node_side = ConvertToDirection(compare_answer);

    runner->child[node_side] = InsertToTree(tree, runner->child[node_side], data, sucsess);

    UpdateHeight(runner->child[node_side]);
    UpdateHeight(runner);

    runner->child[node_side] = MakeBalanced(runner->child[node_side]);

    UpdateHeight(runner->child[node_side]);
    UpdateHeight(runner);

    return (runner);
}


static rec_binary_tree_node_t *MakeBalanced(rec_binary_tree_node_t *sub_tree_root)
{
    int balance = 0;
    int rotation_direction = 0;

    balance = NodeBalance(sub_tree_root);
    rotation_direction = ConvertBalanceToSide(balance);

    if (EVEN != rotation_direction)
    {
        if (0 > balance * NodeBalance(sub_tree_root->child[!rotation_direction]))
        {
            sub_tree_root->child[!rotation_direction] = Rotate(sub_tree_root->child[!rotation_direction], !rotation_direction);
        }

        return (Rotate(sub_tree_root, rotation_direction));
    }

    return (sub_tree_root);
}

static rec_binary_tree_node_t *GoToNode(rec_binary_tree_t *tree, rec_binary_tree_node_t *runner, void *data, int *node_side)
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

    *node_side = ConvertToDirection(compare_answer);

    parent = runner;

    if (0 == compare_answer)
    {
        parent = NULL;
        return (runner);
    }

    return (GoToNode(tree, runner->child[*node_side], data, node_side));
}


static rec_binary_tree_node_t *CreateNode(void *data)
{
    rec_binary_tree_node_t *new_node = NULL;

    assert(data);

    new_node = (rec_binary_tree_node_t *)malloc(TREE_NODE_SIZE);
    if (NULL == new_node)
    {
        return (NULL);
    }

    new_node->data = data;
    new_node->height = 1;
    new_node->child[LEFT] = NULL;
    new_node->child[RIGHT] = NULL;

    return (new_node);
}

static int ConvertToDirection(int compare_function_answer)
{

    if (0 < compare_function_answer)
    {
        return (RIGHT);
    }

    if (0 > compare_function_answer)
    {
        return (LEFT);
    }

    return (2);
}

static rec_binary_tree_node_t *ClingToSide(rec_binary_tree_node_t *node, int side)
{
    if (node->child[side] == NULL)
    {
        return (node);
    }

    return (ClingToSide(node->child[side], side));
}

static void FreeNode(rec_binary_tree_node_t *node)
{
    free(node);
    node = NULL;
}

static int IsLeaf(rec_binary_tree_node_t *node)
{
    return (NULL == node->child[RIGHT] && NULL == node->child[LEFT]);
}

static void CopyNodeData(rec_binary_tree_node_t *dest, rec_binary_tree_node_t *src)
{
    dest->data = src->data;
}

static void DoNothing(rec_binary_tree_node_t *runner, void *param)
{
    UNUSED(runner);
    UNUSED(param);
}

static int ActionFuncCount(void *data, void *param)
{
    UNUSED(data);

    assert(param);

    ++*(size_t *)param;

    return (0);
}

static int TraversePreOrder(rec_binary_tree_node_t *runner, int (*action_func)(void *data, void *param), void (*node_action_func)(rec_binary_tree_node_t *runner, void *param), void *param)
{
    static int action_func_answer = 0;
    int temp = 0;

    if (NULL == runner)
    {
        return (action_func_answer);
    }

    if (action_func_answer != 1)
    {
        action_func_answer = action_func(runner->data, param);
        node_action_func(runner, param);

        TraversePreOrder(runner->child[RIGHT], action_func, node_action_func, param);
        TraversePreOrder(runner->child[LEFT], action_func, node_action_func, param);
    }

    temp = action_func_answer;
    action_func_answer = 0;

    return (temp);
}



static int TraverseInOrder(rec_binary_tree_node_t *runner, int (*action_func)(void *data, void *param), void (*node_action_func)(rec_binary_tree_node_t *runner, void *param), void *param)
{
    static int action_func_answer = 0;
    int temp = 0;

    if (NULL == runner)
    {
        return (action_func_answer);
    }

    if (1 != action_func_answer)
    {
        TraverseInOrder(runner->child[LEFT], action_func, node_action_func, param);
    }

    if (1 != action_func_answer)
    {
        action_func_answer = action_func(runner->data, param);
        node_action_func(runner, param);

        TraverseInOrder(runner->child[RIGHT], action_func, node_action_func, param);
    }

    temp = action_func_answer;
    action_func_answer = 0;

    return (temp);
}

static int TraversePostOrder(rec_binary_tree_node_t *runner, int (*action_func)(void *data, void *param), void (*node_action_func)(rec_binary_tree_node_t *runner, void *param), void *param)
{
    static int action_func_answer = 0;
    int temp = 0;

    if (NULL == runner)
    {
        return (action_func_answer);
    }

    if (1 != action_func_answer)
    {
        TraverseInOrder(runner->child[RIGHT], action_func, node_action_func, param);

        TraverseInOrder(runner->child[LEFT], action_func, node_action_func, param);
    }

    if (1 != action_func_answer)
    {
        action_func_answer = action_func(runner->data, param);
        node_action_func(runner, param);
    }
    temp = action_func_answer;
    action_func_answer = 0;

    return (temp);
}

static int CheckChildSides(rec_binary_tree_node_t *node)
{
    if (NULL != node->child[RIGHT] && NULL != node->child[LEFT])
    {
        return (2);
    }

    else if (NULL != node->child[RIGHT])
    {
        return (RIGHT);
    }

    else if (NULL != node->child[LEFT])
    {
        return (LEFT);
    }

    return (-1);
}

static int NodeBalance(rec_binary_tree_node_t *node)
{
    assert(node);

    return (NodeHeight(node->child[RIGHT]) - NodeHeight(node->child[LEFT]));
}


static int NodeHeight(rec_binary_tree_node_t *node)
{
    if (NULL == node)
    {
        return (0);
    }

    return (node->height);
}

static rec_binary_tree_node_t *Rotate(rec_binary_tree_node_t *sub_tree_root, int side)
{
    rec_binary_tree_node_t *pivot = NULL;

    assert(sub_tree_root);

    pivot = sub_tree_root->child[!side];
    sub_tree_root->child[!side] = pivot->child[side];
    pivot->child[side] = sub_tree_root;

    UpdateHeight(sub_tree_root);
    UpdateHeight(pivot);


    return (pivot);
}

static int ConvertBalanceToSide(int balance)
{
    if (1 < balance)
    {
        return (LEFT);
    }

    if (-1 > balance)
    {
        return (RIGHT);
    }

    return (EVEN);
}

static rec_binary_tree_node_t *InsertToTreeWithoutBalance(rec_binary_tree_t *tree, rec_binary_tree_node_t *runner, void *data, int *node_side, int *sucsess)
{
    int compare_answer = 0;
    rec_binary_tree_node_t *new_node = NULL;

    if (runner == NULL)
    {
        new_node = CreateNode(data);

        if (NULL == new_node)
        {
            *sucsess = 1;
        }

        return (new_node);
    }

    compare_answer = tree->cmp(data, runner->data);

    *node_side = ConvertToDirection(compare_answer);

    runner->child[*node_side] = InsertToTree(tree, runner->child[*node_side], data, sucsess);

    return (runner);
}


static void UpdateHeight(rec_binary_tree_node_t *node)
{
    if (NULL == node)
    {
        node->height = 0;
    }

    node->height = (1 + MAX(NodeHeight(node->child[RIGHT]) ,NodeHeight(node->child[LEFT])));
}

int RecBinaryTreeInsertWithoutBalance(rec_binary_tree_t *tree, void *data)
{
    int side = 0;
    int sucsess = 0;

    assert(tree);
    assert(data);

    tree->root = InsertToTreeWithoutBalance(tree, tree->root, data, &side, &sucsess);

    return (sucsess);
}

static int DoNothingWithData(void *data, void *param)
{
    UNUSED(data);
    UNUSED(param);

    return (0);
}

static void DeleteNodeForTraverse(rec_binary_tree_node_t *node, void *param)
{
    FreeNode(node);
    UNUSED(param);
}

