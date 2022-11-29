


#include <stdio.h>  /*size_t, for, while*/
#include <stdlib.h> /*malloc, free*/
#include <assert.h> /*assert*/

#include "doubly_linked_list.h"
#include "sorted_list.h"

struct sorted_list
{
    dll_t *list;
    int (*cmp)(const void*, const void*);
};

typedef struct cmp_struct
{
	int (* cmp)(const void *data, const void *func_struct);
	void *data;
}cmp_t;


static int IsBiger(const void *data, const void *param);




sorted_list_t *SortedLinkedListCreate(int(*cmp)(const void* data1, const void* data2))
{	
	sorted_list_t *new_list = (sorted_list_t *)malloc(sizeof(sorted_list_t));
	
	assert (cmp);
	
	if (NULL == new_list)
	{
		return (NULL);
	}
	
	new_list -> list = DoublyLinkedListCreate();
	
	if (NULL == new_list -> list)
	{	
		free (new_list);
		return (NULL);
	}
	
	new_list -> cmp = cmp;
	
	return (new_list);
}


void SortedLinkedListDestroy(sorted_list_t *list)
{
	assert (list);
	
	DoublyLinkedListDestroy (list -> list);
	
	list -> list = NULL;
	
	free (list); 
}




int SortedLinkedListIsEmpty(const sorted_list_t *list)
{	
	assert (list);
	
	return (DoublyLinkedListIsEmpty(list -> list));
}






sorted_list_iterator_t SortedLinkedListBegin(const sorted_list_t *list)
{	
	sorted_list_iterator_t convert_iter;		
	
	assert (list);
	
	convert_iter.doubly_iter = DoublyLinkedListBegin(list -> list);

#ifndef NDEBUG
	convert_iter.list = (sorted_list_t*)list;
#endif

	return (convert_iter);
}





sorted_list_iterator_t SortedLinkedListEnd(const sorted_list_t *list)
{	
	sorted_list_iterator_t convert_iter; 			
	
	assert (list);
	
	convert_iter.doubly_iter = DoublyLinkedListEnd(list -> list);
	

#ifndef NDEBUG
	convert_iter.list = (sorted_list_t*)list;
#endif

	
	return (convert_iter);
}


size_t SortedLinkedListSize(const sorted_list_t *list)
{
	assert (list);
	
	return (DoublyLinkedListSize(list -> list));
}



sorted_list_iterator_t SortedLinkedListNext(const sorted_list_iterator_t iterator)
{
	sorted_list_iterator_t convert_iter; 			
	
	convert_iter.doubly_iter = DoublyLinkedListNext(iterator.doubly_iter);
	

		
	return (convert_iter);		
}


sorted_list_iterator_t SortedLinkedListPrev(const sorted_list_iterator_t iterator)
{
	sorted_list_iterator_t convert_iter; 			
	
	convert_iter.doubly_iter = DoublyLinkedListPrev(iterator.doubly_iter);
	
	return (convert_iter);		
}


int SortedLinkedListSameIter(const sorted_list_iterator_t iterator1,const sorted_list_iterator_t iterator2)
{
	int answer = DoublyLinkedListSameIter(iterator1.doubly_iter, iterator2.doubly_iter);		
	
	return (answer);
}

sorted_list_iterator_t SortedLinkedListFind(sorted_list_t *list,sorted_list_iterator_t from, sorted_list_iterator_t to, const void *data)
{
	sorted_list_iterator_t runner = from;
	int sucsess = 0;
	
	
	assert (list);
	
#ifndef NDEBUG
	assert (to.list == list);
/*	assert (from.list == list);*/
#endif
	
	while (1 != SortedLinkedListSameIter(runner, to))
	{	
		sucsess = (list -> cmp)(SortedLinkedListGetData(runner), data);
	
		if (0 == sucsess)
		{
			return (runner);
		}
		
		runner = SortedLinkedListNext(runner);
	}
	
	return (SortedLinkedListEnd(list));
} 	


sorted_list_iterator_t SortedLinkedListFindIf(sorted_list_iterator_t from, sorted_list_iterator_t to, int (*match_func)(const void *data, const void *param),const void *param)
{	
	sorted_list_iterator_t desired_iterator;
	
	assert (match_func);
		
	desired_iterator.doubly_iter = DoublyLinkedListFind(from.doubly_iter ,to.doubly_iter , match_func, param); /*param -not runner*/
	
	
	return(desired_iterator);
}




