#ifndef DHCP_H
#define DHCP_H

#include <stdio.h> /*size_t*/

#include "trie.h"


#define IP_NUM_BYTES 4
#define FULL_ASCII 255


typedef enum 
{
    SUCCESS,
    FAILURE,
    FAILURE_DOUBLE_FREE
} status_t;



typedef struct dhcp dhcp_t;  






/**************************************************************************************************************************************
                                        				create
***************************************************************************************************************************************
DESCRIPTION
	
ARGUMENTS
	
RETURN VALUE
	
complexity - 
**************************************************************************************************************************************/
dhcp_t *DHCPCreate(const unsigned char subnet[IP_NUM_BYTES], size_t num_of_bit_in_subnet);




/**************************************************************************************************************************************
                                        				destroy
***************************************************************************************************************************************
DESCRIPTION
	
ARGUMENTS
	
RETURN VALUE
	
complexity - .
**************************************************************************************************************************************/
void DHCPDestroy(dhcp_t *dhcp);




/**************************************************************************************************************************************
                                        				allocate ip
***************************************************************************************************************************************
DESCRIPTION
	
ARGUMENTS
	
RETURN VALUE
	
complexity - .
**************************************************************************************************************************************/
status_t DHCPAllocateIP(dhcp_t *dhcp, const unsigned char rquest_ip[IP_NUM_BYTES], unsigned char out_ip[IP_NUM_BYTES]);




/**************************************************************************************************************************************
                                        				free ip
***************************************************************************************************************************************
DESCRIPTION
	
ARGUMENTS
	
RETURN VALUE
	
complexity - .
**************************************************************************************************************************************/
status_t DHCPFreeIP(dhcp_t *dhcp, const unsigned char ip[IP_NUM_BYTES]);





/**************************************************************************************************************************************
                                        				count free
***************************************************************************************************************************************
DESCRIPTION
	
ARGUMENTS
	
RETURN VALUE
	
complexity - .
**************************************************************************************************************************************/
size_t DHCPCountFree(const dhcp_t *dhcp);










#endif /*DHCP_H*/