#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include"heap5.h"


/*宏定义*/
#define configTOTAL_HEAP_SIZE 20*1024	//定义数组大小为20KB
#define alignsize 8	//定义8字节对齐
#define heapMINIMUM_BLOCK_SIZE	( ( size_t ) ( heapStructSize * 2 ) )


/*定义全局变量*/
static uint8_t ucHeap[configTOTAL_HEAP_SIZE];
static Block_Link ListHead, ListTail; //定义链表的头尾
static size_t FreeBytesRemaininings = configTOTAL_HEAP_SIZE;




/*1.内存初始化*/
static void MemHeapInit(void)
{




}


/*2.内存申请主函数*/
void* Heap5Malloc(size_t MallocOfSize)
{
	



}
