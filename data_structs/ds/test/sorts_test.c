/*
	dev : Gilad Kahn
	rev : Vitali
	status: approved
	date: 04.02.22
*/

#include <stdio.h>  /*printf*/
#include <stdlib.h> /*rand*/
#include <time.h>   /*assert*/
#include <limits.h> /*INT_MAX*/
#include <assert.h> /*assert*/


#include "sorts.h"
#include "utilities.h"



#define ARRAY_SIZE 50
#define ARRAY_SIZE_BIG 5000


void TestBinarySearch(int *array, size_t array_size, int desired_number, size_t answer);
void TestBinarySearchWithLoop(int *array, size_t array_size, int desired_number, size_t answer);


static void FillRandom(int *array, size_t len)
{
    size_t i = 0;

    for (i = 0; i < len;++i)
    {
        array[i] = (rand()%INT_MAX);
    }
}

static void FillRandom_2(int *array, size_t len)
{
    size_t i = 0;

    for (i = 0; i < len;++i)
    {
        array[i] = (rand()%100);
    }
}
static void FillRandom_3(int *array, size_t len)
{
    size_t i = 0;

    for (i = 0; i < len;++i)
    {
        array[i] = (rand()%1000);
    }
}

static int CompreFunction(const void *pivot, const void *element);


int main()
{   
    clock_t begin = 0;
    clock_t end = 0;
    double time_spent = 0;


    static int array_a[ARRAY_SIZE]={0};
    static int array_b[ARRAY_SIZE]={0};
    static int array_c[ARRAY_SIZE]={0};
    static int array_d[ARRAY_SIZE]={0};
    static int array_e[ARRAY_SIZE]={0};
    static int array_f[ARRAY_SIZE]={0};
    static int array_g[ARRAY_SIZE]={0};
    static int array_h[10] = {1 ,2 ,3, 5, 6, 9, 12, 15, 22, 25};
    size_t i = 0;

    FillRandom(array_a, ARRAY_SIZE);
    FillRandom(array_b, ARRAY_SIZE);
    FillRandom(array_c, ARRAY_SIZE);
    FillRandom_2(array_d, ARRAY_SIZE);

    FillRandom_3(array_e, ARRAY_SIZE);
    FillRandom_2(array_f, ARRAY_SIZE);
    FillRandom_2(array_g, ARRAY_SIZE);


    BubbleSort(array_a, ARRAY_SIZE);
    InsertionSort(array_b, ARRAY_SIZE);
    SelectionSort(array_c, ARRAY_SIZE);
    CountingSort(array_d, ARRAY_SIZE);

    array_d[50] = -10;
    array_d[1500] = -19;
  
    /*
    RadixSort(array_e, ARRAY_SIZE);
    */
    TIME_CHECK(QuickSort(array_f, ARRAY_SIZE, sizeof(int), CompreFunction));
    printf("quick sort Elapsed time: %f seconds\n",time_spent);

    MergeSort(array_g, ARRAY_SIZE);


    printf("sorting tests: \n");

    

    for (i = 0; i < ARRAY_SIZE - 1; ++i)
    {
        if (array_a[i] > array_a[i + 1])
        {
            printf("error in bubble_sort \n");
            printf("%ld", i);
        }

        if (array_b[i] > array_b[i + 1])
        {
            printf("error in insertion sort \n");
            printf("%ld", i);
        }

        if (array_c[i] > array_c[i + 1])
        {
            printf("error in selection sort \n");
            printf("%ld", i);
        }

        if (array_d[i] > array_d[i + 1])
        {
            printf("error in counting sort \n");
            printf(" i= %ld  array[i] = %d \t array[i+1] = %d \n", i,array_d[i], array_d[i+1]);
        }
    /*
        if (array_e[i] > array_e[i + 1])
        {
            printf("error in radix sort \n");

            printf("i = %ld  array[i] = %d \n", i ,array_e[i]);
        }
    */
        if (array_f[i] > array_f[i + 1])
        {
            printf("error in quick sort \n");

             printf("i = %ld  array[i] = %d \n", i ,array_f[i]);
        }

        if (array_g[i] > array_g[i + 1])
        {
            printf("error in merge sort \n");

            printf("i = %ld  array[i] = %d \n", i ,array_g[i]);
        }

    }

    TestBinarySearch(array_h, 10, 9, 5);
    TestBinarySearchWithLoop(array_h, 10, 9, 5);

    return(0);
}




static int CompreFunction(const void *pivot, const void*element)
{
    assert(pivot);
    assert(element);

    return(*(int*)pivot - *(int*)element);
}

/*
quick sort with optimization: 0.109747 
quick sort without optimization: 0.110111
system quick sort : 0.009252 
*/

void TestBinarySearch(int *array, size_t array_size, int desired_number, size_t answer)
{
    size_t result = BinarySearch(array, 0, array_size - 1, desired_number);

    if (result != answer)
    {
        printf("error in recrusive search \n");
    }

}

void TestBinarySearchWithLoop(int *array, size_t array_size, int desired_number, size_t answer)
{
    size_t result = BinarySearchWithLoop(array, array_size, desired_number);

    if (result != answer)
    {
        printf("error in iterative search \n");
    }
}
/*
*/