sorted_list_iterator_t SortedLinkedListInsert(sorted_list_t *list, void *data)
{
	sorted_list_iterator_t convert_iter;
	sorted_list_iterator_t next_iter; 	 			
	
	cmp_t cmp_func;
	
	cmp_func.data = data;
	cmp_func.cmp = list -> cmp;
	
	
/*	next_iter.doubly_iter = DoublyLinkedListFind(DoublyLinkedListBegin(list -> list),DoublyLinkedListEnd(list -> list), IsBiger,&cmp_func);
*/
	next_iter = SortedLinkedListFindIf(SortedLinkedListBegin(list),SortedLinkedListEnd(list), IsBiger,&cmp_func);
	
	convert_iter.doubly_iter = DoublyLinkedListInsertBefore(next_iter.doubly_iter, data);
	
	if (NULL == convert_iter.doubly_iter)
	{	
		free(next_iter.doubly_iter);
		return(SortedLinkedListEnd(list));
	}
	
	
#ifndef NDEBUG
	convert_iter.list = list;
#endif
	
	return (convert_iter);	
}


sorted_list_iterator_t SortedLinkedListRemove(sorted_list_iterator_t iterator)
{	
	sorted_list_iterator_t next_iterator = SortedLinkedListNext(iterator);
	
	DoublyLinkedListRemove(iterator.doubly_iter);
	
	return (next_iterator);
}


void *SortedLinkedListGetData(const sorted_list_iterator_t iterator)
{
	void *data = DoublyLinkedListGetData(iterator.doubly_iter);
	
	return (data);
}




void *SortedLinkedListPopFront(sorted_list_t *list)
{
	void * data = NULL;
	
	assert (list);
	
	data = SortedLinkedListGetData(SortedLinkedListBegin(list));
	
	SortedLinkedListRemove(SortedLinkedListBegin(list));
	
	return (data);
}


void *SortedLinkedListPopBack(sorted_list_t *list)
{
	void * data = NULL;
	sorted_list_iterator_t before_last;
	
	assert (list);
	
	before_last = SortedLinkedListPrev(SortedLinkedListEnd(list));
	
	data = SortedLinkedListGetData(before_last);
	
	SortedLinkedListRemove(before_last);
	
	return (data);
}

int SortedLinkedListForEach(sorted_list_iterator_t from, sorted_list_iterator_t to, int (*action_func)(void *data, void *param), void *param)
{
	return (DoublyLinkedListForEach(from.doubly_iter, to.doubly_iter, action_func, param));
}


void SortedLinkedListMerge(sorted_list_t *dest, sorted_list_t *src)
{
	sorted_list_iterator_t from;
	sorted_list_iterator_t to;
	sorted_list_iterator_t where;
	sorted_list_iterator_t runner;
	sorted_list_iterator_t next;
	
	void *param = NULL;
	
	cmp_t cmp_func;
	
	
	assert (dest);
	assert (src);
	
	cmp_func.cmp = dest -> cmp;
	
	from = SortedLinkedListBegin(src);
	
	runner = from;
	
	to = SortedLinkedListEnd(src);
	
	where = SortedLinkedListBegin(dest);
		
	while (1 != SortedLinkedListSameIter(runner,to))
	{
		next = SortedLinkedListNext(runner);
		param = SortedLinkedListGetData(runner);
		cmp_func.data = param;
		
	/*	printf ("b = %d \n", *(int*)SortedLinkedListGetData(where));*/
	
		if(1 != SortedLinkedListSameIter(where,SortedLinkedListEnd(dest)))
		{
		
		
			where = SortedLinkedListFindIf(where,SortedLinkedListEnd(dest), IsBiger ,&cmp_func);

		}
		 
		DoublyLinkedListSplice(where.doubly_iter, runner.doubly_iter, next.doubly_iter);
		
#ifndef NDEBUG
		runner.list = dest;
#endif

		runner = next;
	}
}


static int IsBiger(const void *data, const void *param)
{
	cmp_t *cmp_bigger = (cmp_t *)param;
    if (0 < cmp_bigger -> cmp(cmp_bigger -> data, data))
    {
        return 0;
    }
    
    else
    {
        return 1;
    }
}


