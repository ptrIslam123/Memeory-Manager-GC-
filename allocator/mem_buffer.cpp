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

size_t MemBuffer::unitTwoFreeMemBlockInOneMemBlock(MemBlock *const lBlock, MemBlock *const rBlock) {
    if (lBlock->getStatusBlock() == unfreeBlock || rBlock->getStatusBlock() == unfreeBlock) {
        return 0;
    }
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


    MemBlock::MemBlock(const size_t sizeBlock, MemBuffer* buffer, MemBlock* prevBlock, MemBlock* nextBlock):
sizeBlock_(sizeBlock),
statusBlock_(unfreeBlock),
buffer_(buffer),
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

bool MemBlock::isLastMemBlock() const {
    return (this == buffer_->lastMemBlock_);
}

bool MemBlock::isFirstMemBlock() const {
    return (char*)this == (char*)(buffer_->begin_);
}

}




