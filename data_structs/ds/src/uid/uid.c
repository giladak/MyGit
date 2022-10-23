/**************************************************************************

	dev : Gilad Kahn
	rev: Vitali
	status: approved
	date: 18.1.22
*******************************************************************/


#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdatomic.h> /*atomic*/


#include "uid.h"


const ilrd_uid_t g_BadUid = {0, 0, 0};

ilrd_uid_t UIDCreate(void)
{
	ilrd_uid_t new_uid;
	static atomic_size_t count_uid = 0;
	
	new_uid.current_time = time(NULL);
	
	new_uid.counter = ++count_uid;
	
	new_uid.pid = getpid();
	
	return (new_uid);
}


int UIDIsSame(ilrd_uid_t uid1, ilrd_uid_t uid2)
{
	return (uid1.pid == uid2.pid && uid1.current_time == uid2.current_time && uid1.counter == uid2.counter);
}
















