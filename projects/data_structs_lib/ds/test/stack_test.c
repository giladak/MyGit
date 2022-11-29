#include <stdio.h>  /*printf*/
#include <stdlib.h> /*size_t*/
#include <assert.h> /*assert*/
#include "../include/stack.h"

#define EMPTY 0

void TestStackDouble(void);
void TestStackInt(void);
void TestStackChar(void);



int main ()
{	
	 TestStackDouble();
	 TestStackInt();
 	 TestStackChar();

	return (0);
}

void TestStackInt(void)
{	
	int a = 5;
	int b = 10;
	size_t i = 0;
	size_t test_capacity = 20;
	size_t test_element_size = 4;
	stack_t *test = NULL;

	printf ("stack functions int tests: \n");


	test = StackCreate(test_capacity, test_element_size);
		
	if(test_capacity != StackCapacity(test))
	{
		printf ("error in StackCapacity test 1\n");
	}
	
		
	StackPush(test, &a);
	
	if (a != *(int*)StackPeek(test))
	{
		printf ("error in push or pick test 1\n");
	}
	
	StackPush(test, &b);	
	StackPop(test);
	
	if (a != *(int*)StackPeek(test))
	{
		printf ("error in pop test 1\n");
	}
	
	if(0 != StackIsEmpty(test))
	{
		printf ("error in is empty test 1\n");
	}
	
	
	StackPop(test);
	if(1 != StackIsEmpty(test))
	{
		printf ("error in is empty test 2\n");
	}
	
	StackPush(test, &a);
	StackPush(test, &b);
	
	if (2 != StackSize(test))
	{
		printf ("error in Stack size test 1\n");
	}	
	
	for (i = 2; i < StackCapacity(test); ++i)
	{
		StackPush(test, &i);
		
		if ((i) != 	*(size_t*)StackPeek(test)&& i != StackSize(test))
		{
			printf ("error in loop test 1 \n ");
		}
	}
	
	
	StackDestroy(test);
}


void TestStackDouble(void)
{	
	double a = 5.5;
	double b = 10.48;
	size_t i = 0;
	size_t test_capacity = 30;
	size_t test_element_size = 8;
	stack_t *test = NULL;

	printf ("stack functions double tests: \n");


	test = StackCreate(test_capacity, test_element_size);
		
	if(test_capacity != StackCapacity(test))
	{
		printf ("error in StackCapacity test 1\n");
	}
	
		
	StackPush(test, &a);
	
	if (a != *(double*)StackPeek(test))
	{
		printf ("error in push or pick test 1\n");
	}
	
	StackPush(test, &b);	
	StackPop(test);
	
	if (a != *(double*)StackPeek(test))
	{
		printf ("error in pop test 1\n");
	}
	
	if(0 != StackIsEmpty(test))
	{
		printf ("error in is empty test 1\n");
	}
	
	
	StackPop(test);
	if(1 != StackIsEmpty(test))
	{
		printf ("error in is empty test 2\n");
	}
	
	StackPush(test, &a);
	StackPush(test, &b);
	
	if (2 != StackSize(test))
	{
		printf ("error in Stack size test 1\n");
	}	
	
	for (i = 2; i < StackCapacity(test); ++i)
	{
		StackPush(test, &i);
		
		if ((i) != 	*(size_t*)StackPeek(test)&& i != StackSize(test))
		{
			printf ("error in loop test 1 \n ");
		}
	}
	
	
	StackDestroy(test);
}



void TestStackChar(void)
{	
	char a = 'A';
	char b = 'B';
	size_t i = 0;
	size_t test_capacity = 1;
	size_t test_element_size = 1;
	stack_t *test = NULL;

	printf ("stack functions char tests: \n");


	test = StackCreate(test_capacity, test_element_size);
		
	if(test_capacity != StackCapacity(test))
	{
		printf ("error in StackCapacity test 1\n");
	}
	
		
	StackPush(test, &a);
	
	if (a != *(char*)StackPeek(test))
	{
		printf ("error in push or pick test 1\n");
	}
	
	StackPush(test, &b);	
	StackPop(test);
	
	if (a != *(char*)StackPeek(test))
	{
		printf ("error in pop test 1\n");
	}
	
	if(0 != StackIsEmpty(test))
	{
		printf ("error in is empty test 1\n");
	}
	
	
	StackPop(test);
	if(1 != StackIsEmpty(test))
	{
		printf ("error in is empty test 2\n");
	}
	
	StackPush(test, &a);
	StackPush(test, &b);
	
	if (2 != StackSize(test))
	{
		printf ("error in Stack size test 1\n");
	}	
	
	for (i = 2; i < StackCapacity(test); ++i)
	{
		StackPush(test, &i);
		
		if ((i) != 	*(size_t*)StackPeek(test)&& i != StackSize(test))
		{
			printf ("error in loop test 1 \n ");
		}
	}
	
	
	StackDestroy(test);
}
