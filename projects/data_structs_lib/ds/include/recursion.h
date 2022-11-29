#ifndef RECURSIV_H
#define RECURSIV_H

#include <stddef.h>/*size_t*/

#include "stack.h"

typedef struct Node 
{
    int data;
    struct Node* next;
}node_t;

int Fibonacci(int element_index);

int FibonacciWithLoop (int element_index);

void StackSort (stack_t *stack);

node_t* FlipList(node_t* node);

size_t Strlen(const char *s);
int Strcmp(const char *s1, const char *s2);
char* Strcpy(char *dest, const char *src);
char* Strcat(char *dest, const char *src);
char* Strstr(const char *haystack, const char *needle);


#endif /*RECURSIV_H*/