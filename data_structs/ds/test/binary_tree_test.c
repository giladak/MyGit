/*
	dev : Gilad Kahn
	rev : Yaniv Sne
	status: approved
	date: 10.2.22
*/

#include <stdio.h>

#include "binary_tree.h"
#include "utilities.h"



static void BinaryTreeTests(void);

static void TestIsEmpty(int answer, binary_tree_t *tree);
static void TestBegin(binary_tree_iterator_t answer, binary_tree_t *tree);
static void TestEnd(binary_tree_iterator_t answer, binary_tree_t *tree);
static void TestNext(const binary_tree_iterator_t answer, const binary_tree_iterator_t iterator);
static void TestPrev(const binary_tree_iterator_t answer, const binary_tree_iterator_t iterator);
static void TestSize(size_t answer, const binary_tree_t *tree);

static void TestIterIsEqual(int answer,const binary_tree_iterator_t iterator_1, const binary_tree_iterator_t iterator_2);
static binary_tree_iterator_t TestInsert (binary_tree_t *tree, void *data); 
static void TestGetData (void *answer, const binary_tree_iterator_t iterator);
static void TestRemove (binary_tree_iterator_t iterator, binary_tree_t *tree);
static void TestFind (binary_tree_iterator_t answer, binary_tree_t *tree, void *data);


static int ComapreFunc(const void *compare_data, const void *runner_data, const void *param)
{	 
	UNUSED(param);

	if (NULL == runner_data)
	{
		return(-1);
	}

	return (*(int*)compare_data - *(int*)runner_data);
}

void BinaryTreeTests(void)
{
	binary_tree_t *test = NULL;

	binary_tree_iterator_t iter_1;
	binary_tree_iterator_t iter_2;
	binary_tree_iterator_t iter_3;
	binary_tree_iterator_t iter_4;



	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	int e = 5;

	int A = 10;
	int B = 20;
	int C = 30;
	int D = 40;
	int E = 50;
	int param = 0;


	printf ("binary tree tests: \n");

	test = BinaryTreeCreate(&ComapreFunc, &param);

	TestIsEmpty(1,test);

	TestSize(0, test);

	iter_1 = TestInsert(test, &a);
	
	TestBegin(iter_1, test);

	TestInsert(test, &E);
	iter_2 = TestInsert(test, &d);
	TestInsert(test, &C);
	iter_4 = TestInsert(test, &e);
	TestInsert(test, &A);
	TestInsert(test, &c);
	TestInsert(test, &B);
	iter_3 = TestInsert(test, &D);


	TestSize(9, test);
	
	TestGetData(&d, iter_2);
	TestFind(iter_2, test, &d);
	TestBegin(iter_1, test);


	TestNext(iter_4, iter_2);
	TestPrev(iter_2, iter_4);
	iter_2 = TestInsert(test, &b);

	TestEnd(BinaryTreeNext(BinaryTreeFind(test, &E)), test);

	TestIterIsEqual(0, iter_1, iter_2);
	TestIterIsEqual(1, iter_1, iter_1);
	TestRemove(iter_1, test);
	TestRemove(iter_3, test);
	TestRemove(iter_2, test);
	TestRemove(iter_4, test);


	BinaryTreeDestroy(test);
}




int main()
{
	BinaryTreeTests();

	return (0);
}

static void TestIsEmpty(int answer, binary_tree_t *tree)
{	
	static size_t testnum = 1;

	if (answer != BinaryTreeIsEmpty(tree))
	{
		printf("error in IsEmpty test %ld  \n", testnum);

	}

	++testnum;
}

static void TestBegin(binary_tree_iterator_t answer, binary_tree_t *tree)
{
	static size_t testnum = 1;

	if (answer != BinaryTreeBegin(tree))
	{
		printf("error in Begin test %ld \n", testnum);
	}

	++testnum;
}

static void TestGetData (void *answer, const binary_tree_iterator_t iterator)
{
	static size_t testnum = 1;

	if (answer != BinaryTreeGetData(iterator))
	{
		printf("error in Get Data test %ld  \n", testnum);

	}

	++testnum;
}

static binary_tree_iterator_t TestInsert (binary_tree_t *tree, void *data)
{
	static size_t testnum = 1;
	binary_tree_iterator_t iterator = BinaryTreeInsert(tree, data);

	if (iterator != BinaryTreeFind(tree, data))
	{
		printf("error in insert test %ld  \n", testnum);

	}

	++testnum;

	return (iterator);
}


static void TestFind (binary_tree_iterator_t answer, binary_tree_t *tree, void *data)
{
	static size_t testnum = 1;

	if (answer != BinaryTreeFind(tree, data))
	{
		printf("error in Find test %ld \n", testnum);

	}

	++testnum;
}

static void TestNext(const binary_tree_iterator_t answer, const binary_tree_iterator_t iterator)
{
	static size_t testnum = 1;

	if (answer != BinaryTreeNext(iterator))
	{
		printf("error in next test %ld  \n", testnum);

	}

	++testnum;
}

static void TestPrev(const binary_tree_iterator_t answer, const binary_tree_iterator_t iterator)
{
	static size_t testnum = 1;

	if (answer != BinaryTreePrev(iterator))
	{
		printf("error in Prev test %ld  \n", testnum);

	}

	++testnum;
}

static void TestEnd(binary_tree_iterator_t answer, binary_tree_t *tree)
{
	static size_t testnum = 1;

	if (answer != BinaryTreeEnd(tree))
	{
		printf("error in end test %ld  \n", testnum);

	}

	++testnum;

}

static void TestIterIsEqual(int answer, const binary_tree_iterator_t iterator_1, const binary_tree_iterator_t iterator_2)
{
	static size_t testnum = 1;

	if (answer != BinaryTreeIterIsEqual(iterator_1, iterator_2))
	{
		printf("error in is equal test %ld  \n", testnum);

	}

	++testnum;
}


static void TestSize(size_t answer, const binary_tree_t *tree)
{
	static size_t testnum = 1;

	if (answer != BinaryTreeSize(tree))
	{
		printf("error in Size test %ld  \n", testnum);
		printf("Size is %ld  \n", BinaryTreeSize(tree));
	}

	++testnum;

}



static void TestRemove (binary_tree_iterator_t iterator,binary_tree_t *tree)
{
	static size_t testnum = 1;
	void *data = BinaryTreeGetData(iterator);


	BinaryTreeRemove(iterator);

	if (NULL != BinaryTreeFind(tree, data))
	{
		printf("error in remove test %ld  \n", testnum);

	}

	++testnum;
}
