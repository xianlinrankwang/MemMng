#ifndef HEAP5_H
#define HEAP5_H

struct BLOCK
{
	struct BLOCK* pnextFreeBlock;	//���е�block����һ��block
	size_t FreeBlockSize;	//���е�block�Ĵ�С
};

typedef struct BLOCK Block_Link;
typedef struct BLOCK* Block_Link_t;

void* Heap5Malloc(size_t MallocOfSize);






#endif // !HEAP_H