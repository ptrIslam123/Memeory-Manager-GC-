#include "tests.h"

#include "../allocator/mem_buffer.h"

using namespace mem;

void allocMemBlockTest(size_t sizeBuff, size_t sizeMemBlock) {
    MemBuffer buf(sizeBuff);
    buf.allocateBuffer();
    size_t counter = 0;

    for (int i = 0; i < 10; i++) {
        MemBlock* block = buf.allocMemBlock(sizeMemBlock);
        if (block == nullptr) {
            break;
        }
        assert(sizeMemBlock == block->getSizeBlock());
        counter++;
    }

    assert(counter != sizeBuff/sizeMemBlock);
}