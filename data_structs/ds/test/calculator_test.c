/*
	dev : Gilad Kahn
	rev : Daniel Gabay
	status: approved
	date: 15.02.22
*/


#include <stdio.h>


#include "stack.h"
#include "Calculator.h"



void TestCalculator(double answer,const char *str, status_t *sent_status,status_t required_status, calc_t *calc);

int main()
{
        char str[100] = "7+8";              /* Result = 15 status = SUCCESS       */
        char str2[100] = "8+8*3+-2^5";         /* Result =  0 status = SUCCESS      */
        char str3[100] = "8+8*3-2^";         /* Result =  0 status = SYNTAX_ERROR */
        char str4[100] = "2/0";             /* Result =  0 status = MATH_ERROR         */
        char str5[100] = "8++8*((3-2)*5)";     /* Result = 48 status = SUCCESS       */
        char str6[100] = "3-2)*5";         /* Result =  0 status = SYNTAX_ERROR */
        char str7[100] = "(3-2)*5+ 5*(4+4+4";    /* Result =  0 status = SYNTAX_ERROR */
        char str8[100] = "456+++4";

        status_t status = SUCCESS;


        calc_t *test = NULL;


        test = CalcInit(100);

        if (test != NULL)
        {
            printf("succsess in init \n");
        }




        TestCalculator(15, str, &status, SUCCESS , test);
        TestCalculator(0, str2, &status, SUCCESS , test);
        TestCalculator(0, str3, &status, SYNTAX_ERROR, test);
        TestCalculator(0, str4, &status, MATH_ERROR, test);
        TestCalculator(48, str5, &status, SUCCESS, test);
        TestCalculator(0, str6, &status, SYNTAX_ERROR, test);
        TestCalculator(0, str7, &status, SYNTAX_ERROR, test);
        TestCalculator(0, str8, &status, SYNTAX_ERROR, test);  


    CalcDestroy(test);
    

    return(0);
}


void TestCalculator(double answer,const char *str, status_t *sent_status,status_t required_status, calc_t *calc)
{
    static size_t test_num = 1;

    if (answer != CalcCalculate(str, sent_status, calc))
    {
        printf("error in test %ld \n", test_num);
        printf("answer = %f wrong answer = %f \n", answer, CalcCalculate(str, sent_status, calc));
    }
    ++test_num;

    if (*sent_status != required_status)
    {
        printf("error in test %ld \n", test_num);
        printf("sent_status = %d required_status = %d \n",*sent_status, required_status);
    }
    ++test_num;

}