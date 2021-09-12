#include "mem_buffer.h"

#include "mem_block.h"

namespace mem {

MemBuffer::MemBuffer(const size_t sizeBuff):
        begin_(nullptr),
        curFreeSpace_(nullptr),
        sizeBuff_(sizeBuff),
        countBlocks_(0)
{}

void MemBuffer::allocateBuffer() {
    begin_ = malloc(sizeBuff_);
    curFreeSpace_ = begin_;
}

MemBlock* MemBuffer::allocMemBlock(const size_t size) {
    const size_t totalSize = size + sizeof(MemBlock);

    if (isBufferOver(totalSize)) {
        return nullptr;
    }

    MemBlock* newMemBlock = nullptr;

    if (curFreeSpace_ == begin_) {
        newMemBlock = static_cast<MemBlock*>(begin_);
        curFreeSpace_ = (char*)curFreeSpace_ + totalSize;
        new (newMemBlock) MemBlock(size, this, nullptr, static_cast<MemBlock*>(curFreeSpace_));
        lastMemBlock_ = newMemBlock;
    }else {
        newMemBlock = static_cast<MemBlock*>(curFreeSpace_);
        curFreeSpace_ = (char*)curFreeSpace_ + totalSize;
        new (newMemBlock) MemBlock(size, this, lastMemBlock_, static_cast<MemBlock*>(curFreeSpace_));
        lastMemBlock_ = newMemBlock;
    }

    sizeBuff_ -= totalSize;
    countBlocks_++;
    return newMemBlock;
}

bool MemBuffer::deallocateMemBlock(MemBlock *memBlock) {
    if (memBlock->getStatusBlock() == freeBlock) {
        return false;
    }

    memBlock->setStatusBlock(freeBlock);
    if (!memBlock->isFirstMemBlock()) {
        return unitTwoFreeMemBlockInOneMemBlock(memBlock->getPrevMemBlock(), memBlock);
    } else if (!memBlock->isLastMemBlock()) {
        return unitTwoFreeMemBlockInOneMemBlock(memBlock, memBlock->getNextMemBlock());
    } else {
        return false;
    }
}

bool MemBuffer::isBufferOver(const size_t size) const {
    return (size > sizeBuff_);
}

void *MemBuffer::getBuffer() const {
    return begin_;
}

size_t MemBuffer::getSizeFreeSpace() const {
    return sizeBuff_;
}

size_t MemBuffer::getCountBlocks() const {
    return countBlocks_;
}

MemBuffer::~MemBuffer() {
    free(begin_);

    begin_ = nullptr;
    curFreeSpace_ = nullptr;
    sizeBuff_ = 0;
    countBlocks_ = 0;
}

size_t MemBuffer::unitTwoFreeMemBlockInOneMemBlock(MemBlock *const lBlock, MemBlock *const rBlock) {
    if (lBlock->getStatusBlock() == unfreeBlock || rBlock->getStatusBlock() == unfreeBlock) {
        return 0;
    }

    if (rBlock->isLastMemBlock()) {
        lastMemBlock_ = lBlock;
    }
    return unitTwoBlockInOne(lBlock, rBlock);
}

size_t MemBuffer::unitTwoBlockInOne(MemBlock *const lBlock, MemBlock *const rBlock) {
    const size_t sizeUnitMemBlock = lBlock->getSizeBlock() + rBlock->getSizeBlock();
    lBlock->setSizeBlock(sizeUnitMemBlock);
    lBlock->setNextMemBlock(rBlock->getNextMemBlock());
    MemBlock* nextBlock = rBlock->getNextMemBlock();
    nextBlock->setPrevMemBlock(lBlock);
    countBlocks_--;
    return sizeUnitMemBlock;
}

MemBlock *MemBuffer::getPrevMemBlock(MemBlock *const memBlock) {
    return memBlock->getPrevMemBlock();
}

MemBlock *MemBuffer::getNextMemBlock(MemBlock *const memBlock) {
    return memBlock->getNextMemBlock();
}

MemBlock *MemBuffer::getFirstMemBlock() {
    return static_cast<MemBlock*>(begin_);
}

MemBlock* MemBuffer::getLastMemBlock() {
    return lastMemBlock_;
}


MemBuffer &getMemBufferInstance() {
    static constexpr size_t sizeBuffer = 1024;
    static mem::MemBuffer buffer(sizeBuffer);
    static bool isInitBuffer = false;

    if (!isInitBuffer) {
        buffer.allocateBuffer();
        isInitBuffer = true;
    }
    return buffer;
}

} //namespace mem
