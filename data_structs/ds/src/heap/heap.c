/*
	dev :
	rev :
	status:
	date:
*/

#include <stdio.h>	/*for*/
#include <stdlib.h> /*malloc*/
#include <assert.h> /*assert*/
#include <string.h>

#include "utilities.h"
#include "heap.h"
#include "dvector.h"

#define HEAP_STRUCT_SIZE sizeof(heap_t)

#define LEFT 0
#define RIGHT 1

struct heap
{
	int (*cmp)(const void *data1, const void *data2);
	vector_t *vector;
};

/***********************help functions declerations******************************/

static void HeapifyUp(heap_t *heap);
static void HeapifyDown(heap_t *heap, size_t index);

static size_t CalculateParentIndex(size_t current_index);
static size_t CalculateChildIndex(size_t current_index, int side);
static int FindIndex (heap_t *heap, int(*is_matched)(const void *data, const void *param), const void *param);

static void GenericSwap(void *p1, void *p2, size_t size);

/***********************heap create******************************/
heap_t *HeapCreate(int (*cmp)(const void *data1, const void *data2), size_t capacity)
{
	heap_t *new_heap = NULL;

	assert(cmp);

	new_heap = (heap_t *)malloc(HEAP_STRUCT_SIZE);

	if (NULL == new_heap)
	{
		return (NULL);
	}

	new_heap->cmp = cmp;

	new_heap->vector = DVectorCreate(capacity, sizeof(void *));

	if (NULL == new_heap->vector)
	{
		free(new_heap);

		return (NULL);
	}

	return(new_heap);
}

/***********************Destroy******************************/
void HeapDestroy(heap_t *heap)
{
	assert(heap);

	DVectorDestroy(heap->vector);

	free(heap);
}

/***********************Size******************************/
size_t HeapSize(const heap_t *heap)
{
	assert(heap);

	return (DVectorSize(heap->vector));
}

/***********************IsEmpty******************************/
int HeapIsEmpty(const heap_t *heap)
{
	assert(heap);

	return (0 == HeapSize(heap));
}

/***********************Push******************************/
int HeapPush(heap_t *heap, void *element)
{	
	void *element_ptr = NULL;
	assert(heap);
	assert(element);

	element_ptr = &element;

	DVectorPushBack(heap->vector, element_ptr);

	HeapifyUp(heap);

	return (0);
}

/***********************Peek******************************/
void *HeapPeek(const heap_t *heap)
{	
	void **ptr_to_ptr = NULL; 

	assert(heap);

	ptr_to_ptr = DVectorGetAt(heap->vector, 0);

	return (*ptr_to_ptr);
}


/***********************Pop******************************/
void HeapPop(heap_t *heap)
{	
	assert(heap);

	GenericSwap(DVectorGetAt(heap->vector, 0),DVectorGetAt(heap->vector, HeapSize(heap) - 1), POINTER_SIZE);

	DVectorPopBack(heap->vector);

	HeapifyDown(heap, 0);
}

/***********************Remove******************************/

void *HeapRemove(heap_t *heap, int(*is_matched)(const void *data, const void *param), const void *param)
{
	int index = 0;
	void *data = NULL;
	void **ptr_to_ptr = NULL;

	assert (heap);
	assert (is_matched);

	index = FindIndex(heap, is_matched, param);

	if (-1 == index)
	{
		return(NULL);
	}

	ptr_to_ptr = DVectorGetAt(heap->vector, index);

	data = *ptr_to_ptr;

	GenericSwap(DVectorGetAt(heap->vector, index),DVectorGetAt(heap->vector, HeapSize(heap) - 1), POINTER_SIZE);

	DVectorPopBack(heap->vector);

	HeapifyDown(heap, index);

	return(data);
}


/***********************help functions******************************/

