
#ifndef UID_H
#define UID_H

#include <stdio.h>

#include <time.h>
#include <sys/types.h>
#include <unistd.h>



typedef struct uid ilrd_uid_t;
struct uid  /*  in header file */
{
	size_t counter; 
	pid_t pid;	 /*getpid (void) */
	time_t current_time; /*use ctime func */
};



ilrd_uid_t UIDCreate(void);

int UIDIsSame(ilrd_uid_t uid1, ilrd_uid_t uid2);

extern const ilrd_uid_t g_BadUid;



#endif /*UID_H*/

