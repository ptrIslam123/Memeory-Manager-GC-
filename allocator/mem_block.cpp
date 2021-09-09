#include "mem_block.h"

#include "mem_buffer.h"

namespace mem {

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

} //namespace mem
