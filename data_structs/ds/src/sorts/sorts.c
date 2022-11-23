#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "sorts.h"
#include "utilities.h"

#define RANGE 200
#define RANGE_NEGTIVE 100
#define BASE 10



/***********************help functions******************************/
static void swap (int *num1, int *num2);
static int GetMax(int *arr, size_t size);
static int GetMin(int *arr, size_t size);
static int GetRange(int *arr, size_t size);
static int CountingSortWithPlace(int *arr, size_t size, size_t digit);
static int GetDigit(int num, size_t place);
static char *DoPatrition(size_t size, char *start, char *end, int(*compare)(const void*, const void*));
static void GenericSwap(void *p1, void *p2, size_t size);




/*
	dev : Gilad Kahn
	rev : Vitali
	status: approved
	date: 04.02.22
*/

/***********************bubble sort******************************/
void BubbleSort(int *arr, size_t size)
{
	size_t i = 0;
	size_t change_count = 1;
	size_t stop_run = size - 1;

    assert (arr);
	
	while (0 != change_count)
	{
		change_count = 0;
			
		for (i = 0; i < stop_run; ++i)
		{
			if (arr [i] > arr[i + 1])
			{
				swap(&arr [i], &arr[i + 1]);
				
				++change_count;	
			}
		}
	}
	
}

/*
	dev : Gilad Kahn
	rev : Vitali
	status: approved
	date: 04.02.22
*/

/***********************insertion sort******************************/

void InsertionSort(int *arr, size_t size)
{
    size_t i = 0;
    int j = 0;
    int temp = 0;

    assert (arr);


    for (i = 1; i < size; i++)  
    {
        temp = arr[i];
        j = i - 1;

        while (j >= 0 && temp < arr[j])
        {
            arr[j + 1] = arr[j];
            j -= 1;         
        }

        arr[j + 1] = temp;
    }
}



/*
	dev : Gilad Kahn
	rev : Vitali
	status: approved
	date: 04.02.22
*/
/***********************selection sort******************************/

void SelectionSort(int *arr, size_t size)   
{
    size_t i = 0;
    size_t min_index = 0;
    size_t unsorted_index = 0;

    assert (arr);
    while (unsorted_index < size)
    {

        min_index = unsorted_index;    
        for (i = unsorted_index; i < size;++i)    
        {
            if (arr[i] < arr[min_index])
            {
                  min_index = i;  
            }

        }

        swap (&arr[min_index], &arr[unsorted_index]);

        ++unsorted_index;
    }
}


/*
	dev : Gilad Kahn
	rev : Nimrod Segev
	status: approved
	date: 06.02.22
*/

/***********************countiong sort******************************/


int CountingSort(int *arr, size_t size)
{
    int *count_array = NULL;
    int *output = NULL;
    size_t i = 0;
    int j = 0;
    size_t range = 0;
    int min = 0;

    assert(arr);

    range = GetRange(arr, size);
    min = GetMin(arr, size);

    count_array = (int*)calloc((range + 1),sizeof(int));
    if (NULL == count_array)
    {
         return(1);   
    }

    output = (int*)calloc(size + 1, sizeof(int));

    if (NULL == output)
    {   
        free (count_array);
         return(1);   
    }
    
    for (i = 0; i < size; ++i)   
    {                           
        ++count_array[arr[i] - min];            
    }

    for (i = 1; i <= range; ++i)
    {
        count_array[i] += count_array[i - 1];
    }

    for (j = size - 1; j >= 0;--j)
    {
        output[count_array[arr[j] - min] - 1] = arr[j];
        --count_array[arr[j] - min];
    }

    for (i = 0; i < size; ++i)
    {
       arr[i] = output[i];      
    }

    free (count_array);
    free (output);

    return(0);
}

/***********************radix sort ******************************/


int RadixSort(int *arr, size_t size)
{
    int max = 0;
    size_t place = 1;

    assert(arr);

    max = GetMax(arr, size);

    while (0 != max)
    {
        CountingSortWithPlace(arr, size, place);

       ++place;
       max /= BASE;
    }

    return (0);
}

