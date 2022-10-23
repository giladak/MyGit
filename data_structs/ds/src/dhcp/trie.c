/*
	dev : Gilad Kahn
	rev : Daniel Gabay
	status: approved
	date: 3.3.22
*/

#include <stdio.h>	/*for*/
#include <stdlib.h> /*malloc*/
#include <assert.h> /*assert*/
#include <string.h> /*strcmp*/

#include "utilities.h"
#include "trie.h"

#define STRING_LEN 10
#define FULL 1
#define FAIL 1

#define LEFT 0
#define RIGHT 1
#define NUM_OF_CHILDREN 2

enum failures
{
	SUCCSESS = 0,
	ALLOCATION_FAIL = 1,
	NOT_EMPTY = 2
};

struct trie_node /* IN C FILE OF TRIE */
{
	trie_node_t *child[NUM_OF_CHILDREN];
	int is_full;
	char bit;
};

struct trie
{
	size_t depth;
	trie_node_t *root;
};

/***********************help functions declerations******************************/
static void DestroyRootNode(trie_node_t *node);
static int NodesMemoryAllocation(trie_node_t *empty_slot_parent, char *string);
static trie_node_t *CreateNewNode(void);
static void UpdateIsFull(trie_node_t *node);
static trie_node_t *InsertToPath(trie_node_t *sub_tree_root, char *path, int *succsess);
static trie_node_t *GoToSmallestAvaliableAndAlloc(trie_node_t *sub_tree_root, char *string, int *succsess);
static int IsLeaf(trie_node_t *node);
static size_t Count(trie_node_t *node);
static trie_node_t *RemoveNode(trie_node_t *node ,char *key, int *succsess);
static void DestroyLeafNode(trie_node_t *node);
/***********************Create******************************/

trie_t *TrieCreate()
{
	trie_t *new_trie = (trie_t *)malloc(sizeof(trie_t));

	if (NULL == new_trie)
	{
		return (NULL);
	}

	new_trie->root = CreateNewNode();
	if (NULL == new_trie->root)
	{
		free(new_trie);
		return (NULL);
	}

	return (new_trie);
}

/***********************Destroy******************************/

void TrieDestroy(trie_t *trie)
{
	assert(trie);

	DestroyRootNode(trie->root);

	trie->root = NULL;

	free(trie);
}

/***********************IsEmpty******************************/
int TrieIsEmpty(const trie_t *trie)
{
	assert(trie);

	return (NULL == trie->root->child[RIGHT] && NULL == trie->root->child[LEFT]);
}

/***********************TrieInsert******************************/
int TrieInsert(trie_t *trie, char *key, char *answer)
{
	int succsess = 0;

	assert(trie);
	assert(key);

	memcpy(answer, key, strlen(key) + 1);

	trie->root = InsertToPath(trie->root, answer, &succsess);

	UpdateIsFull(trie->root);

	return (succsess);
}

/***********************TrieRemve******************************/


/***********************TrieSize******************************/

size_t TrieCount(const trie_t *trie)
{
	size_t counter = 0;

	counter += Count(trie->root->child[RIGHT]);
	counter += Count(trie->root->child[LEFT]);

	return (counter);
}


/***********************remove******************************/

int TrieRemove(trie_t *trie,  char *key)
{	
	int side = 0;
	int succsess = 0;


	assert(trie);
	assert(key);

	side = *key - ASCII_ZERO;

	trie->root->child[side] = RemoveNode(trie->root->child[side] ,++key, &succsess);

	UpdateIsFull(trie->root);

	return(succsess);
}


/***********************help functions******************************/

static void DestroyRootNode(trie_node_t *node)
{
	if (NULL != node)
	{
		DestroyRootNode(node->child[LEFT]);
		DestroyRootNode(node->child[RIGHT]);
		free(node);
	}
}

static trie_node_t *GoToSmallestAvaliableAndAlloc(trie_node_t *sub_tree_root, char *string, int *succsess)
{
	if (NULL == sub_tree_root->child[LEFT])
	{
		*string = LEFT + ASCII_ZERO;
		*succsess = NodesMemoryAllocation(sub_tree_root, string);
		UpdateIsFull(sub_tree_root);
		return (sub_tree_root);
	}

	else if (FULL != sub_tree_root->child[LEFT]->is_full)
	{
		*string = LEFT + ASCII_ZERO;
		return (GoToSmallestAvaliableAndAlloc(sub_tree_root->child[LEFT], ++string, succsess));
	}

	else if (NULL == sub_tree_root->child[RIGHT])
	{
		*string = RIGHT + ASCII_ZERO;
		*succsess = NodesMemoryAllocation(sub_tree_root, string);
		UpdateIsFull(sub_tree_root);
		return (sub_tree_root);
	}

	else
	{
		*string = RIGHT + ASCII_ZERO;
		return (GoToSmallestAvaliableAndAlloc(sub_tree_root->child[RIGHT], ++string, succsess));
	}
}

