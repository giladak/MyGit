

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "recursion.h"
#include "stack.h"


void FibonacciTestFunc (int answer, int index);
void FibonacciWithLoopTestFunc (int answer, int index);
void FlipListTestFunc (void);
void TestStrstr();
void TestStrcpy();
void TestStrcmp();
void TestStrlen(size_t answer, char *string);
void TestStrCat(char *answer, char *dest, char *src);
void TestIsStackSorted (stack_t *stack);

char *empty= '\0';
char *abcd = "abcd";
char *abcdefg = "abcdefg";
char *abcdsef = "abcd ef";
char *ef = "ef";
char *EF = "EF";
char *numtest = "12345";
char *sabcd = " abcd";
char *abcds = "abcd ";
char *ABCD = "ABCD";
char *sABCD = "sABCD";
char *ABCe = "ABCe";
char *weird = "&^#^&";

char test1[10] = {'a', 'b', 'c', 'd', '\0'};
char test2[10] = {'e', 'f', 'g', '\0'};
char test3[10] = {'\0'};




int main()
{   
    stack_t *test = NULL;

	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	int e = 5;

	test = StackCreate(10, sizeof(int));

	StackPush(test, &a);
	StackPush(test, &b);
	StackPush(test, &c);
	StackPush(test, &d);
	StackPush(test, &e);

	StackSort(test);

	TestIsStackSorted(test);

    printf ("recursion tests: \n");

    FlipListTestFunc ();

    FibonacciWithLoopTestFunc (0, 0);
    FibonacciWithLoopTestFunc (1, 1); 
    FibonacciWithLoopTestFunc (5, 5); 
    FibonacciWithLoopTestFunc (8, 6);  
    FibonacciWithLoopTestFunc (13, 7);   

    FibonacciTestFunc (0, 0);
    FibonacciTestFunc (1, 1); 
    FibonacciTestFunc (5, 5); 
    FibonacciTestFunc (8, 6);  
    FibonacciTestFunc (13, 7);

    printf ("string tests: \n");

    TestStrlen(5, "hello");
    TestStrlen(1, "h");
    TestStrlen(11, "pretty cool");

    TestStrcmp ();
    TestStrcpy ();
	TestStrstr();

	TestStrCat(test1, test1, abcd);
	TestStrCat(test2, test2, abcd);
	TestStrCat(test3, test3, abcd);

    return(0);
}

void FibonacciTestFunc (int answer, int index)
{
    static int testnum = 1;

    if (answer != Fibonacci(index))
    {
        printf ("error in Fibonacci test %d \n", testnum);
        printf ("answer = %d  worng answer = %d\n", answer, Fibonacci(index));
    }

    ++testnum; 
}


void FibonacciWithLoopTestFunc (int answer, int index)
{
    static int testnum = 1;

    if (answer != FibonacciWithLoop(index))
    {
        printf ("error in FibonacciWithloop test %d \n", testnum);
        printf ("answer = %d  worng answer = %d\n", answer, FibonacciWithLoop(index));
    }

    ++testnum; 
}



void FlipListTestFunc (void)
{
    int a = 5;
	int b = 10;
	int c = 15;
	
	int A = 50;
	int B = 100;
	
	
	node_t *first_node = (node_t*)malloc(sizeof(node_t));
	node_t *second_node = (node_t*)malloc(sizeof(node_t));
	node_t *third_node = (node_t*)malloc(sizeof(node_t));
	node_t *fourth_node = (node_t*)malloc(sizeof(node_t));
	node_t *fifth_node = (node_t*)malloc(sizeof(node_t));

	
	first_node -> next = second_node;
	second_node -> next = third_node;
	third_node -> next = fourth_node;
	fourth_node -> next = fifth_node;
	fifth_node -> next = NULL;
	
	
	first_node -> data = a;
	second_node -> data = b;
	third_node -> data = c;
	fourth_node -> data = A;
	fifth_node -> data = B;
	
	/*******************************flip test********************************************/	
	
	printf ("flip test: \n");
	
	FlipList(first_node);
	
	if(NULL != (first_node -> next))
	{
		printf ("error in flip test 1\n");
	}
	
	if(first_node != (second_node -> next))
	{
		printf ("error in flip test 2 \n");
	}
	
	if(fourth_node != (fifth_node -> next))
	{
		printf ("error in flip test 3 \n");
	}

}


