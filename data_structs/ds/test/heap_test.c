/*
	dev :
	rev : 
	status: 
	date: 
*/

#include <stdio.h>

#include "heap.h"
#include "utilities.h"



static void HeapTests(void);
static void TestIsEmpty(int answer, heap_t *heap);
static void TestSize(size_t answer, const heap_t *heap);
static void TestRemove (void *data, heap_t *heap);
static void TestPush(heap_t *heap, void *data);
static int IsMatchFunc(const void *heap_data, const void *param);


static int IsMatchFunc(const void *heap_data, const void *param)
{	
	return(*(int*)heap_data == *(int*)param);
}


static int ComapreFunc(const void *compare_data, const void *runner_data)
{	 

	if (NULL == runner_data)
	{
		return(-1);
	}

	return (*(int*)compare_data - *(int*)runner_data);
}

void HeapTests(void)
{
	heap_t *test = NULL;

	
	int a_num = 1;
	int b_num = 2;
	int c_num = 3;
	int d_num = 4;
	int e_num = 5;

	int A_num = 10;
	int B_num = 20;
	int C_num = 30;
	int D_num = 40;
	int E_num = 50;






	int *a = &a_num;
	int *b = &b_num;
	int *c = &c_num;
	int *d = &d_num;
	int *e = &e_num;

	int *A = &A_num;
	int *B = &B_num;
	int *C = &C_num;
	int *D = &D_num;
	int *E = &E_num;
	int *param = NULL;

	printf ("heap tests: \n");

	test = HeapCreate(ComapreFunc, 10);

	if (test == NULL)
	{
		printf("error in create \n");
	}

	TestIsEmpty(1,test);

	TestSize(0, test);

	TestPush(test, a);
	TestPush(test, E);
	TestPush(test, d);
	TestPush(test, C);

	
	TestPush(test, e);
	TestPush(test, A);
	TestPush(test, c);
	TestPush(test, B);
	TestPush(test, D);

	PrintHeap(test);

	TestSize(9, test);
/*
	PrintHeap(test);
	HeapPop(test);
	PrintHeap(test);
*/

	TestRemove(a, test);
	TestRemove(A, test);


	HeapDestroy(test);
}




int main()
{
	HeapTests();

	return (0);
}
static void TestIsEmpty(int answer, heap_t *heap)
{	
	static size_t testnum = 1;

	if (answer != HeapIsEmpty(heap))
	{
		printf("error in IsEmpty test %ld  \n", testnum);

	}

	++testnum;
}


static void TestSize(size_t answer, const heap_t *heap)
{
	static size_t testnum = 1;

	if (answer != HeapSize(heap))
	{
		printf("error in Size test %ld  \n", testnum);
		printf("Size is %ld  \n", HeapSize(heap));
	}

	++testnum;

}

static void TestPush (heap_t *heap, void *data)
{
	static size_t testnum = 1;
	size_t size_before_push = HeapSize(heap);

	HeapPush(heap, data);

	if (size_before_push == HeapSize(heap))
	{
		printf("error in Push test %ld  \n", testnum);

	}

	++testnum;
}



static void TestRemove (void *data, heap_t *heap)
{
	static size_t testnum = 1;
	void *answer = NULL;
	size_t size_before_remove = HeapSize(heap);

	answer = HeapRemove(heap, IsMatchFunc, data);

	if (size_before_remove == HeapSize(heap))
	{
		printf("error in remove test %ld  \n", testnum);

	}
	++testnum;

	if (*(int *)answer != *(int*)data)
	{
		printf("error in remove test %ld  \n", testnum);
	}
/*
*/

	++testnum;
}
