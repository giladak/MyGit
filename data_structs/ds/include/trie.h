#ifndef TRIE_H
#define TRIE_H

#include <stddef.h> /*size_t*/

typedef struct trie trie_t;

typedef struct trie_node trie_node_t;  /*HEADER OF TRIE*/

trie_t* TrieCreate();

void TrieDestroy(trie_t *trie);

int TrieInsert(trie_t *trie, char *key, char *answer);

int TrieRemove(trie_t *trie,  char *key);

int TrieIsEmpty(const trie_t *trie);

size_t TrieCount(const trie_t *trie);

#endif /* TRIE_H */



/*
static trie_node_t *FindNextSubTreeParent(trie_node_t *sub_tree_root, char *string, char **path_split_point)
{
	trie_node_t *return_node = NULL;

	while (*string != '\0')
	{
		if (*string != RIGHT && FULL != sub_tree_root->child[RIGHT]->is_full)
		{
			path_split_point = &string;
			return_node = sub_tree_root;
		}

		sub_tree_root = sub_tree_root->child[*string];
		++string;
	}

	return (return_node);
}
*/