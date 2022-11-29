
#include <stdio.h>   /*for*/
#include <stdlib.h>  /*malloc*/
#include <assert.h> /*assert*/


#include "doubly_linked_list.h"
#include "hash_table.h"
#include "utilities.h"


struct hash_table /*in c file*/
{
    size_t(*hash_function)(const void *key);
    int(*cmp)(const void *key1, const void *key2);
    size_t size;
    dll_t **array;
};






static int ActionFuncCount(void *data, void *param);
void FreeUpTo(hash_table_t *hash_table, size_t index);
size_t FitForTableSize(hash_table_t *hash_table, size_t hash_function_answer);

/************************************create ********************************/

hash_table_t *HashTableCreate(size_t size,int(*cmp)(const void *key1, const void *key2),  size_t(*hash_function)(const void *key))
{
    hash_table_t *new_table = NULL;
    size_t i = 0;

    assert(cmp);
    assert(hash_function);

    new_table = (hash_table_t *)malloc(sizeof(hash_table_t));
    if(NULL == new_table)
    {
        return(NULL);
    }

    new_table->array = (dll_t**)malloc(sizeof(dll_t*)*size);
    if(NULL == new_table->array)
    {   
        free(new_table);
        return(NULL);
    }


    for (i = 0; i < size; ++i)
    {
        new_table->array[i] = DoublyLinkedListCreate();

        if(NULL == new_table->array[i])
        {   
            FreeUpTo(new_table, i);
            free(new_table->array);    
            free(new_table);
            return(NULL);
        }
    }

    new_table->cmp = cmp;
    new_table->hash_function = hash_function;
    new_table->size = size;


    return(new_table);
}


/************************************destroy********************************/

void HashTableDestroy(hash_table_t *hash_table)
{   
    assert(hash_table);

    FreeUpTo(hash_table, hash_table->size);

    free(hash_table->array);
    free (hash_table);
    hash_table = NULL;
}


/************************************Is Empty********************************/

int HashTableIsEmpty(const hash_table_t *hash_table)
{   
    assert(hash_table);

    return(0 == HashTableSize(hash_table));     
}


/************************************insert********************************/ 

int HashTableInsert(hash_table_t *hash_table, void *data)
{
    size_t insertion_index = 0;
    dll_iterator_t list_iterator = NULL;

    assert(data);
    assert(hash_table);          

    insertion_index = hash_table->hash_function(data);

    insertion_index = FitForTableSize(hash_table, insertion_index);

    list_iterator = DoublyLinkedListBegin(hash_table->array[insertion_index]);

    list_iterator = DoublyLinkedListInsertBefore(list_iterator, data);

    if (DoublyLinkedListEnd(hash_table->array[insertion_index]) == list_iterator)
    {
        return(1);
    }

    return(0);
}


/************************************find********************************/ 

void *HashTableFind(const hash_table_t *hash_table, const void *key)
{
    size_t find_index = 0;
    void *requested_data = NULL;
    dll_iterator_t data_iterator = NULL;
    
    assert(key);
    assert(hash_table);

    find_index = hash_table->hash_function(key);
    find_index = FitForTableSize((hash_table_t *)hash_table, find_index);

    data_iterator = DoublyLinkedListFind(DoublyLinkedListBegin(hash_table->array[find_index]), DoublyLinkedListEnd(hash_table->array[find_index]), hash_table->cmp, key);

    requested_data = DoublyLinkedListGetData(data_iterator);

    if (DoublyLinkedListEnd(hash_table->array[find_index]) != data_iterator)
    {
        DoublyLinkedListPushFront(hash_table->array[find_index], requested_data);

        DoublyLinkedListRemove(data_iterator);
    }

    return(requested_data);
}


/**********************************remove*************************************************/
void HashTableRemove(hash_table_t *hash_table, const void *key)
{
    size_t remove_index = 0;
    dll_iterator_t iterator = NULL;
    dll_iterator_t end_iterator = NULL;
    dll_iterator_t begin_iterator = NULL;

    assert(key);
    assert(hash_table);

    remove_index = hash_table->hash_function(key);
    remove_index = FitForTableSize(hash_table, remove_index);

    begin_iterator = DoublyLinkedListBegin(hash_table->array[remove_index]);
    end_iterator = DoublyLinkedListEnd(hash_table->array[remove_index]);

    iterator = DoublyLinkedListFind(begin_iterator,end_iterator , hash_table->cmp, key);

    if (DoublyLinkedListEnd(hash_table->array[remove_index]) != iterator)
    {
        DoublyLinkedListRemove(iterator);
    }    
}   


/************************************for each********************************/ 

int HashTableForEach(hash_table_t *hash_table, int (*action_func)(void *data, void *param), void *param)
{   
    size_t i = 0;
    int sucsess = 0;

    assert(hash_table);
    assert(action_func);

    for (i = 0; i < hash_table->size && 0 == sucsess; ++i)
    {
        sucsess = DoublyLinkedListForEach(DoublyLinkedListBegin(hash_table->array[i]), DoublyLinkedListEnd(hash_table->array[i]), action_func, param);
    }

    return(sucsess);
}


/************************************count********************************/ 

size_t HashTableSize(const hash_table_t *hash_table)
{   
    size_t count = 0;

    assert(hash_table);

    HashTableForEach((hash_table_t *)hash_table, ActionFuncCount,&count);

    return(count);
}


/********************************Load Factor********************************/

double HashTableLoadFactor(const hash_table_t *hash_table)
{
    size_t filled_index_count = 0;
    double load_factor = 0;
    size_t i = 0;

    for (i = 0; i < hash_table->size; ++i)
    {
        if (1 != DoublyLinkedListIsEmpty(hash_table->array[i]))
        {
            ++filled_index_count;
        }
    }

    load_factor = filled_index_count / hash_table->size;

    return(load_factor);
}


static int ActionFuncCount(void *data, void *param)
{
    UNUSED(data);

    ++*(size_t *)param;

    return (0);
}


void FreeUpTo(hash_table_t *hash_table, size_t index)
{
    size_t i = 0;

    for (i = 0; i < index; ++i)
    {
        DoublyLinkedListDestroy(hash_table->array[i]);
    } 
}

size_t FitForTableSize(hash_table_t *hash_table, size_t hash_function_answer)
{
    return(hash_function_answer % hash_table->size);
}


