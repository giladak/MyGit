/*
	dev : 
	rev : 
	status: 
	date: 
*/

#define _DEFAULT_SOURCE


#include <stdio.h> /*for*/
#include <stdlib.h> /*malloc*/
#include <assert.h> /*assert*/
#include <string.h>
#include <pthread.h> /*pthread_create*/
#include <signal.h> /*sigemptyset*/
#include <stdatomic.h>



#include "utilities.h"



pthread_t test_thread;

atomic_int flag = OFF;


void SignalHandler(int signum);
void SetHandler(int signum,  void (*handler)(int));
void* TestThread(void *param);
void SetThreadMask(int signum);
void UnSetThreadMask(int signum);
void SetProcMask(int signum);
void UnSetProcMask(int signum);




void* TestThread(void *param)
{	
    printf("watchdog pid = %d \n", getpid());

	SetHandler(SIGINT, SignalHandler);

	UnSetThreadMask(SIGINT);

	sleep(10);

	return(NULL);
}




 
int main()
{
	struct sigaction oldact;



	printf("test pid = %d \n", getpid());

	SetThreadMask(SIGINT);

	
	pthread_create(&test_thread, NULL, TestThread, NULL);




	while(1)
	{
		sleep(1);

		if (ON == flag)
		{
			printf("signal accpeted \n");

			break;
		}

	}


	pthread_join(test_thread, NULL);


	return(0);
}




void SetThreadMask(int signum)
{
	sigset_t sigmask;
    
    sigemptyset(&sigmask);
    sigaddset(&sigmask, signum);


	if (0 != pthread_sigmask(SIG_BLOCK, &sigmask, NULL))
	{
		return;
	}

    return;
}
void UnSetThreadMask(int signum)
{
	sigset_t sigmask;
    
    sigemptyset(&sigmask);
    sigaddset(&sigmask, signum);


	if (0 != pthread_sigmask(SIG_UNBLOCK, &sigmask, NULL))
	{
		return;
	}

    return;
}


void SetProcMask(int signum)
{
	sigset_t sigmask;
    
    sigemptyset(&sigmask);
    sigaddset(&sigmask, signum);


	if (0 != sigprocmask(SIG_BLOCK, &sigmask, NULL))
	{
		return;
	}

    return;
}

void UnSetProcMask(int signum)
{
	sigset_t sigmask;
    
    sigemptyset(&sigmask);
    sigaddset(&sigmask, signum);


	if (0 != sigprocmask(SIG_UNBLOCK, &sigmask, NULL))
	{
		return;
	}

    return ;

}



void SignalHandler (int signum)
{
    UNUSED(signum);

    flag = ON;
}


void SetHandler(int signum,  void (*handler)(int))
{
    struct sigaction sa;


    sa.sa_handler = handler;

    sigaction(signum, &sa, NULL);
   
 }
