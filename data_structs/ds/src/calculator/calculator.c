/*
	dev : Gilad Kahn
	rev : Daniel Gabay
	status: approved
	date: 15.02.22
*/


#include <stdio.h> 
#include <stdlib.h> /*strtod*/
#include <assert.h> /*assert*/
#include <math.h> /*pow*/
#include <string.h> /*assert*/

#include "stack.h"
#include "Calculator.h"
#include "utilities.h"


#define CHARS_NUM 256
#define OPERATORS_NUM 8 /*+, -, *, /, ^, (,), \0*/
#define HEAD_STRUCT_SIZE sizeof(calc_t)
#define OPT_FUNC_STRUCT_SIZE sizeof(opt_func_t)

/*typedef struct calculator calc_t;

typedef enum
{
    SUCCESS,
    MATH_ERROR,
    SYNTAX_ERROR
} status_t;
*/


/*********************************declerations and typedefs******************************/
typedef double (*math_func)(double, double, status_t *);
typedef char *(*transition_func)(const char *event, status_t *status, calc_t *calc);
typedef double(*opteration_function)(calc_t *calc, status_t *status, math_func math_func_ptr); 


typedef enum
{
    WAIT_FOR_NUM,
    WAIT_FOR_OPT,
    ERROR,
    STATES_NUM
}STATE;


typedef struct opt_func
{
    int prority;
    double(*opteration_function)(calc_t *calc, status_t *status, math_func math_func_ptr);
    double (*math_func)(double, double, status_t *);  
}opt_func_t;



struct calculator
{
    stack_t *nums_stack;
    stack_t *opts_stack;
    opt_func_t operation_lut[CHAR_NUM];
    char *(*transition_lut[STATES_NUM][CHAR_NUM])(const char *event, status_t *status, calc_t *calc);
    int STATE;
};




/*******************************inititilazitions funcs********************************/
static void InitilizeOperationLut(calc_t *calc);
static void InitilizeTransitionLut(char* (*(*transition_lut)[CHAR_NUM])(const char *event, status_t *status, calc_t *calc));


 
/***************************transition funcs*************************************/
static char *AbortOperation(const char *str, status_t *status, calc_t *calc);
static char *HandleNum(const char *str, status_t *status, calc_t *calc);
static char *HandlePlusMinus(const char *str, status_t *status, calc_t *calc);
static char *HandleOp(const char *str, status_t *status, calc_t *calc);
static char *HandleOpenParanthesess(const char *str, status_t *status, calc_t *calc);
static char *HandleSpace(const char *str, status_t *status, calc_t *calc);
static char *HandleNullByte(const char *str, status_t *status, calc_t *calc);



/***********************************static operation funcs*******************************************/
static double DoMathOperation(calc_t*calc, status_t *status, math_func math_func_ptr);
static double DoAbortOperation(calc_t*calc, status_t *status, math_func math_func_ptr);
static double DoNothingOperation(calc_t*calc, status_t *status, math_func math_func_ptr);



/***********************************static math funcs*******************************************/
static double Add(double num1, double num2, status_t *status);
static double Divide(double num1, double num2, status_t *status);
static double Power(double num1, double num2, status_t *status);
static double Multiply(double num1, double num2, status_t *status);
static double Minus(double num1, double num2, status_t *status);
static double DoNothing(double num1, double num2, status_t *status);



/***********************************my assitance funcs*******************************************/
static void InitilizeOperationStruct(opt_func_t *opt_func, int priority, opteration_function opt_function, math_func math_function);
static double AssignPeekToDouble(calc_t *calc);
static void CalculateUpToLowerPriority(unsigned char operator, status_t *status, calc_t *calc);
static void EmptyStack(stack_t *stack);
/*
static void ChecksFunc(calc_t*calc, status_t *status);
*/
/***********************************user funcs*******************************************/

calc_t *CalcInit(size_t max_length)
{
    calc_t *new_calculator = NULL;
    
    new_calculator = (calc_t*)malloc(HEAD_STRUCT_SIZE);
    
    if (NULL == new_calculator)
    {
        return(NULL);
    }
    
    new_calculator->nums_stack = StackCreate(HALF_OF(max_length), sizeof(double));
    new_calculator->opts_stack = StackCreate(HALF_OF(max_length), sizeof(char));             /*check*/
    new_calculator->STATE = WAIT_FOR_NUM;

    InitilizeTransitionLut(new_calculator->transition_lut);
   
    InitilizeOperationLut(new_calculator);

    return(new_calculator);
}



void CalcDestroy(calc_t *calc)
{
    StackDestroy(calc->nums_stack);
    StackDestroy(calc->opts_stack);

    free (calc);

    calc = NULL;
}




