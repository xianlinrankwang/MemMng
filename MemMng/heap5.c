#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include"heap5.h"


/*�궨��*/
#define configTOTAL_HEAP_SIZE 20*1024	//���������СΪ20KB
#define alignsize 8	//����8�ֽڶ���
#define heapMINIMUM_BLOCK_SIZE	( ( size_t ) ( heapStructSize * 2 ) )


/*����ȫ�ֱ���*/
static uint8_t ucHeap[configTOTAL_HEAP_SIZE];
static Block_Link ListHead, ListTail; //���������ͷβ
static size_t FreeBytesRemaininings = configTOTAL_HEAP_SIZE;




/*1.�ڴ��ʼ��*/
static void MemHeapInit(void)
{




}


/*2.�ڴ�����������*/
void* Heap5Malloc(size_t MallocOfSize)
{
	



}
