#include "mem_buffer_test.h"

using namespace mem;

void iterationByMemBufferTest(size_t sizeBuff)
{
    MemBuffer buff(sizeBuff);
    buff.allocateBuffer();

    for (size_t i = 0; i < 10000; ++i) {
        MemBlock* block = buff.allocMemBlock(rand() % 50);
        if (block == nullptr) {
            break;
        }
        printBlock(block);
    }

    const size_t blockCount = buff.getCountBlocks();
    std::cout << "blockCounts : " << blockCount << "\n\n\n";
    MemBlock* it = buff.getFirstMemBlock();
    size_t counter = 0;
    while (!it->isLastMemBlock()) {
        printBlock(it);
        it = it->getNextMemBlock();
        counter++;
    }

    assert(counter != blockCount);
}

void allocMemBlockTest(size_t sizeBuff, size_t sizeMemBlock) {
    MemBuffer buf(sizeBuff);
    buf.allocateBuffer();
    size_t counter = 0;

    for (int i = 0; i < 10; ++i) {
        MemBlock* block = buf.allocMemBlock(sizeMemBlock);
        if (block == nullptr) {
            break;
        }
        assert(sizeMemBlock == block->getSizeBlock());
        counter++;
    }

    assert(counter != sizeBuff/sizeMemBlock);
}

void printBlock(const mem::MemBlock* block, const std::string blockType) {
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