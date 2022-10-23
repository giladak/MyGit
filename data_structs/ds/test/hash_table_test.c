/*
	dev : Gilad Kahn
	rev : Tomer Fridman
	status: approved
	date: 21.2.22
*/

#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <assert.h>
#include <ctype.h>


#include "hash_table.h"
#include "utilities.h"

#define PRIME_NUMBER 31
#define EXTRA_SPACE_RATIO 1.25

static void HashTableTests(void);

static void TestIsEmpty(int answer, hash_table_t *hash_table);


static void TestSize(size_t answer, const hash_table_t *hash_table);

static void TestInsert (hash_table_t *hash_table, void *data); 
static void TestRemove (hash_table_t *hash_table, void *data);
static void TestFind (void *answer, hash_table_t *hash_table, void *data);
static int ComapreFunc_1(const void *compare_data, const void *runner_data);
size_t SimpleHashFunction(const void *key);

/******************dictionary functions****************************/

size_t CheckFileSize (FILE *file_ptr);
size_t CheckNumOfLines(FILE *file_ptr);
static int CompareStrings(const void *user_key, const void *table_key);
static size_t DictionaryHashFunction(const void *key);
static void AddNullBytes(char *string);
hash_table_t *InitlizeDictionary();
char *IntilizeBuffer(FILE *file_ptr);
void DictionaryTests();




int main()
{	

	DictionaryTests();
	HashTableTests();

	return (0);
}

void DictionaryTests()
{
	hash_table_t *dictionary = NULL;
	char user_string[20];

	dictionary = InitlizeDictionary();

	printf("please enter a word in english:  \n");

	scanf("%s", user_string);


	if (NULL == HashTableFind(dictionary, user_string))
	{
		printf("the word was spelled incorrectly \n");
	}

	else
	{
		printf("the word was spelled correctly \n");
	}

	HashTableDestroy(dictionary);
}



hash_table_t *InitlizeDictionary()
{
	hash_table_t *dictionary = NULL;
	char *buffer = NULL;
	char *start_buffer = NULL;
	FILE *file_ptr = NULL;
	size_t num_of_words = 0;
	size_t i = 0;

	file_ptr = fopen("/usr/share/dict/words", "r");

	num_of_words = CheckNumOfLines(file_ptr);

	buffer = IntilizeBuffer(file_ptr);

	start_buffer = buffer;

	dictionary = HashTableCreate(num_of_words*EXTRA_SPACE_RATIO, CompareStrings, DictionaryHashFunction);

	for (i = 0; i < num_of_words; ++i)
	{
		HashTableInsert(dictionary, buffer);

		buffer += strlen(buffer) + 1;
	}

	fclose(file_ptr);
	
	free(start_buffer);

	return(dictionary);
}


char *IntilizeBuffer(FILE *file_ptr)
{
	size_t file_size = 0;
	char *buffer = NULL;

	file_size = CheckFileSize(file_ptr);

	fseek(file_ptr, 0, SEEK_SET);

	buffer = (char*)malloc(file_size + 1);

	fread(buffer, 1, file_size, file_ptr);

	buffer[file_size] = '\0';

	AddNullBytes(buffer);

	return(buffer);
}



static void AddNullBytes(char *string)
{
	while ('\0' != *string)
	{
		if ('\n' == *string)
		{
			*string = '\0';
		}

		++string;
	}

}


static int CompareStrings(const void *user_key, const void *table_key)
{
	return(strcasecmp(user_key, table_key));
}


static size_t DictionaryHashFunction(const void *key)
{
    size_t value = 0;
    size_t i = 0;
    size_t key_len = 0;

    assert(NULL != key);

    key_len = strlen((char *)key);

    for (i = 0; i < key_len; ++i) 
    {
        value = value * PRIME_NUMBER + tolower(((char *)key)[i]);
    }

    return value;
}



size_t CheckNumOfLines(FILE *file_ptr)
{	
	size_t lines = 0;
	char current_char = 0;


	fseek(file_ptr, 0, SEEK_SET);


	while(!feof(file_ptr))
	{
		current_char = fgetc(file_ptr);

		if(current_char == '\n')
		{
			lines++;
		}
	}

	fseek(file_ptr, 0, SEEK_SET);

	return(lines);
}


size_t CheckFileSize(FILE *file_ptr)
{	
	fseek(file_ptr,0 ,SEEK_END);

	return (ftell(file_ptr));
}





static void TestIsEmpty(int answer, hash_table_t *hash_table)
{	
	static size_t testnum = 1;

	if (answer != HashTableIsEmpty(hash_table))
	{
		printf("error in IsEmpty test %ld  \n", testnum);

	}

	++testnum;
}




static void TestSize(size_t answer, const hash_table_t *hash_table)
{
	static size_t testnum = 1;

	if (answer != HashTableSize(hash_table))
	{
		printf("error in Size test %ld  \n", testnum);
		printf("Size is %ld  \n", HashTableSize(hash_table));
	}

	++testnum;

}


static void TestInsert (hash_table_t *hash_table, void *data)
{
	static size_t testnum = 1;
	HashTableInsert(hash_table, data);

	if (data != HashTableFind(hash_table, data))
	{
		printf("error in insert test %ld  \n", testnum);

	}

	++testnum;
}



static void TestFind (void *answer, hash_table_t *hash_table, void *data)
{
	static size_t testnum = 1;

	if (answer != HashTableFind(hash_table, data))
	{
		printf("error in Find test %ld \n", testnum);

	}

	++testnum;
}



static void TestRemove (hash_table_t *hash_table, void *data)
{
	static size_t testnum = 1;
	

	HashTableRemove(hash_table, data);

	if (NULL != HashTableFind(hash_table, data))
	{
		printf("error in remove test %ld  \n", testnum);

	}

	++testnum;
}


static int ComapreFunc_1(const void *compare_data, const void *runner_data)
{	
	if (NULL == runner_data)
	{
		return(-1);
	}

	return (*(int*)compare_data - *(int*)runner_data);
}

size_t SimpleHashFunction(const void *key)
{
	return(*(size_t*)key % 10);
}





void HashTableTests(void)
{
	hash_table_t *test = NULL;

	int a = 1;

	int c = 3;
	int d = 4;
	int e = 5;

	int A = 10;
	int B = 20;
	int C = 30;
	int D = 40;
	int E = 50;


	printf ("Hash Table tests: \n");

	test = HashTableCreate(10, ComapreFunc_1, SimpleHashFunction);

	TestIsEmpty(1,test);

	TestSize(0, test);

	TestInsert(test, &a);
	
	TestFind(NULL, test, &E);

	TestInsert(test, &E);
	TestInsert(test, &d);
	TestInsert(test, &C);
	TestInsert(test, &e);
	TestInsert(test, &A);
	TestInsert(test, &c);
	TestInsert(test, &B);
	TestInsert(test, &D);

	TestRemove(test, &B);
	TestRemove(test, &C);


	TestSize(7, test);


	HashTableDestroy(test);
}




/*
*/