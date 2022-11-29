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
