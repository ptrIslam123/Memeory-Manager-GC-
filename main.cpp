#include <iostream>
#include "allocator/mem_buffer.h"
#include "test/mem_buffer_test.h"




int main() {

    using namespace mem;

    MemBuffer buf(300);
    buf.allocateBuffer();

    MemBlock* b1 = buf.allocMemBlock(10);
    MemBlock* b2 = buf.allocMemBlock(20);
    MemBlock* b3 = buf.allocMemBlock(15);

    b1->setStatusBlock(true);
    b2->setStatusBlock(true);

    const size_t b1Size = b1->getSizeBlock();
    const size_t b2Size = b2->getSizeBlock();

    if (buf.unitTwoFreeMemBlockInOneMemBlock(b1, b2) == 0) {
        std::cout << "erorr\n";
        return -1;
    }
    std::cout << "newB1Size : " << b1->getSizeBlock() << "\n";


    MemBlock* it = buf.getFirstMemBlock();
    while (!it->isLastMemBlock()) {
        printBlock(it);
        it = it->getNextMemBlock();
    }

    printBlock(it);


    return 0;
}
