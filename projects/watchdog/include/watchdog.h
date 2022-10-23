/**************************************************************************

	dev : Gilad Kahn
	rev: Idan Matalon
	status: approved
	date: 30.3.22
*******************************************************************/	


#ifndef WATCHDOG_H
#define WATCHDOG_H


#include <stdio.h>     /*printf*/
#include <unistd.h>    /*pid_t*/
#include <sys/types.h> /*pthread_t*/




typedef struct watch_dog_return watch_dog_answer_t;


struct watch_dog_return
{
    pid_t pid;
    pthread_t *pthread;
	pthread_attr_t *attr;
};


/**************************************************************************
 * @brief 
 * 
 * @param process_exe_path - the process of the current path, argv[0].
 * @param watchdog_exe_path - the process of the watchdog. if the the exe path is in the same file is the user program the user can insert "./watchdog.out" to this argument.
 * @param grace - the number of times the function can not accept a signal before starting to revive
 * @return watch_dog_answer_t* - a answer is placed in a struct and should be accepted by user and inserted in to the stop function
 ***************************************************************************/




watch_dog_answer_t *WatchDogRun(char *process_exe_path, char *watchdog_exe_path, size_t grace);


/*************************************************************************8
 * @brief stops the watchdog
 * 
 * @param watch_dog_return - 
 **************************************************************/

void WatchDogStop (watch_dog_answer_t *watch_dog_return);


#endif /*WATCHDOG_H*/


