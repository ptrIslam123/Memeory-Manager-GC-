#include <iostream>
#include "allocator/mem_buffer.h"
#include "test/tests.h"

void printBlock(const mem::MemBlock* block, const std::string blockType = "block") {
    if (block == nullptr) {
        return;
    }

    if (blockType == "block") {
        std::cout << "{\n";
        std::cout << "block.size : " << block->getSizeBlock() << "\n"
                  << "block.status : " << block->getStatusBlock() << "\n";
        printBlock(block->getPrevMemBlock(), "prevBlock");
        printBlock(block->getNextMemBlock(), "nextBlock");

        std::cout << "\n}\n";
    } else {
        std::cout << "\t" << blockType << ".size : " << block->getSizeBlock() << "\n"
                  << "\t" << blockType <<  ".status : " << block->getStatusBlock() << "\n";
    }
}


int main() {

    using namespace mem;

    MemBuffer buff(200);
    buff.allocateBuffer();

    MemBlock* b1 = buff.allocMemBlock(10);
    MemBlock* b2 = buff.allocMemBlock(20);

    if (b2->isLastMemBlock()) {
        std::cout << "last blcok\n";
    } else {
        std::cout << "don`t last block\n";
    }

    return 0;
}
