

#include <stdio.h>

#include "rec_binary_tree.h"
#include "utilities.h"


#define TEST_SAMPLE 50000


static void RecBinaryTreeTests(void);
static void TestHeight(size_t answer, rec_binary_tree_t *tree);
static void TestIsEmpty(int answer, rec_binary_tree_t *tree);
static void TestCount(size_t answer, const rec_binary_tree_t *tree);
static void TestInsert(rec_binary_tree_t *tree, void *data);
static void TestRemove(void *data, rec_binary_tree_t *tree);
static void TestFind (void *answer, rec_binary_tree_t *tree, void *data);
static void TestForEach (size_t count_answer , rec_binary_tree_t *tree);
static int ActionFuncCount(void *data, void *param);
static void TestAvlBalance ();
static int ComapreFunc(const void *compare_data, const void *runner_data)
{	 

	if (NULL == runner_data)
	{
		return(-1);
	}

	return (*(int*)compare_data - *(int*)runner_data);
}


static void TestAvlBalance ()
{	
	rec_binary_tree_t *test = NULL;
	rec_binary_tree_t *test2 = NULL;
	size_t i = 0;
	static int array[TEST_SAMPLE];
	static int array_2[TEST_SAMPLE];

	test = RecBinaryTreeCreate(ComapreFunc);
	test2 = RecBinaryTreeCreate(ComapreFunc);

	for (i = 0; i < TEST_SAMPLE; ++i)
	{
		array[i] = i;
		RecBinaryTreeInsert(test, &array[i]);
	}

	printf ("inserton 1 completed: \n");


	for (i = 0; i < TEST_SAMPLE; ++i)
	{
		array_2[i] = i;
		RecBinaryTreeInsertWithoutBalance(test2, &array_2[i]);
	}

	printf ("inserton 2 completed: \n");


	RecBinaryTreeFind(test, &array[TEST_SAMPLE - 1]);
	printf ("find with avl completed \n");

	RecBinaryTreeFind(test2, &array_2[TEST_SAMPLE - 1]);
	printf ("find without avl completed \n");
}



void RecBinaryTreeTests(void)
{
	rec_binary_tree_t *test = NULL;

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


	printf ("recursive binary tree tests: \n");

	test = RecBinaryTreeCreate(ComapreFunc);

	TestCount(0, test);
	TestForEach(0, test);
	TestHeight(0, test);

	TestFind(NULL, test, &a);

	TestIsEmpty(1, test);

	TestInsert(test, &A);
	TestCount(1, test);

	TestInsert(test, &b);
	TestInsert(test, &c);
	TestInsert(test, &C);
	TestInsert(test, &a);

	TestCount(5, test);
	

	TestInsert(test, &e);
	TestInsert(test, &d);
	TestInsert(test, &B);
	TestInsert(test, &D);

	TestFind(&b, test, &b);

	TestCount(9, test);
	TestForEach(9, test);

	TestInsert(test, &E);

	TestCount(10, test);
	
	TestRemove(&C, test);
	TestRemove(&D, test);
	TestRemove(&E, test);

	TestCount(7, test);
	TestForEach(7, test);

	RecBinaryTreeDestroy(test);
}




int main()
{

	RecBinaryTreeTests();

	TestAvlBalance ();

	return (0);
}





static void TestIsEmpty(int answer, rec_binary_tree_t *tree)
{	
	static size_t testnum = 1;

	if (answer != RecBinaryTreeIsEmpty(tree))
	{
		printf("error in IsEmpty test %ld  \n", testnum);

	}

	++testnum;
}

static void TestInsert (rec_binary_tree_t *tree, void *data)
{
	static size_t testnum = 1;
	RecBinaryTreeInsert(tree, data);

	if (data != RecBinaryTreeFind(tree, data))
	{
		printf("error in insert test %ld  \n", testnum);
	}

	++testnum;

}


static void TestFind (void *answer, rec_binary_tree_t *tree, void *data)
{
	static size_t testnum = 1;

	if (answer != RecBinaryTreeFind(tree, data))
	{
		printf("error in Find test %ld \n", testnum);

	}

	++testnum;
}

static void TestRemove (void *data,rec_binary_tree_t *tree)
{
	static size_t testnum = 1;

	RecBinaryTreeRemove(tree, data);

	if (NULL != RecBinaryTreeFind(tree, data))
	{
		printf("error in remove test %ld  \n", testnum);

	}
	++testnum;
}

static void TestCount(size_t answer, const rec_binary_tree_t *tree)
{
	static size_t testnum = 1;

	if (answer != RecBinaryTreeCount(tree))
	{
		printf("error in Count test %ld  \n", testnum);
		printf("worng count is %ld  \n", RecBinaryTreeCount(tree));
	}

	++testnum;
}



static void TestForEach (size_t count_answer , rec_binary_tree_t *tree)
{
	size_t count_1 = 0;
	size_t count_2 = 0;
	size_t count_3 = 0;

    RecBinaryTreeForEach((rec_binary_tree_t *)tree, ActionFuncCount, &count_1, PRE_ORDER);
	RecBinaryTreeForEach((rec_binary_tree_t *)tree, ActionFuncCount, &count_2, IN_ORDER);
	RecBinaryTreeForEach((rec_binary_tree_t *)tree, ActionFuncCount, &count_3, POST_ORDER);

	if (count_1 != count_answer)
	{
		printf("error in Pre Order \n");
	}

	if (count_2 != count_answer)
	{
		printf("error in in Order \n");
	}

	if (count_3 != count_answer)
	{
		printf("error in Post Order \n");
	}

}



static int ActionFuncCount(void *data, void *param)
{   
	UNUSED(data);

	++*(size_t*)param;
		
	return (0);
}








static void TestHeight(size_t answer, rec_binary_tree_t *tree)
{
	static size_t testnum = 1;

	if (answer != RecBinaryTreeHeight(tree))
	{
		printf("error in Height test %ld  \n", testnum);
		printf("Height is %ld  \n", RecBinaryTreeHeight(tree));
	}

	++testnum;
}