/***********************Counting Sort With Place ******************************/


static int CountingSortWithPlace(int *arr, size_t size, size_t place)
{
    int count_array[BASE] = {0};
    int *output = NULL;
    size_t i = 0;
    int digit = 0;
    int j = 0;

    assert(arr);

    output = (int*)calloc(size, sizeof(int));
    
    
    for (i = 0; i < size; ++i)
    {   
        digit = GetDigit(arr[i], place);
        ++count_array[digit];            
    }

    for(i = 1; i <= BASE; ++i)
    {
        count_array[i] += count_array[i - 1];
    }

    for (j = size - 1; j >= 0;--j)
    {   
        digit = GetDigit(arr[j], place);

        output[count_array[digit] - 1] = arr[j];
        --count_array[digit];
    }

    for (i = 0; i < size; ++i)
    {
       arr[i] = output[i];      
    }


    free (output);

    return(0);
}


/*
	dev : Gilad Kahn
	rev : Daniel Gabay
	status: approved
	date: 06.02.22
*/

/************************************merge************************************/

int MergeSort(int *arr_to_sort, size_t num_elements)
{
    size_t middle_index = 0;
    int *array1 = NULL;
    int *array2 = NULL;
    size_t i = 0;
    size_t j = 0;


    assert(arr_to_sort);


    if (num_elements > 1)
    {
        array1 = (int *)malloc((num_elements/2 + 1)*sizeof(int));
        if (NULL == array1)
        {
            return(1);
        }

        array2 = (int *)malloc((num_elements/2 + 1)*sizeof(int));
        if (NULL == array2)
        {   
            free(array1);
            return(1);
        }

        middle_index = num_elements / 2;
        memmove(array1, arr_to_sort, middle_index*sizeof(int));
        memmove(array2, &arr_to_sort[middle_index], (num_elements - middle_index)*sizeof(int));
        
        MergeSort(array1, middle_index);
        MergeSort(array2, num_elements - middle_index);

        while(i < middle_index && j < (num_elements - middle_index))
        {
            if (array1[i] <= array2[j])
            {   
                *arr_to_sort = array1[i];
                ++i;
                ++arr_to_sort;

            }

            else
            {
                *arr_to_sort = array2[j];
                ++j;
                ++arr_to_sort;
            }
        }

        while(i < middle_index)
        {
            *arr_to_sort = array1[i];
            ++i;
            ++arr_to_sort;
        }

        while (j < (num_elements - middle_index))
        {
            *arr_to_sort = array2[j];
            ++j;
            ++arr_to_sort;
        }
       
        free(array1);
        free(array2);

    }

    return(0);
}


/************************list merge******/

merge_node_t *ListsMergeSort(merge_node_t *head_1, merge_node_t *head_2)
{
    merge_node_t *merged_list_node = NULL;

    if (NULL == head_1)
    {
        return(head_2);
    }

    else if (NULL == head_2)
    {
        return(head_1);
    }


    if (head_1->data >= head_2->data)
    {
        merged_list_node = head_1;
        merged_list_node->next = ListsMergeSort(head_1->next, head_2);
    }

    else
    {
        merged_list_node = head_2;
        merged_list_node->next = ListsMergeSort(head_1, head_2->next); 
    }


    return(merged_list_node);
}



/*
	dev : Gilad Kahn
	rev : Daniel Gabay
	status: approved
	date: 06.02.22
*/


/*******************************binary search with loop********************************************/

int BinarySearchWithLoop(int *sorted_array, size_t size, int number)
{
    size_t middle = 0;

    middle = size / 2;

    while (size != middle && number != sorted_array[middle])
    {

        if (number > sorted_array[middle])
        {
            middle += (size - middle)/2; 
        }

        if (number < sorted_array[middle])
        {
            size = middle; 
            middle -= middle/2;
        }

    }

    if (number != sorted_array[middle])
    {
        return(-1);
    }

    return(middle);
}



/*
	dev : Gilad Kahn
	rev : Daniel Gabay
	status: approved
	date: 06.02.22
*/


