#include "mem_buffer_test.h"

using namespace mem;

void deallocateMemBlockTest() {
    MemBuffer buf(600);
    buf.allocateBuffer();

    MemBlock *b1 = buf.allocMemBlock(10);
    MemBlock *b2 = buf.allocMemBlock(20);
    MemBlock *b3 = buf.allocMemBlock(30);
    MemBlock *b4 = buf.allocMemBlock(40);
    MemBlock *b5 = buf.allocMemBlock(50);
    MemBlock *b6 = buf.allocMemBlock(60);

    const size_t b1Size = b1->getSizeBlock();
    const size_t b2Size = b2->getSizeBlock();
    const size_t b3Size = b3->getSizeBlock();
    const size_t b4Size = b4->getSizeBlock();
    const size_t b5Size = b5->getSizeBlock();
    const size_t b6Size = b6->getSizeBlock();

    buf.deallocateMemBlock(b1);
    buf.deallocateMemBlock(b2);

    buf.deallocateMemBlock(b4);
    buf.deallocateMemBlock(b5);
    buf.deallocateMemBlock(b6);

    assert(b1->getStatusBlock() == freeBlock);
    assert(b2->getStatusBlock() == freeBlock);
    assert(b3->getStatusBlock() == unfreeBlock);
    assert(b4->getStatusBlock() == freeBlock);
    assert(b5->getStatusBlock() == freeBlock);
    assert(b1->getSizeBlock() == (b1Size + b2Size));
    assert(b4->getSizeBlock() == (b4Size + b5Size + b6Size));
}

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