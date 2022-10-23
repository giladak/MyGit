/*
	dev : Gilad Kahn
	rev : Daniel Gabay
	status: approved
	date: 16.02.22
*/


#include <stdio.h> /*for*/
#include <assert.h> /*assert*/
#include <string.h> /*strncmp*/

#include "recursion.h"
#include "utilities.h"
#include "stack.h"
#include "sorts.h"

int FibonacciWithLoop (int element_index);




static void StackSortInsert(stack_t *stack, int key_data);



int Fibonacci (int element_index)
{
    static int current_element = 0;
    static int next_elememt = 1;
    int temp = 0;


    if (0 != element_index)
    {

    temp = current_element + next_elememt;

    current_element = next_elememt;

    next_elememt = temp;

    return (Fibonacci(element_index - 1));

    }

    temp = current_element;
    current_element = 0;
    next_elememt = 1;

    return (temp);
}

int FibonacciWithLoop (int element_index)
{
    int temp = 0;
    int current_element = 0;
    int next_elememt = 1;
    int i = 0;

    for (i = 0; i < element_index; ++i)
    {
        temp = current_element + next_elememt;

        current_element = next_elememt;

        next_elememt = temp;
    }

    return(current_element);
}


/******************************************flip****************/

node_t *FlipList(node_t *node)
{
    node_t *list_new_head = NULL;

    assert(node);

    if (node->next == NULL)
    {
        return node;
    }
    
    list_new_head = FlipList(node->next);

    node->next->next = node;
    node->next = NULL;

    return list_new_head;
}

/******************************************Strlen****************/


size_t Strlen(const char *s)
{
    static size_t count = 0;
    size_t answer = 0;

    assert(s);

    if ('\0' == *s)
    {   
        answer = count;
        count = 0;

        return (answer);
    }

    ++count;

    return (Strlen(++s));
}

/******************************strcmp****************/

int Strcmp(const char *s1, const char *s2)
{
    assert (s1);
    assert (s2);

    if ('\0' == *s1 || *s1 != *s2)
    {
        return(*s1 - *s2);
    }

    return(Strcmp(++s1, ++s2));

}


char* Strcpy(char *dest, const char *src)
{
    static size_t count = 0;
    size_t src_len = 0;

    assert(dest);
    assert(src);

    if ('\0' == *src)
    {
       *dest = *src;

        src_len = count;
        count = 0;

       return (dest - src_len); 
    }

    *dest = *src;

    ++count;

    return (Strcpy(++dest, ++src));
}

char* Strstr(const char *haystack, const char *needle)
{
    assert(haystack);
    assert(needle);
    
    if ('\0'== *haystack)
    {
        return(NULL);
    }

    if (0 == strncmp(haystack, needle, strlen(needle)))
    {
        return((char *)haystack);
    }

    return(Strstr(++haystack, needle));
}


char* Strcat(char *dest, const char *src)
{   
    static size_t count = 0;
    static int before_null_byte = TRUE; 
    size_t dest_len = 0;

    assert(dest);
    assert(src);


    if ('\0' == *src)
    {
        *dest = *src;

        before_null_byte = TRUE;
        dest_len = count;
        count = 0;

        return (dest - dest_len);
    }

    if('\0' == *dest || FALSE == before_null_byte)
    {   
        *dest = *src;
        ++count;
        before_null_byte = FALSE;

        return(Strcat(++dest, ++src));
    } 
    
    ++count;

    return(Strcat(++dest, src));

}

void StackSort(stack_t *stack)
{
    int key_data = 0;

    assert(stack);

    if (1 != StackIsEmpty(stack))
    {
        key_data = *(int*)StackPeek(stack);
        StackPop(stack); 
        StackSort(stack);
        StackSortInsert(stack, key_data);
    }
}




static void StackSortInsert(stack_t *stack, int key_data)
{
    int temp = 0;

    assert(stack);

    if (1 == StackIsEmpty(stack) || key_data < *(int*)StackPeek(stack))
    {
       StackPush(stack ,&key_data);
    }

    else 
    {
        temp = *(int*)StackPeek(stack);
        StackPop(stack);

        StackSortInsert(stack, key_data);
        StackPush(stack, &temp); 
    }
}