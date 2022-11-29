
#include "../include/dvector.h"

#define EMPTY 0
#define FACTOR 2

void TestDVectorDouble(void);
void TestDVectorChar(void);
void TestDVectorInt(void);


void TestDVectordouble(void)
{
	double a = 45.3;
	double b = 107.89;
	size_t test_capacity = 10;
	size_t test_element_size = 8;
	vector_t *test = NULL;

	printf ("DVector functions double tests: \n");


	test = DVectorCreate(test_capacity, test_element_size);
		
	if(test_capacity != DVectorCapacity(test))
	{
		printf ("error in DVectorCapacity test 1\n");
	}
	
	DVectorPushBack(test, &a);
	
	if (a != *(double*)DVectorGetAt(test, 0))
	{
		printf ("error in pushback or GetAt test 1\n");
	}
	
	if (1 != DVectorSize(test))
	{
		printf ("error in DVectorSize test 1\n");
	}
	
	DVectorPushBack(test, &b);
	
	if (b != *(double*)DVectorGetAt(test, 1))
	{
		printf ("error in pushback or GetAt test 2\n");
	}
	
	DVectorPopBack(test);
		
	if (1 != DVectorSize(test))
	{
		printf ("error in DVectorSize test 2\n");
	}
	
	DVectorPushBack(test, &b);
	DVectorPushBack(test, &b);
	DVectorPushBack(test, &b);
	DVectorPushBack(test, &b);
	DVectorPushBack(test, &b);
	DVectorPushBack(test, &b);
	DVectorPushBack(test, &b);
	DVectorPushBack(test, &b);
	DVectorPushBack(test, &b);
	DVectorPushBack(test, &b);
	
	if (test_capacity*FACTOR != DVectorCapacity(test))
	{
		printf ("error in DVectorReserve test 1\n");
		printf ("%ld\n",DVectorCapacity(test));
	}
	
	DVectorPopBack(test);
	DVectorPopBack(test);
	DVectorPopBack(test);
	DVectorPopBack(test);
	
	DVectorShrink(test);
	
	if (test_capacity != DVectorCapacity(test))
	{
		printf ("error in DVectorShrink test 1\n");
		printf ("%ld\n",DVectorCapacity(test));
	}	
	
	DVectorDestroy(test);
}




int main ()
{	
	TestDVectorInt();
	TestDVectorChar();
	TestDVectordouble();

	return (0);
}



void TestDVectorInt(void)
{
	int a = 5;
	int b = 10;
	size_t test_capacity = 5;
	size_t test_element_size = 4;
	vector_t *test = NULL;

	printf ("DVector functions int tests: \n");
	
	test = DVectorCreate(test_capacity, test_element_size);
		
	if(test_capacity != DVectorCapacity(test))
	{
		printf ("error in DVectorCapacity test 1\n");
	}
	
	DVectorPushBack(test, &a);
	
	if (a != *(int*)DVectorGetAt(test, 0))
	{
		printf ("error in pushback or GetAt test 1\n");
	}
	
	if (1 != DVectorSize(test))
	{
		printf ("error in DVectorSize test 1\n");
	}
	
	DVectorPushBack(test, &b);
	
	if (b != *(int*)DVectorGetAt(test, 1))
	{
		printf ("error in pushback or GetAt test 2\n");
	}
	
	DVectorPopBack(test);
		
	if (1 != DVectorSize(test))
	{
		printf ("error in DVectorSize test 2\n");
	}
	
	DVectorPushBack(test, &b);
	DVectorPushBack(test, &b);
	DVectorPushBack(test, &b);
	DVectorPushBack(test, &b);
	DVectorPushBack(test, &b);
	
	if (test_capacity*FACTOR != DVectorCapacity(test))
	{
		printf ("error in DVectorReserve test 1\n");
		printf ("%ld\n",DVectorCapacity(test));
	}
	
	DVectorPopBack(test);
	DVectorPopBack(test);
	DVectorPopBack(test);
	
	DVectorShrink(test);
	
	if (test_capacity != DVectorCapacity(test))
	{
		printf ("error in DVectorShrink test 1\n");
		printf ("%ld\n",DVectorCapacity(test));
	}	
	
	DVectorDestroy(test);
}



void TestDVectorChar(void)
{
	char a = 'a';
	char b = 'b';
	size_t test_capacity = 10;
	size_t test_element_size = 1;
	vector_t *test = NULL;

	printf ("DVector functions char tests: \n");


	test = DVectorCreate(test_capacity, test_element_size);
		
	if(test_capacity != DVectorCapacity(test))
	{
		printf ("error in DVectorCapacity test 1\n");
	}
	
	DVectorPushBack(test, &a);
	
	if (a != *(char*)DVectorGetAt(test, 0))
	{
		printf ("error in pushback or GetAt test 1\n");
	}
	
	if (1 != DVectorSize(test))
	{
		printf ("error in DVectorSize test 1\n");
	}
	
	DVectorPushBack(test, &b);
	
	if (b != *(char*)DVectorGetAt(test, 1))
	{
		printf ("error in pushback or GetAt test 2\n");
	}
	
	DVectorPopBack(test);
		
	if (1 != DVectorSize(test))
	{
		printf ("error in DVectorSize test 2\n");
	}
	
	DVectorPushBack(test, &b);
	DVectorPushBack(test, &b);
	DVectorPushBack(test, &b);
	DVectorPushBack(test, &b);
	DVectorPushBack(test, &b);
	DVectorPushBack(test, &b);
	DVectorPushBack(test, &b);
	DVectorPushBack(test, &b);
	DVectorPushBack(test, &b);
	DVectorPushBack(test, &b);
	
	if (test_capacity*FACTOR != DVectorCapacity(test))
	{
		printf ("error in DVectorReserve test 1\n");
		printf ("%ld\n",DVectorCapacity(test));
	}
	
	DVectorPopBack(test);
	DVectorPopBack(test);
	DVectorPopBack(test);
	DVectorPopBack(test);
	
	DVectorShrink(test);
	
	if (test_capacity != DVectorCapacity(test))
	{
		printf ("error in DVectorShrink test 1\n");
		printf ("%ld\n",DVectorCapacity(test));
	}	
	
	DVectorDestroy(test);
}





