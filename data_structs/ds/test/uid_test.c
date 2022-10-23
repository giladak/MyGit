/**************************************************************************

	dev : Gilad Kahn
	rev: Vitali
	status: approved
	date: 18.1.22
*******************************************************************/

#include <stdio.h>  /*printf*/
#include <stdlib.h> /*size_t*/
#include <stddef.h> /*NULL*/
#include <time.h> /*time_t*/

#include "uid.h"





/*
	if (  != )
	{
		printf ("error in test 1 \n");
	}
	
	if (  != )
	{
		printf ("error in test 2 \n");
	}
	
	if (  != )
	{
		printf ("error in test 3 \n");
	}   
*/




int main()
{
	ilrd_uid_t new_uid = UIDCreate(); 
	time_t cur_time;
	if (UIDIsSame(new_uid, g_BadUid) != 0)
	{
		printf ("error in test 1 \n");
	}
	
	time(&cur_time);
	
	printf("%s \n", ctime(&cur_time));
		
	
	return(0);
}



