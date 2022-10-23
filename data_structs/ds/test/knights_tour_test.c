/*
	dev : Gilad Kahn
	rev : Alon Twig
	status: approved
	date: 06.03.22
*/


#include <stdio.h> /*for*/
#include <stdlib.h> /*malloc*/
#include <assert.h> /*assert*/
#include <string.h>

#include "utilities.h"
#include "knights_tour.h"
#include "sorts.h"


static void PrintAnswerArray (size_t *answer_array);


int main ()
{	
	size_t answer[NUM_OF_CELLS] = {0};
	size_t *answer_2 = NULL;
	int succsess = 0;

	printf("knights tour tests: \n");

	succsess = GetPathWithWarndorffs(answer, 2, 2);

	if (1 == succsess)
	{
		printf("function failed \n");
	}
	else
	{
		PrintAnswerArray(answer);
	}

    return(0);
}


static void PrintAnswerArray (size_t *answer_array)
{
	size_t i = 0;

	assert(answer_array);

	printf("answer array: \n");

	for (i = 0; i < NUM_OF_CELLS; ++i)
	{
		printf("%ld \n", answer_array[i]);
	}
}



