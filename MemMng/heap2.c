#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include"heap2.h"

/*�궨��*/
#define configTOTAL_HEAP_SIZE 20*1024	//���������СΪ20KB
#define alignsize 8	//����8�ֽڶ���
#define heapMINIMUM_BLOCK_SIZE	( ( size_t ) ( heapStructSize * 2 ) )


/*����ȫ�ֱ���*/
static uint8_t ucHeap[configTOTAL_HEAP_SIZE];	
static Block_Link ListHead, ListTail; //���������ͷβ
static size_t FreeBytesRemaininings = configTOTAL_HEAP_SIZE;



/*���峣��*/
static const uint16_t heapStructSize = ((sizeof(Block_Link) + (alignsize - 1)) & ~0x001f);


/*�ڴ��ʼ������Ҫ������ʼ��ַ�Ķ���*/
static void	MemHeapInit(void)
{
	Block_Link* _pFirstFreeBlock;
	uint8_t* _AlignedStartAddr;

	/*8�ֽڶ���ķ�ʽ���ⲿ�ֲ��ù��ھ���*/
	_AlignedStartAddr = (uint8_t*)(((uint32_t) &ucHeap[alignsize]) & (~(uint32_t)(0x001f)));

	ListHead.pnextFreeBlock = (void*)_AlignedStartAddr;//���ڴ���������ͷָ���������ʵ��ַ
	ListHead.FreeBlockSize  = (size_t)0;//���������blockΪ0��ע��ǿת�����ֽ�

	ListTail.pnextFreeBlock = NULL;
	ListTail.FreeBlockSize  = configTOTAL_HEAP_SIZE - alignsize;

	_pFirstFreeBlock = (void*)_AlignedStartAddr;
	_pFirstFreeBlock->FreeBlockSize  = configTOTAL_HEAP_SIZE - alignsize;
	_pFirstFreeBlock->pnextFreeBlock = & ListTail;
}

/*����������뺯��*/
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


/*heap2�����ڴ�ʵ��*/
void *Heap2Malloc(size_t MallocOfSize)
{
	Block_Link* _pPreBlock;
	Block_Link* _pBlcok;
	Block_Link* _pNewBlcok;

	void* _pRtnAddr = NULL;

	MemHeapInit();//�ڴ��ʼ�����׵�ַ�ö���

	if (MallocOfSize > 0)				//������ڴ���Ҫ���ڴ���봦��
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
			_pRtnAddr = (void*)(((uint8_t*)_pPreBlock->pnextFreeBlock) + heapStructSize);//��һ����Ҫ�ǿ���ṹ���ͷ����������ʵ��ʹ�õ�ַ��ʼ��ֵ
			_pPreBlock->pnextFreeBlock = _pBlcok->pnextFreeBlock;//ɾ����ǰ��_pBlock
			

			/*�ж���������ڴ�ռ��Ƿ񻹿����ٲ�֣��ж�������*/
			if ((_pBlcok->FreeBlockSize - MallocOfSize) > heapMINIMUM_BLOCK_SIZE)
			{
				_pNewBlcok = (void*)(((uint8_t*)_pBlcok) + MallocOfSize);

				_pNewBlcok->FreeBlockSize = _pBlcok->FreeBlockSize - MallocOfSize;
				_pBlcok->FreeBlockSize = MallocOfSize;

				/*���²�ֳ�����block����ԭ���Ŀ��е�������ȥ*/
				NewBlcokInserIntoList(_pNewBlcok);
				FreeBytesRemaininings -= _pBlcok->FreeBlockSize;
			}
//		}

	}

	
	return _pRtnAddr;
}

