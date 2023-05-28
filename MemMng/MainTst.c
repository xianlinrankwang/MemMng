#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include "heap2.h"


int main(void)
{
	uint8_t* buffer = NULL;

	uint8_t MallocOFSize = 1;


//	scanf("%d", &MallocOFSize);
	

	buffer = Heap2Malloc(100);

	printf("申请到的内存地址为：%#x\r\n",buffer);

	return 0;

}