
#include <stdio.h> /*for*/
#include <stdlib.h> /*malloc, atoi*/
#include <assert.h> /*assert*/
#include <string.h> /*memmove*/

#include "utilities.h"
#include "dhcp.h"
#include "trie.h"





struct dhcp
{
    unsigned char subnet[IP_NUM_BYTES];
    size_t num_of_bit_for_subnet;
    trie_t *trie;
};


/***********************help functions declerations******************************/
static double Power(double num1, int num2);
static int IsAllZero(const unsigned char ip1[], size_t size);
void ConvertCharToBinaryString(char num,  char *buffer, size_t num_of_bits);
static unsigned char ConvertBinaryStringToChar(char binary_str[]);



/**************************DHCPCreate*************************************/

dhcp_t *DHCPCreate(const unsigned char subnet[IP_NUM_BYTES], size_t num_of_bit_in_subnet)
{
	dhcp_t *new_dhcp = NULL;
	size_t i = 0;
	size_t size_of_ip = 0;
	char ip_for_broadcast[IP_NUM_BYTES*BYTE_BITS + 1] = {0};
	char ip_for_network[IP_NUM_BYTES*BYTE_BITS + 1] = {0};
	char ip_for_server[IP_NUM_BYTES*BYTE_BITS + 1] = {0};

	assert(subnet);

	new_dhcp = (dhcp_t*)malloc(sizeof(dhcp_t));

	if (NULL == new_dhcp)
	{
		return(NULL);
	}

	new_dhcp->num_of_bit_for_subnet = num_of_bit_in_subnet;
	new_dhcp->trie = TrieCreate();

	if (NULL == new_dhcp->trie)
	{
		free(new_dhcp->trie);
		return(NULL);
	}

	for (i = 0; i < IP_NUM_BYTES; ++i)
	{
		new_dhcp->subnet[i] = subnet[i];
	}

	size_of_ip = IP_NUM_BYTES*BYTE_BITS - num_of_bit_in_subnet;

	for (i = 0; i < size_of_ip;++i)
	{
		ip_for_network[i] = '0';
		ip_for_server[i] = '1';
		ip_for_broadcast[i] = '1';
	}

	ip_for_server[i - 1] = '0';

	if (FAIL == TrieInsert(new_dhcp->trie, ip_for_broadcast, ip_for_broadcast))
	{
		TrieDestroy(new_dhcp->trie);
		free(new_dhcp);
		return(NULL);
	}

	if (FAIL == TrieInsert(new_dhcp->trie, ip_for_server, ip_for_server))
	{
		TrieDestroy(new_dhcp->trie);
		free(new_dhcp);
		return(NULL);
	}

	if (FAIL == TrieInsert(new_dhcp->trie, ip_for_network, ip_for_network))
	{
		TrieDestroy(new_dhcp->trie);
		free(new_dhcp);
		return(NULL);
	}


	return(new_dhcp);
}

/**************************DHCPDestroy*************************************/

void DHCPDestroy(dhcp_t *dhcp)
{
    assert (dhcp);

    TrieDestroy(dhcp->trie);

	dhcp->trie = NULL;

    free(dhcp);
}

/**************************DHCPCount*************************************/
size_t DHCPCountFree(const dhcp_t *dhcp)
{
	size_t dhcp_capacitiy = 0;
	size_t filled_spaces = 0;
	size_t free_spaces = 0;

	assert(dhcp);

	dhcp_capacitiy = Power(2,(IP_NUM_BYTES*BYTE_BITS - dhcp->num_of_bit_for_subnet));
	filled_spaces = TrieCount(dhcp->trie);
	free_spaces = dhcp_capacitiy - filled_spaces;

	return(free_spaces);
}



/**************************DHCPAllocateIp*************************************/
status_t DHCPAllocateIP(dhcp_t *dhcp, const unsigned char rquest_ip[IP_NUM_BYTES], unsigned char out_ip[IP_NUM_BYTES])
{
	char binary_ip[IP_NUM_BYTES * BYTE_BITS + 1] = {0};
	char binary_subnet[IP_NUM_BYTES * BYTE_BITS + 1] = {0};
	char answer_binary[IP_NUM_BYTES * BYTE_BITS + 1] = {0};
	size_t i = 0;

	assert(dhcp);
	assert(rquest_ip);
	assert(out_ip);

	
	for (i = 0; i < IP_NUM_BYTES; ++i)
	{
		ConvertCharToBinaryString(rquest_ip[i], &binary_ip[i*BYTE_BITS], BYTE_BITS);
		ConvertCharToBinaryString(dhcp->subnet[i], &binary_subnet[i*BYTE_BITS], BYTE_BITS);
	}

	if (TRUE == IsAllZero(rquest_ip, IP_NUM_BYTES))
	{
		memmove(binary_ip, binary_subnet, dhcp->num_of_bit_for_subnet);
	}

	if (FAIL == TrieInsert(dhcp->trie, &binary_ip[dhcp->num_of_bit_for_subnet], answer_binary))
		return(FAILURE);
	}

	memmove(&binary_ip[dhcp->num_of_bit_for_subnet], answer_binary, strlen(answer_binary));

	for (i = 0; i < IP_NUM_BYTES; ++i)
	{
		out_ip[i] = ConvertBinaryStringToChar(&binary_ip[i*BYTE_BITS]);
	}

	return(SUCCESS);
}


/**************************DHCPFreeIp*************************************/

status_t DHCPFreeIP(dhcp_t *dhcp, const unsigned char ip[IP_NUM_BYTES])
{
	char binary_ip[IP_NUM_BYTES * BYTE_BITS + 1] = {0};
	size_t i = 0;

	assert(dhcp);
	assert(ip);

	for (i = 0; i < IP_NUM_BYTES; ++i)
	{				       
		ConvertCharToBinaryString(ip[i], &binary_ip[i*BYTE_BITS], BYTE_BITS);
	}

	if (FAIL == TrieRemove(dhcp->trie, &binary_ip[dhcp->num_of_bit_for_subnet]))
	{
		return(FAILURE_DOUBLE_FREE);
	}

	return(SUCCESS);
}




/***********************help functions******************************/



static double Power(double num1, int num2)
{
    double res = 1;
    int i;
    
    if( 0 > num2 )
    {
        num2 *= -1;
        num1 = 1 / num1;
    }
    
    for( i = 0; i < num2; ++i )
    {
        res *= num1;
    }
    
    return res;  
}


static int IsAllZero(const unsigned char ip1[], size_t size)
{

    size_t i = 0;

    assert( NULL != ip1 );
    

    for( i = 0; i < size; ++i )
    {
        if( ip1[i] != 0 )
        {
            return FALSE;
        }
    }

    return TRUE;
}


void ConvertCharToBinaryString(char num,  char *buffer, size_t num_of_bits)
{
        
    int m = num_of_bits-1;
    
    assert( NULL != buffer);
    
    while(0 <= m)
    {
        buffer[m] = num & 1 ? '1' : '0';
        num >>= 1 ;
        --m;
    }
}


static unsigned char ConvertBinaryStringToChar(char binary_str[])
{
    int decimal = 0;
    int position = 0;
    int index = BYTE_BITS -1 ;
    
    assert(binary_str);

    while (index >= 0)
    {
        decimal = decimal + (binary_str[index] - 48) * Power(2, position);
        --index;
        ++position;
    }

    return (unsigned char)decimal;
}