void TestStrlen(size_t answer, char *string)
{
    static int testnum = 1;

    if (answer != Strlen(string))
    {
        printf ("error in Strlen test %d \n", testnum);
        printf ("answer = %ld  worng answer = %ld\n", answer, Strlen(string));
    }

    ++testnum;
}

void TestStrcmp ()
{
	printf ("the function Strcmp: \n");

	if (Strcmp(abcd ,numtest) != strcmp(abcd ,numtest))
	{
		printf ("Error in test1\n");
	} 
	if (Strcmp(abcd, abcd) != strcmp(abcd, abcd))
	{
		printf ("Error in test2\n");
	
	} 
	if (Strcmp(abcd, sabcd) != strcmp(abcd, sabcd))
	{
		printf ("Error in test3\n");
	} 
	if (Strcmp(abcdsef, abcdefg) != strcmp(abcdsef, abcdefg))
	{
		printf ("Error in test4\n");
	} 
	
	if (Strcmp(abcd, weird) != strcmp(abcd, weird))
	{
		printf ("Error in test 5\n");
	} 
}


void TestStrcpy ()
{
	char abcd [25] = {0};
	char abcd_copy [25] = {0};
	char abcdefg [20] = "abcdefg";
	char numtest [20] = "12345";
	char sabcd [20] = {0};
	char sabcd_copy [20] = {0};
	char abcds [20] = {0};
	char abcds_copy [20] = {0};
	


	printf ("the function Strcpy: \n");

	if (0 != strcmp(Strcpy(abcd, abcdefg),strcpy(abcd_copy, abcdefg)))
	{
		printf ("Error in test1 \n");
	}  
	if (0 != strcmp(Strcpy(abcd, abcdefg), strcpy(abcd_copy, abcdefg)))
	{
		printf ("Error in test2 \n");
	} 
	if (0 != strcmp(Strcpy(abcds, abcd), strcpy(abcds_copy, abcd)))
	{
		printf ("Error in test3 \n");
	}
	if (0 != strcmp(Strcpy(sabcd, abcd), strcpy(sabcd_copy, abcd)))
	{
		printf ("Error in test4 \n");
	}
	if (0 != strcmp(Strcpy(abcd, numtest), strcpy(abcd_copy, numtest)))
	{
		printf ("Error in test5 \n");
	}
}


void TestStrstr()
{
	printf ("the function Strstr: \n");

	if (Strstr(abcd, abcd) != strstr(abcd, abcd))
	{
		printf ("Error in test1\n");
	} 
		
	if (Strstr(abcd, abcdsef) != strstr(abcd, abcdsef))
	{
		printf ("Error in test2\n");
	} 
	if (Strstr(abcd, abcdefg) != strstr(abcd, abcdefg))
	{
		printf ("Error in test4\n");
	}
	
	if (Strstr(EF, abcd) != strstr(EF, abcd))
	{
		printf ("Error in test5 \n");
	}

	if (Strstr(abcd, numtest) != strstr(abcd, numtest))
	{
		printf ("Error in test3 \n");
	}
}


void TestStrCat(char *answer, char *dest, char *src)
{
	static int testnum = 1;

    if (dest != Strcat(dest, src))
    {
        printf ("error in Strcat test %d \n", testnum);
		++testnum;
    }

	if (NULL == Strstr(answer, src))
	{
		printf ("error in Strcat test %d \n", testnum);
	}

    ++testnum;
}

void TestIsStackSorted (stack_t *stack)
{
	static int testnum = 1;
	int data = 0;
	int next_data = 0;
	size_t i = 0;

	for (i = 0; i < StackSize(stack); ++i)
	{
		data = *(int*)StackPeek(stack);
		StackPop(stack);
		next_data = *(int*)StackPeek(stack);

		if (data > next_data)
		{
			printf ("error in Stack sort test %d at element %d \n", testnum, data);
		}

		data = next_data;
	}
	++testnum;
}
