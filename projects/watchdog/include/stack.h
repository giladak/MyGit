#ifndef ILRD_STACK
#define ILRD_STACK

#include <stddef.h> /*size_t*/



typedef struct stack stack_t;


struct stack				
{
    size_t element_size;
    char *start_stack;
    size_t size;
    size_t capacity;
};







/*  Allocates space of a given size.
	arguments: number of elements,element size.
	returns the created stack. */

stack_t *StackCreate(size_t capacity, size_t element_size);

/*  Destroys a given stack.
	arguments: stack to be destroyed.
	no return value. */

void StackDestroy(stack_t *stack);

/*  popes element from the stack out, the last element entered the stack at first.
	arguments: the stack.
	no return value. */
	
void StackPop(stack_t *stack);

/*  Pushes element from the user to the stack, locating it at the top.
	arguments: the stack, pointer to element.
	no return value. */
	
void StackPush(stack_t *stack, const void *element);

/*  checks weather the stack is empty.
	arguments: the stack.
	returns 1 if true and 0 if false */
	
int StackIsEmpty(const stack_t *stack);


/*  Presents the last pushed item for watch only.
	arguments: the stack.
	returns the last element inserted. */
	
void *StackPeek(const stack_t *stack);

/*  Returns the size of the orginal capacity of the stack .
	return used space. */
	
size_t StackCapacity(const stack_t *stack);

/*  counts the amounts of elements inserted.
	arguments: the stack.
	return the space left. */
	
size_t StackSize(const stack_t *stack);
 
 
#endif /*ILRD_STACK*/


