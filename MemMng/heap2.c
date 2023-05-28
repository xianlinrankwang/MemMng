#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include"heap2.h"

/*宏定义*/
#define configTOTAL_HEAP_SIZE 20*1024	//定义数组大小为20KB
#define alignsize 8	//定义8字节对齐
#define heapMINIMUM_BLOCK_SIZE	( ( size_t ) ( heapStructSize * 2 ) )


/*定义全局变量*/
static uint8_t ucHeap[configTOTAL_HEAP_SIZE];	
static Block_Link ListHead, ListTail; //定义链表的头尾
static size_t FreeBytesRemaininings = configTOTAL_HEAP_SIZE;



/*定义常量*/
static const uint16_t heapStructSize = ((sizeof(Block_Link) + (alignsize - 1)) & ~0x001f);


/*内存初始化，主要用于起始地址的对齐*/
static void	MemHeapInit(void)
{
	Block_Link* _pFirstFreeBlock;
	uint8_t* _AlignedStartAddr;

	/*8字节对齐的方式，这部分不用过于纠结*/
	_AlignedStartAddr = (uint8_t*)(((uint32_t) &ucHeap[alignsize]) & (~(uint32_t)(0x001f)));

	ListHead.pnextFreeBlock = (void*)_AlignedStartAddr;//将内存管理链表的头指向对齐后的其实地址
	ListHead.FreeBlockSize  = (size_t)0;//管理链表的block为0，注意强转成四字节

	ListTail.pnextFreeBlock = NULL;
	ListTail.FreeBlockSize  = configTOTAL_HEAP_SIZE - alignsize;

	_pFirstFreeBlock = (void*)_AlignedStartAddr;
	_pFirstFreeBlock->FreeBlockSize  = configTOTAL_HEAP_SIZE - alignsize;
	_pFirstFreeBlock->pnextFreeBlock = & ListTail;
}

/*空闲链表插入函数*/
void NewBlcokInserIntoList(Block_Link_t pxBlockToInsert)
{
	Block_Link* pxinteror;
	size_t BlockSize;

	BlockSize = pxBlockToInsert->FreeBlockSize;
	
	for (pxinteror = &ListHead; pxinteror->pnextFreeBlock->FreeBlockSize < BlockSize;
		pxinteror = pxinteror->pnextFreeBlock)
	{
		/*do nothing*/
	}

	pxBlockToInsert->pnextFreeBlock = pxinteror->pnextFreeBlock;
	pxinteror->pnextFreeBlock = pxBlockToInsert;
}


/*heap2申请内存实现*/
void *Heap2Malloc(size_t MallocOfSize)
{
	Block_Link* _pPreBlock;
	Block_Link* _pBlcok;
	Block_Link* _pNewBlcok;

	void* _pRtnAddr = NULL;

	MemHeapInit();//内存初始化，首地址得对齐

	if (MallocOfSize > 0)				//申请的内存需要做内存对齐处理
	{
		MallocOfSize += heapStructSize;

		if ((MallocOfSize & 0x001f) != 0)
		{
			MallocOfSize += (alignsize - (MallocOfSize & 0x001f));
		}
	}

	int i = 0;
	if ((MallocOfSize > 0) && (MallocOfSize < configTOTAL_HEAP_SIZE - alignsize))
	{
		_pPreBlock = &ListHead;
		_pBlcok = ListHead.pnextFreeBlock;

		while ((_pBlcok->FreeBlockSize < MallocOfSize) && (_pBlcok->pnextFreeBlock != NULL));
		{
			_pPreBlock = _pBlcok;
			_pBlcok    = _pBlcok->pnextFreeBlock;
			i++;

		}
		printf("i times%d\r\n", i);
		printf("addr %#x\r\n",_pBlcok );

//		if(_pBlcok != &ListTail)
//		{
		printf("running here!\r\n");
			_pRtnAddr = (void*)(((uint8_t*)_pPreBlock->pnextFreeBlock) + heapStructSize);//这一块主要是跨过结构体的头部，从他的实际使用地址开始赋值
			_pPreBlock->pnextFreeBlock = _pBlcok->pnextFreeBlock;//删掉当前的_pBlock
			

			/*判断新申请的内存空间是否还可以再拆分，判断条件：*/
			if ((_pBlcok->FreeBlockSize - MallocOfSize) > heapMINIMUM_BLOCK_SIZE)
			{
				_pNewBlcok = (void*)(((uint8_t*)_pBlcok) + MallocOfSize);

				_pNewBlcok->FreeBlockSize = _pBlcok->FreeBlockSize - MallocOfSize;
				_pBlcok->FreeBlockSize = MallocOfSize;

				/*把新拆分出来的block插入原来的空闲的链表中去*/
				NewBlcokInserIntoList(_pNewBlcok);
				FreeBytesRemaininings -= _pBlcok->FreeBlockSize;
			}
//		}

	}

	
	return _pRtnAddr;
}

