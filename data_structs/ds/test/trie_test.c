/*
	dev : Gilad Kahn
	rev : Daniel Gabay
	status: approved
	date: 3.3.22
*/


#include <stdio.h>
#include <string.h> /*strcmp*/

#include "trie.h"
#include "utilities.h"

static void TrieTests(void);

static void TestIsEmpty(trie_t *trie ,int answer);
static void TestCount(const trie_t *trie, size_t answer);
static void TestInsert(trie_t *trie,  char* key,  char *answer);
static void TestRemove(trie_t *trie,  char *key);


static void TrieTests()
{
    trie_t *test = NULL;


    printf("trie tests: \n");

    test = TrieCreate();
    if (NULL == test)
    {
        printf("error in create test 1\n");
    }

    TestIsEmpty(test, TRUE);
    TestCount(test, 0);

    TestInsert(test, "001", "001");
	TestCount(test, 1);

    TestInsert(test, "000", "000");
	TestCount(test, 2);

	TestInsert(test, "111", "111");
	TestCount(test, 3);

	TestInsert(test, "111", "111");
	TestCount(test, 3);	

    TestInsert(test, "001", "010");
	TestCount(test, 4);	

    TestInsert(test, "001", "011");
	TestCount(test, 5);

    TestRemove(test, "111");
	TestCount(test, 4);

	TestRemove(test, "001");
	TestCount(test, 3);

s

    TrieDestroy(test);

}




int main ()
{
    TrieTests();


    return(0);
}

static void TestIsEmpty(trie_t *trie, int answer)
{	
	static size_t testnum = 1;

	if (answer != TrieIsEmpty(trie))
	{
		printf("error in IsEmpty test %ld  \n", testnum);

	}

	++testnum;
}

static void TestInsert (trie_t *trie,  char* key, char *answer)
{
	static size_t testnum = 1;
	char answer_array[20] = {0};
	
	TrieInsert(trie, key, answer_array);

	if (0 != strcmp(answer, answer_array))
	{
		printf("error in insert test %ld  \n", testnum);
		printf("worng answer = %s , expected answer = %s \n", answer_array, answer);
	}

	++testnum;

}


static void TestRemove (trie_t *trie, char* key)
{
	static size_t testnum = 1;
	char insert_answer_array[20] = {0};

	TrieRemove(trie, key);
	TrieInsert(trie, key, insert_answer_array);

	if (0 != strcmp(key, insert_answer_array))
	{
		printf("error in remove test %ld  \n", testnum);
	}
	++testnum;

/*	

/*
	if (TrieCount(trie) != size_before - 1)
	{
		printf("error in remove test %ld  \n", testnum);
	}

	++testnum;

*/
    TrieRemove(trie, key);
}

static void TestCount(const trie_t *trie, size_t answer)
{
	static size_t testnum = 1;

	
	if (answer != TrieCount(trie))
	{
		printf("error in Count test %ld  \n", testnum);
		printf("worng count is %ld  \n", TrieCount(trie));
	}

	++testnum;
}