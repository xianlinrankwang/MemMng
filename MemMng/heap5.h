#ifndef HEAP5_H
#define HEAP5_H

struct BLOCK
{
	struct BLOCK* pnextFreeBlock;	//空闲的block的下一个block
	size_t FreeBlockSize;	//空闲的block的大小
};

typedef struct BLOCK Block_Link;
typedef struct BLOCK* Block_Link_t;

void* Heap5Malloc(size_t MallocOfSize);






#endif // !HEAP_H