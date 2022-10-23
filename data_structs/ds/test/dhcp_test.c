/*
	dev : Gilad Kahn
	rev : Sara Shushan
	status: approved
	date: 7.3.22
*/


#include <stdio.h> /*printf*/


#include "utilities.h"
#include "dhcp.h"


void DhcpTests(void);
void TestAllocateIp(dhcp_t *test, const unsigned char request_ip[IP_NUM_BYTES], unsigned char answer[IP_NUM_BYTES], status_t answer_status);
void TestFreeIp(dhcp_t *test, unsigned char request_ip_to_free[IP_NUM_BYTES], status_t answer_status);
void TestCount (dhcp_t *test, size_t answer);


int main()
{
	DhcpTests();

    return(0);
}



void DhcpTests(void)
{	

	size_t num_of_bits_in_subnet = 24;
	dhcp_t *test = NULL;

	const unsigned char subnet[IP_NUM_BYTES] = {192,168,111,0};
	const unsigned char ip_to_insert_1[IP_NUM_BYTES] = {0,0,0,0};
	const unsigned char ip_to_insert_2[IP_NUM_BYTES] = {192,168,111,250};
	const unsigned char ip_to_insert_3[IP_NUM_BYTES] = {192,168,111,250};
	const unsigned char ip_to_insert_4[IP_NUM_BYTES] = {192,168,111,18};
	const unsigned char ip_to_insert_5[IP_NUM_BYTES] = {192,168,111,18};
	const unsigned char ip_to_insert_6[IP_NUM_BYTES] = {192,168,111,25};
	const unsigned char ip_to_insert_7[IP_NUM_BYTES] = {192,168,111,100};

	unsigned char allocated_ip_1[IP_NUM_BYTES] = {0,0,0,0};
	unsigned char allocated_ip_2[IP_NUM_BYTES] = {0,0,0,0};
	unsigned char allocated_ip_3[IP_NUM_BYTES] = {0,0,0,0};
	unsigned char allocated_ip_4[IP_NUM_BYTES] = {0,0,0,0};
	unsigned char allocated_ip_5[IP_NUM_BYTES] = {0,0,0,0};
	unsigned char allocated_ip_6[IP_NUM_BYTES] = {0,0,0,0};
	unsigned char allocated_ip_7[IP_NUM_BYTES] = {0,0,0,0};


	unsigned char ip_to_insert_res_1[IP_NUM_BYTES] = {192,168,111,1};
	unsigned char ip_to_insert_res_2[IP_NUM_BYTES] = {192,168,111,250};
	unsigned char ip_to_insert_res_3[IP_NUM_BYTES] = {192,168,111,251};
	unsigned char ip_to_insert_res_4[IP_NUM_BYTES] = {192,168,111,18};
	unsigned char ip_to_insert_res_5[IP_NUM_BYTES] = {192,168,111,19};
	unsigned char ip_to_insert_res_6[IP_NUM_BYTES] = {192,168,111,25};
	unsigned char ip_to_insert_res_7[IP_NUM_BYTES] = {192,168,111,100};
	
	
	
	test = DHCPCreate(subnet, num_of_bits_in_subnet);
	TestCount(test, 253);

	TestAllocateIp(test, ip_to_insert_1, ip_to_insert_res_1, SUCCESS);
	TestAllocateIp(test, ip_to_insert_2, ip_to_insert_res_2, SUCCESS);
	TestAllocateIp(test, ip_to_insert_3, ip_to_insert_res_3, SUCCESS);
	TestAllocateIp(test, ip_to_insert_4, ip_to_insert_res_4, SUCCESS);
	TestAllocateIp(test, ip_to_insert_5, ip_to_insert_res_5, SUCCESS);
	TestAllocateIp(test, ip_to_insert_6, ip_to_insert_res_6, SUCCESS);
	TestAllocateIp(test, ip_to_insert_7, ip_to_insert_res_7, SUCCESS);

	TestCount(test, 246);

	TestFreeIp(test, (unsigned char *)ip_to_insert_2, SUCCESS);
	TestFreeIp(test, (unsigned char *)ip_to_insert_2, FAILURE_DOUBLE_FREE);

	TestCount(test, 247);

	DHCPDestroy(test);
}


void TestCount (dhcp_t *test, size_t answer)
{
	static size_t test_num = 0;


	if (answer != DHCPCountFree(test))
	{
		printf("error in count test %ld \n", test_num);
		printf("worng count is: %ld \n", DHCPCountFree(test));
	}

	++test_num;
}


/*
void TestAllocateIp(dhcp_t *test, unsigned char request_ip[IP_NUM_BYTES], unsigned char answer[IP_NUM_BYTES])
{
	static size_t test_num = 0;


	if (!=)
	{
		printf("error in   test %ld \n", test_num);
	}

	++test_num;
}


*/

void TestFreeIp(dhcp_t *test, unsigned char request_ip_to_free[IP_NUM_BYTES], status_t answer_status)
{
	static size_t test_num = 0;
	status_t accepted_answer = DHCPFreeIP(test, request_ip_to_free);

	if (accepted_answer != answer_status)
	{
		printf("error in free ip test %ld \n", test_num);
	}

	++test_num;
}


void TestAllocateIp(dhcp_t *test, const unsigned char request_ip[IP_NUM_BYTES], unsigned char answer[IP_NUM_BYTES], status_t answer_status)
{
	static size_t test_num = 0;
	size_t i = 0;
	unsigned char out_param_array[IP_NUM_BYTES] = {0};
	status_t success = DHCPAllocateIP(test, request_ip, out_param_array);

	if(success != answer_status)
	{
		printf("error in Allocate Ip test %ld \n", test_num);
	}
	++test_num;

	for(i = 0; i < IP_NUM_BYTES; ++i)
	{	
		if (out_param_array[i] != answer[i])
		{
			printf("error in Allocate Ip test %ld \n", test_num);
		}
	}
	
	++test_num;
}
