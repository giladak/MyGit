/**************************************************************************

	dev : Gilad Kahn
	rev: Alon Levy
	status: approved
	date: 12.1.22
***********************************************************************/

#ifndef ILRD_CBUFFER_H
#define ILRD_CBUFFER_H




#include <unistd.h>/*ssize_t*/
#include <stddef.h> /*size_t*/

typedef struct circular_buffer cbuff_t;




/*************************************************************************************************************************
** This funcation crates a Circular Buffer.
**
** Arguments: the desired capacity of the file
**
** Return value: pointer to start of created Circular Buffer.
**
** Complexity: O(N)
*************************************************************************************************************************/
cbuff_t *CBufferCreate(size_t capacity); 


/*************************************************************************************************************************
** This funcation free all the circular buffer bytes.
**
** Arguments: buffer - pointer to a byte in the buffer.
**
** Return value: non.
**
** Complexity: O(N)
*************************************************************************************************************************/

void CBufferDestroy(cbuff_t *buffer);


/*************************************************************************************************************************
** This funcation checks if the  circular buffer is empty.
**
** Arguments: buffer - pointer to the start of the buffer.
**
** Return value: 1 if empty, 0 otherwise.
**
** Complexity: O(1)
*************************************************************************************************************************/	
int CBufferIsEmpty(const cbuff_t *buffer);


/*************************************************************************************************************************
** This funcation writes bytes to the circular buffer.
**
** Arguments: buffer - pointer to the place to write in the buffer,
	
	src - a pointer the infomation that will be copied to the array
		
	 count - the number of byets to write.
**
** Return value: the number of bytes sucssefully written.
**
** Complexity: 
*************************************************************************************************************************/	
ssize_t CBufferWrite(cbuff_t *buffer, const void *src, size_t count);


/*************************************************************************************************************************
** This funcation reads bytes from the buffer
**
** Arguments: buffer - pointer to the bytes to read from the buffer.

	 count - the number of byets to read.
**
** Return value: the number of bytes sucssefully readen.
**
** Complexity:
*************************************************************************************************************************/	
ssize_t CBufferRead(cbuff_t *buffer, void *dest, size_t count);


/*************************************************************************************************************************
** This funcation count the number of bytes written in the buffer.
**
** Arguments: buffer - pointer to the buffer.
**
** Return value: the number of byets in the buffer.
**
** Complexity: O(1) 
*************************************************************************************************************************/	
size_t CBufferSiz(const cbuff_t *buffer);


/*************************************************************************************************************************
** This funcation returns the number of free bytes.
**
** Arguments: buffer - pointer to the buffer.
**
** Return value: number of free bytes.
**
** Complexity: O(1)
*************************************************************************************************************************/	
size_t CBufferFreeSpace(const cbuff_t *buffer);



#endif /* ILRD_CBUFFER_H */





