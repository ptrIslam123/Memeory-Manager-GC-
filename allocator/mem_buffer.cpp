#include "mem_buffer.h"

namespace mem {

MemBuffer::MemBuffer(const size_t sizeBuff):
        begin_(nullptr),
        curFreeSpace_(nullptr),
        sizeBuff_(sizeBuff),
        countBlocks_(0)
{}

void MemBuffer::allocateBuffer() {
    begin_ = operator new(sizeBuff_);
    curFreeSpace_ = begin_;
}

MemBlock* MemBuffer::allocMemBlock(const size_t size) {
    const size_t totalSize = size + sizeof(MemBlock);

    if (isBufferOver(totalSize)) {
        return nullptr;
    }

    MemBlock* memBlock = nullptr;
    if (curFreeSpace_ == begin_) {
        memBlock = static_cast<MemBlock*>(begin_);
        curFreeSpace_ = (char*)curFreeSpace_ + totalSize;
    }else {
        memBlock = static_cast<MemBlock*>(curFreeSpace_);
        curFreeSpace_ = (char*)curFreeSpace_ + totalSize;
    }

    new (memBlock) MemBlock(size);
    sizeBuff_ -= totalSize;
    return memBlock;
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
    delete(begin_);

    begin_ = nullptr;
    curFreeSpace_ = nullptr;
    sizeBuff_ = 0;
    countBlocks_ = 0;
}


MemBlock::MemBlock(const size_t sizeBlock):
sizeBlock_(sizeBlock),
statusBlock_(freeBlock)
{}

size_t MemBlock::getSizeBlock() const {
    return sizeBlock_;
}

bool MemBlock::getStatusBlock() const {
    return statusBlock_;
}

}




