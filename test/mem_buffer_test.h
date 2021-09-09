#ifndef ALLOCATOR_MEM_BUFFER_TEST_H
#define ALLOCATOR_MEM_BUFFER_TEST_H

#include <assert.h>
#include <stdlib.h>

#include "../allocator/mem_buffer.h"

void allocMemBlockTest(size_t sizeBuff, size_t sizeMemBlock);
void iterationByMemBufferTest(size_t sizeBuff);
void printBlock(const mem::MemBlock* block, const std::string blockType = "block");

#endif //ALLOCATOR_MEM_BUFFER_TEST_H