static void HeapifyUp(heap_t *heap)
{
	size_t current_index = 0;
	size_t parent_index = 0;
	int result = 0;
	void **parent_data = NULL;
	void **child_data = NULL;

	assert(heap);

	current_index = DVectorSize(heap->vector) - 1;

	if (0 != current_index)
	{
		child_data = DVectorGetAt(heap->vector, current_index);
		parent_index = CalculateParentIndex(current_index);
		parent_data = DVectorGetAt(heap->vector, parent_index);

		result = heap->cmp(*child_data, *parent_data);
	}


	while (0 != current_index && result > 0)
	{
		parent_index = CalculateParentIndex(current_index);
		parent_data = DVectorGetAt(heap->vector, parent_index);

		result = heap->cmp(*child_data, *parent_data);

		if (result > 0)
		{
			GenericSwap(parent_data, child_data, POINTER_SIZE);
		}
		current_index = parent_index;
		child_data = parent_data;
	}
}
/*
static void Heapifydown(heap_t *heap, size_t index)
{
	void **remove_data = NULL;
	void **left_child_data = NULL; 
	void **right_child_data = NULL;
	size_t right_child_index = 0;
	size_t left_child_index = 0;
	size_t end_index = 0;
	int result = 0;

	assert(heap);

	end_index = HeapSize(heap) - 1;
	right_child_index = CalculateChildIndex(index, RIGHT);
	left_child_index = CalculateChildIndex(index, LEFT);
	right_child_data = DVectorGetAt(heap->vector,right_child_index);
	left_child_data = DVectorGetAt(heap->vector,left_child_index);
	remove_data = DVectorGetAt(heap->vector,index);


	while (left_child_index <= end_index)
	{	
		result = heap->cmp(right_child_data, left_child_data);

		if (result > 0)							
		{
			GenericSwap(remove_data, right_child_data, POINTER_SIZE);

			index = right_child_index;
			right_child_index = CalculateChildIndex(index, RIGHT);
			left_child_index = CalculateChildIndex(index, LEFT);

			remove_data = right_child_data;
			right_child_data = DVectorGetAt(heap->vector,right_child_index);
			left_child_data = DVectorGetAt(heap->vector,left_child_index);
		}

		else
		{
			GenericSwap(remove_data, left_child_data, POINTER_SIZE);

			index = left_child_index;
			left_child_index = CalculateChildIndex(index, LEFT);
			right_child_index = CalculateChildIndex(index, RIGHT);
			remove_data = left_child_data;
			
			left_child_data = DVectorGetAt(heap->vector,left_child_index);
			right_child_data = DVectorGetAt(heap->vector,right_child_index);
		}
	}

	GenericSwap(remove_data, DVectorGetAt(heap->vector, end_index), POINTER_SIZE);
}
*/

static void HeapifyDown(heap_t *heap, size_t index)
{
    void **left_child_data = NULL;
    void **right_child_data = NULL;
	size_t right_child_index = 0;
	size_t left_child_index = 0;
    void **largest_data = NULL;
    size_t largest = index;
	size_t size = 0;

	assert(heap);
	
	size = HeapSize(heap);

	right_child_index = CalculateChildIndex(index, RIGHT);
	left_child_index  = CalculateChildIndex(index, LEFT);
	right_child_data  = DVectorGetAt(heap->vector,right_child_index);
	left_child_data   = DVectorGetAt(heap->vector,left_child_index);
	largest_data      = DVectorGetAt(heap->vector,index);

    if (left_child_index < size &&  0 <= heap->cmp(*left_child_data,*largest_data))
    {
        largest = left_child_index;
        largest_data = DVectorGetAt(heap->vector,left_child_index);
    }

    if (right_child_index < size && 0 < heap->cmp(*right_child_data,*largest_data))
    {
        largest = right_child_index;
        largest_data = DVectorGetAt(heap->vector,right_child_index);
    }

    if(largest != index)
    {
        GenericSwap(DVectorGetAt(heap->vector,index), largest_data, POINTER_SIZE);
        HeapifyDown(heap, largest);
    }
}


static size_t CalculateParentIndex(size_t current_index)
{
	current_index = (current_index - 1) / 2;

	return (current_index);
}

void PrintHeap (const heap_t *heap)
{
	size_t i = 0;

	for (i = 0; i <  HeapSize(heap); ++i)
	{
		printf ("%d \n",**(int**)DVectorGetAt(heap->vector, i));
	}

	printf ("\n\n\n");	
}

static void GenericSwap(void *p1, void *p2, size_t size)
{
    char buffer = 0;
    char *tmp1 = (char *)p1;
    char *tmp2 = (char *)p2;
    size_t i = 0;

    for (i = 0; i < size; ++i)
    {
        buffer = *tmp1;
        *tmp1 = *tmp2;
        *tmp2 = buffer;
        ++tmp1;
        ++tmp2;
    }
}

size_t CalculateChildIndex(size_t current_index, int side)
{
	if (RIGHT == side)
	{
		return (2*current_index +1);
	}

	return (2*current_index +2);
}

static int FindIndex (heap_t *heap, int(*is_matched)(const void *data, const void *param), const void *param)
{
	size_t index = 0;
	size_t heap_size = 0;
	int is_match = 0;
	void **ptr_to_ptr = NULL;

	assert(heap);
	assert(is_matched);

	heap_size = HeapSize(heap);

	for (index = 0; index < heap_size; ++index)
	{	

		ptr_to_ptr = DVectorGetAt(heap->vector, index);
		is_match = is_matched(*ptr_to_ptr, param);

		if (1 == is_match)
		{
			break;
		}
	}

	if (is_match != 1)
	{
		return(-1);
	}

	return(index);
}
