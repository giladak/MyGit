/*
	dev : Gilad Kahn
	rev : Tomer Fridman
	status: approved
	date: 21.2.22
*/


#ifndef HASH_TABLE_H
#define HASH_TABLE_H


#include <stddef.h>
#include "doubly_linked_list.h"

typedef struct hash_table hash_table_t; /*in header*/

/*****************************************
 description: creats a new hash table
 
 arguments:
 size - the size of the new hash table
 cmp- a compare function that will decide where the new data shall be inserted
 
 return value: a pointer to the new hash table
 
 complexity: 0(1)
*****************************************/

hash_table_t *HashTableCreate(size_t size,int(*cmp)(const void *key1, const void *key2),  size_t(*hash_function)(const void *key));/*use modulo */
/*****************************************
 description: destroys the hash table
 
 arguments:
	- a pointer to the new hash table
 
 return value: non
 
 complexity: 0(n)
 *****************************************/
void HashTableDestroy(hash_table_t *hash_table);
/*****************************************

description: remove a element from the hash table
 
 arguments:
	- a pointer to the new hash table
 
 return value: non
 
 complexity: 0(1)
 *****************************************/
void HashTableRemove(hash_table_t *hash_table, const void *key);
/*****************************************

description: insert a element f the hash table
 
 arguments:
	- a pointer to the hash table
 	- a pointer to the new data location	
 	
 return value: 0 on sucssess and 1 in failure
 
 complexity: 0(1)
 *****************************************/
int HashTableInsert(hash_table_t *hash_table, void *data);
/*****************************************
description: check the number of elements inserted to the hash table
 
 arguments:
	- a pointer to the hash table	
 	
 return value: the number of elements inserted to the hash table
 
 complexity: 0(1)
 *****************************************/
size_t HashTableSize(const hash_table_t *hash_table);
/*****************************************

description: check if the hash table is empty
 
 arguments:
	- a pointer to the hash table	
 	
 return value: 1 if empty, zero if not
 
 complexity: 0(1)
 *****************************************/
int HashTableIsEmpty(const hash_table_t *hash_table);
/*****************************************
description: returns data from the hash table through data key
 
 arguments:
	- a pointer to the hash table
	- a pointer to the relavent key	
 	
 return value: a pointer to the data stored with the key
 
 complexity: 0(1)
 *****************************************/
void *HashTableFind(const hash_table_t *hash_table, const void *key);/* pointer to data itself*/
/*****************************************

description: acts uppon each node
 
 arguments:
	- a pointer to the hash table
	- a pointer to a action function
	- a pointer to a parameter
 	
 return value: 0 on sucssess and 1 in failure
 
 complexity: 0(1)
 *****************************************/
int HashTableForEach(hash_table_t *hash_table, int (*action_func)(void *data, void *param), void *param);
/*****************************************

description: calculates the load factor of the table
 
 arguments:
	- a pointer to the hash table

 	
 return value: the load Factor of the hash table 
 
 complexity: 0(1)
 *****************************************/
double HashTableLoadFactor(const hash_table_t *hash_table);
/*****************************************
 description: calculates the standerd devition of the table
 
 arguments:
	- a pointer to the hash table

 	
 return value: the standerd devition of the hash table 
 
 complexity: 0(1)
 *****************************************/
double HashTableStandardDeviation(const hash_table_t *hash_table);
#endif /*HASH_TABLE_H*/