double CalcCalculate(const char *str, status_t *status, calc_t *calc)
{
    double result = 0;
    status_t current_status = PENDING;
    calc->STATE = WAIT_FOR_NUM;
    
    while (PENDING == current_status && ERROR != calc->STATE)
    {
        str = (*calc->transition_lut[calc->STATE][*(unsigned char *)str])((char*)str, &current_status, calc); 
    }

    result = *(double*)StackPeek(calc->nums_stack);

    StackPop(calc->nums_stack);

    if (NULL != status)
    {    
        *status = current_status;
    }

    return (result);
}

/*************************************state_funcs******************************************/


char *AbortOperation(const char *str, status_t *status, calc_t *calc)
{   
    double zero = 0;

    UNUSED(str);
    UNUSED(calc);

    calc->STATE = ERROR;
    *status = SYNTAX_ERROR;

    EmptyStack(calc->nums_stack);
    EmptyStack(calc->opts_stack);

    StackPush(calc->nums_stack, &zero);

    return((char *)str);
}




static char *HandleCloseParanthesess(const char *str, status_t *status, calc_t *calc)
{   
    assert(str);
    assert(calc);

    CalculateUpToLowerPriority(*str, status, calc);

    if (1 == StackIsEmpty(calc->opts_stack) || '(' != *(char*)StackPeek(calc->opts_stack))
    {
        AbortOperation(str, status, calc);
        return ((char*)str);
    }

    StackPop(calc->opts_stack);

    ++str;

    return ((char*)str);
}




static char *HandleOpenParanthesess(const char *str, status_t *status, calc_t *calc)
{   
    assert(str);
    assert(calc);
    
    UNUSED(status);

    StackPush(calc->opts_stack, str);

    ++str;

    return ((char*)str);
}


static char *HandleSpace(const char *str, status_t *status, calc_t *calc)
{
    assert(str);
    assert(calc);

    UNUSED(status);

    ++str;

    return ((char*)str);
}

static char *HandleNullByte(const char *str, status_t *status, calc_t *calc)
{
    assert(str);
    assert(calc);

    CalculateUpToLowerPriority(*str, status, calc);

    if (1 != StackIsEmpty(calc->opts_stack))
    {
        AbortOperation(str, status, calc);
        return ((char*)str);
    }

    *status = (*status - 3) *(-1) / 2; /*makes sure math_error remains*/

    return ((char*)str);
}

char *HandleNum(const char *str, status_t *status, calc_t *calc)
{
    double number = 0;

    assert(calc);
    assert(str);

    UNUSED(status);


    number = strtod(str, (char**)&str);

    /*
    printf("pushed number = %f \n", number);
    */
   
    StackPush(calc->nums_stack, &number);

    calc->STATE = WAIT_FOR_OPT;

    return((char *)str);
}



char *HandleOp(const char *str, status_t *status, calc_t *calc)
{
   CalculateUpToLowerPriority(*str, status, calc); 

   calc->STATE = WAIT_FOR_NUM;
    
    StackPush(calc->opts_stack, str);

    ++str;

    return((char*)str);
}


static char *HandlePlusMinus(const char *str, status_t *status, calc_t *calc)
{
    double number = 0;

    assert(str);
    assert(status);
    assert(calc);

    number = strtod(str, NULL);

    if (number == 0)
    {
        return(AbortOperation(str, status, calc));
    }

    return(HandleNum(str, status, calc));
}




static void CalculateUpToLowerPriority(unsigned char operator, status_t *status, calc_t *calc)
{
  
    int current_operation_prioritiy = 0;
    int running_operation_prioritiy = 0;
    unsigned char previous_operation = 0;

    assert(calc);

    current_operation_prioritiy = calc->operation_lut[operator].prority;

    
    while (1 != StackIsEmpty(calc->opts_stack))
    {
        previous_operation = *(char*)StackPeek(calc->opts_stack);

        running_operation_prioritiy = calc->operation_lut[previous_operation].prority;

        if (current_operation_prioritiy >= running_operation_prioritiy)
        {
            break;
        }

        calc->operation_lut[previous_operation].opteration_function(calc, status, (*(calc->operation_lut[previous_operation].math_func)));

        StackPop(calc->opts_stack);
    }
}


static void EmptyStack(stack_t *stack)
{
    while (1 != StackIsEmpty(stack))
    { 
        StackPop(stack);
    }
}

/*******************************operation funcs****************************/


static double DoNothingOperation(calc_t*calc, status_t *status, math_func math_func_ptr)
{
    UNUSED(calc);
    UNUSED(status);
    UNUSED(math_func_ptr);

    return(0);
}

static double DoAbortOperation(calc_t*calc, status_t *status, math_func math_func_ptr)
{
    AbortOperation(0, status, calc);

    UNUSED(math_func_ptr);
    
    return(0);
}




