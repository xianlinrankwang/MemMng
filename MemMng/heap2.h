#ifndef HEAP2_H
#define HEAP2_H

struct BLOCK
{
	struct BLOCK* pnextFreeBlock;	//���е�block����һ��block
	size_t FreeBlockSize;	//���е�block�Ĵ�С
};

typedef struct BLOCK Block_Link;
typedef struct BLOCK *Block_Link_t;

void* Heap2Malloc(size_t MallocOfSize);






#endif // !HEAP_H