static int NodesMemoryAllocation(trie_node_t *empty_slot_parent, char *string)
{
	assert(empty_slot_parent);
	assert(string);

	if ('\0' == *string)
	{
		empty_slot_parent->is_full = FULL;
		return (0);
	}

	else if (NULL == empty_slot_parent->child[LEFT])
	{
		empty_slot_parent->child[LEFT] = CreateNewNode();
		UpdateIsFull(empty_slot_parent);
		if (NULL == empty_slot_parent->child[LEFT])
		{
			return (1);
		}
		*string = '0';
		return (NodesMemoryAllocation(empty_slot_parent->child[LEFT], ++string));
	}

	else
	{
		empty_slot_parent->child[RIGHT] = CreateNewNode();
		UpdateIsFull(empty_slot_parent);
		if (NULL == empty_slot_parent->child[RIGHT])
		{
			return (1);
		}
		*string = '1';
		return (NodesMemoryAllocation(empty_slot_parent->child[RIGHT], ++string));
	}
}

static trie_node_t *CreateNewNode(void)
{
	trie_node_t *new_node = (trie_node_t *)malloc(sizeof(trie_node_t));

	new_node->child[RIGHT] = NULL;
	new_node->child[LEFT] = NULL;

	new_node->is_full = EMPTY;

	return (new_node);
}

static void UpdateIsFull(trie_node_t *node)
{
	if (NULL != node->child[RIGHT] && NULL != node->child[LEFT])
	{
		if (FULL == node->child[RIGHT]->is_full && FULL == node->child[LEFT]->is_full)
		{
			node->is_full = FULL;
		}
		else
		{
			node->is_full = EMPTY;
		}
	}

	else
	{
		node->is_full = EMPTY;
	}
}

static trie_node_t *InsertToPath(trie_node_t *parent, char *path, int *succsess)
{
	int side = 0;

	assert(succsess);
	assert(path);
	assert(parent);

	side = *path - ASCII_ZERO;

	if ('\0' == *path)
	{
		parent->is_full = FULL;
		return (parent);
	}

	if (NULL == parent->child[side])
	{
		parent->child[side] = CreateNewNode();

		if (NULL == parent->child[side])
		{
			*succsess = ALLOCATION_FAIL;
			return (NULL);
		}

		parent->child[side] = InsertToPath(parent->child[side], ++path, succsess);
	}

	else if (FULL == parent->child[side]->is_full)
	{
		*succsess = NOT_EMPTY;
	}

	else if (FULL != parent->child[side]->is_full)
	{
		parent->child[side] = InsertToPath(parent->child[side], ++path, succsess);
	}

	/****************************/

	if (NOT_EMPTY == *succsess)
	{
		if (RIGHT == side)
		{
			return (parent);
		}

		else if (NULL == parent->child[RIGHT])
		{
			*succsess = NodesMemoryAllocation(parent, path);
		}

		else if (FULL == parent->child[RIGHT]->is_full)
		{
			return (parent);
		}

		else if (NULL != parent->child[RIGHT] && FULL != parent->child[RIGHT]->is_full)
		{
			side = RIGHT;
			*path = '1';
			parent->child[RIGHT] = GoToSmallestAvaliableAndAlloc(parent->child[RIGHT], ++path, succsess);
		}
	}

	UpdateIsFull(parent);
	return (parent);
}

static int IsLeaf(trie_node_t *node)
{
	assert(node);

	return (NULL == node->child[RIGHT] && NULL == node->child[LEFT]);
}

static size_t Count(trie_node_t *node)
{	
	size_t count = 0;


	if (NULL == node)
	{
		return(0);	
	}

	count += Count(node->child[RIGHT]);
	count += Count(node->child[LEFT]);

	if (TRUE == IsLeaf(node))
	{
		++count;
	}

	return (count);	
}


static trie_node_t *RemoveNode(trie_node_t *node ,char *key, int *succsess)
{	
	int side = 0;

	assert(node);
	assert(key);
	assert(succsess);

	side = *key - ASCII_ZERO;

	if('\0' == *key)
	{
		DestroyLeafNode(node);
		return(NULL);
	}

	else if (NULL == node->child[side])
	{
		*succsess = FAIL;
		return(node);
	}

	else
	{
		node->child[side] = RemoveNode(node->child[side], ++key, succsess);

		if(TRUE == IsLeaf(node))
		{
			DestroyLeafNode(node);
			return(NULL);
		}

		UpdateIsFull(node);
		return(node);
	}
}

static void DestroyLeafNode(trie_node_t *node)
{	
	assert(node);

	node->child[LEFT] = NULL;
	node->child[RIGHT] = NULL;

	free(node);
}







