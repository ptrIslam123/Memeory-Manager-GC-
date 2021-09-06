#include "mem_buffer.h"

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
        new (newMemBlock) MemBlock(size, nullptr, static_cast<MemBlock*>(curFreeSpace_));
        curMemBlock_ = newMemBlock;
    }else {
        newMemBlock = static_cast<MemBlock*>(curFreeSpace_);
        curFreeSpace_ = (char*)curFreeSpace_ + totalSize;
        new (newMemBlock) MemBlock(size, curMemBlock_, static_cast<MemBlock*>(curFreeSpace_));
        curMemBlock_ = newMemBlock;
    }

    sizeBuff_ -= totalSize;
    return newMemBlock;
}

bool MemBuffer::isBufferOver(const size_t size) const {
    return (size > sizeBuff_);
}

void *MemBuffer::getBuffer() const {
    return begin_;
}

size_t MemBuffer::getSizeBuffer() const {
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

bool MemBuffer::unitTwoFreeMemBlockInOneMemBlock(MemBlock *const lBlock, MemBlock *const rBlock) {

    return true;
}


MemBlock::MemBlock(const size_t sizeBlock, MemBlock* prevBlock, MemBlock* nextBlock):
sizeBlock_(sizeBlock),
statusBlock_(unfreeBlock),
prevBlock_(prevBlock),
nextBlock_(nextBlock)
{}

size_t MemBlock::getSizeBlock() const {
    return sizeBlock_;
}

bool MemBlock::getStatusBlock() const {
    return statusBlock_;
}

void MemBlock::setSizeBlock(const size_t size) {
    sizeBlock_ = size;
}

void MemBlock::setStatusBlock(const bool status) {
    statusBlock_ = status;
}

void MemBlock::setPrevMemBlock(MemBlock *const memBlock) {
    prevBlock_ = memBlock;
}

void MemBlock::setNextMemBlock(MemBlock *const memBlock) {
    nextBlock_ = memBlock;
}

MemBlock *MemBlock::getPrevMemBlock() const {
    return prevBlock_;
}

MemBlock *MemBlock::getNextMemBlock() const {
    return nextBlock_;
}

}