/*******************************binary search********************************************/
int BinarySearch(int *sorted_array, size_t first_index, size_t last_index, int num)
{
    size_t middle = 0;

    middle = (first_index + last_index) / 2;

    if (last_index < first_index)
    {
        return(-1);
    }

    if (sorted_array[middle] > num)
    {
        return(BinarySearch(sorted_array, first_index, middle, num));
    }

    if (sorted_array[middle] < num)
    {
        return(BinarySearch(sorted_array, middle, last_index, num));
    }

    else
    {   
        return(middle);
    }
}


/*
	dev : Gilad Kahn
	rev : Daniel Gabay
	status: approved
	date: 06.02.22
*/


/*************************quick sort *******************/

/********we will first accomplish it all wait ints then change**********/


void QuickSort(void *base, size_t nmemb, size_t size, int(*compare)(const void*, const void*))
{
    char *pivot_location = NULL;
    char *runner = NULL;
    char *end = NULL;
    size_t block_1_size = 0;
    size_t block_2_size = 0;
    
    assert(base);
    assert(compare);


    runner = (char *)base;
    end = runner + nmemb*size;

    if (1 < nmemb)
    {
        pivot_location = DoPatrition(size, runner, end, compare);

        block_1_size = (pivot_location - runner)/size;
        block_2_size = ((end - pivot_location)) / size - 1;
  
        QuickSort(runner, block_1_size, size, compare);
        QuickSort(pivot_location + size, block_2_size , size, compare);
    } 
}




/*******************************help functions*******************************/

static char *DoPatrition(size_t size, char *start, char *end, int(*compare)(const void*, const void*))
{   
    char *pivot = NULL;
    char *patritioned = NULL;
    char *runner = NULL;
    
    assert(compare);
    assert(start);
    assert(end);

    pivot = end - size;
    patritioned = start;
    runner = start;


    while (runner < pivot)
    {
        if (0 < compare(pivot, runner))
        {
            GenericSwap(runner, patritioned, size);
            patritioned += size;
        }

        runner += size;
    }

    GenericSwap(patritioned, pivot, size);

    return(patritioned);
}


/*

    size_t i = 0;
    size_t j = 0;
    int pivot = 0;
    int *array = NULL;

    assert(base);

    array = (int *)base;

    pivot = array[end_index];

    for (j = 0; j < end_index; ++j)
    {
        if (0 < compare(&pivot, &array[j]))
        {
            swap(&array[i], &array[j]);
            ++i;
        }
    }

    swap(&array[end_index], &array[i + 1]);

    return(i + 1);

*/
static void swap (int *num1, int *num2)
{
    int temp = *num1;
    *num1 = *num2;
    *num2 = temp;
}

static int GetMax(int *arr, size_t size)
{
    size_t i = 0;
    int max = 0;

    for (i = 0; i < size; ++i)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }

    return (max);
}


static int GetMin(int *arr, size_t size)
{
    size_t i = 0;
    int min = 0;

    min = arr[0];

    for (i = 0; i < size; ++i)
    {
        if (arr[i] < min)
        {
            min = arr[i];
        }
    }

    return (min);
}

static int GetRange(int *arr, size_t size){


    return (GetMax(arr,size) - GetMin(arr,size));
}


static int GetDigit(int num, size_t place)
{
    size_t i = 0;

   for (i = 1; i < place; ++i)  
    {                               
        num /= BASE;             
    }

    num = num % BASE;

    return(num);
    /*

    return ((num/place)%10);
*/
}


static void GenericSwap(void *p1, void *p2, size_t size)
{
    size_t i = 0;
    unsigned char c = 0;

    assert(NULL != p1);
    assert(NULL != p2);

    for(i = 0; i < size; ++i)
    {
        c = *(unsigned char *)p1;
        *(unsigned char *)p1 = *(unsigned char *)p2;
        *(unsigned char *)p2 = c;
        p1 = (void *)((char *)p1 +1);
        p2 = (void *)((char *)p2 +1);
    }
}