static double DoMathOperation(calc_t*calc, status_t *status, math_func math_func_ptr)
{
    double num1 = 0;
    double num2 = 0;
    double result = 0;

    assert(math_func_ptr);

    num1 = AssignPeekToDouble(calc);
    num2 = AssignPeekToDouble(calc);

    result = (*math_func_ptr)(num2, num1 , status);

    StackPush(calc->nums_stack, &result);

    return (result);
}




/*************************math funcs *****************************/



static double Add(double num1, double num2, status_t *status)
{   
    UNUSED(status);

    return(num1 + num2);
}



static double Divide(double num1, double num2, status_t *status)
{   
    if (0 == num2)
    {
        *status = MATH_ERROR;
        return(0);
    }
    return(num1 / num2);
}



static double Power(double x, double y, status_t *status)
{
    double ans = 1;
    size_t i = 0;

    UNUSED(status);
    if (y < 0)
    {
        x = 1 / x;
        y *= -1;
    }
    for (i = 0; i < y; ++i)
    {
        ans *= x;
    }
    return ans;
}

static double Multiply(double num1, double num2, status_t *status)
{   
    UNUSED(status);

    return(num1 * num2);
}

static double Minus(double num1, double num2, status_t *status)
{  
    UNUSED(status);

    return(num1 - num2);
}


static double DoNothing(double num1, double num2, status_t *status)
{
    UNUSED(num1);
    UNUSED(num2);
    UNUSED(status);

    return(0);
}




static double AssignPeekToDouble(calc_t *calc)
{
    double answer = 0;

    assert (calc);

    answer = *(double*)StackPeek(calc->nums_stack);

    StackPop(calc->nums_stack);

    return(answer);
}



static void InitilizeOperationLut(calc_t *calc)
{
    size_t i = 0;

    for (i = 0; i < CHAR_NUM; ++i)
    {
        InitilizeOperationStruct(&calc->operation_lut[i], 6, DoAbortOperation, DoNothing);
    }

    InitilizeOperationStruct(&calc->operation_lut['('], 0, DoNothingOperation, DoNothing); /*change*/ 
    InitilizeOperationStruct(&calc->operation_lut[')'], 1, DoNothingOperation, DoNothing); /*change*/
    InitilizeOperationStruct(&calc->operation_lut['\0'], 2, DoNothingOperation, DoNothing); /*change*/
    InitilizeOperationStruct(&calc->operation_lut['+'], 3, DoMathOperation, Add);
    InitilizeOperationStruct(&calc->operation_lut['-'], 3, DoMathOperation, Minus);
    InitilizeOperationStruct(&calc->operation_lut['*'], 4, DoMathOperation, Multiply);
    InitilizeOperationStruct(&calc->operation_lut['/'], 4, DoMathOperation, Divide);
    InitilizeOperationStruct(&calc->operation_lut['^'], 5, DoMathOperation, Power);
}


static void InitilizeOperationStruct(opt_func_t *opt_func, int priority, opteration_function opt_function, math_func math_function)
{
    assert(opt_func);

    opt_func->prority = priority;
    opt_func->opteration_function = opt_function;  
    opt_func->math_func = math_function;
}

static void InitilizeTransitionLut(char* (*(*transition_lut)[CHAR_NUM])(const char *event, status_t *status, calc_t *calc))
{
    size_t i = 0;
    size_t j = 0;

    for (i = 0; i < STATES_NUM; ++i)
    {
        for (j = 0; j < CHAR_NUM; ++j)
        {
            transition_lut[i][j] = AbortOperation;
        }
    }

    /*********initilize numbers*************/

    for(j = '0'; j <= '9'; ++j)
    {
        transition_lut[WAIT_FOR_NUM][j] = HandleNum;
    }

    transition_lut[WAIT_FOR_NUM]['+'] = HandlePlusMinus;
    transition_lut[WAIT_FOR_NUM]['-'] = HandlePlusMinus;
    transition_lut[WAIT_FOR_NUM]['('] = HandleOpenParanthesess;
    transition_lut[WAIT_FOR_NUM][' '] = HandleSpace;  


    /*********initilize other charachters*************/
    
    transition_lut[WAIT_FOR_OPT]['+'] = HandleOp;
    transition_lut[WAIT_FOR_OPT]['-'] = HandleOp;
    transition_lut[WAIT_FOR_OPT]['*'] = HandleOp;
    transition_lut[WAIT_FOR_OPT]['/'] = HandleOp;
    transition_lut[WAIT_FOR_OPT]['^'] = HandleOp;

    transition_lut[WAIT_FOR_OPT][')'] = HandleCloseParanthesess;
    transition_lut[WAIT_FOR_OPT][' '] = HandleSpace;         
    transition_lut[WAIT_FOR_OPT]['\0'] = HandleNullByte;    
}
