#ifndef ALLOCATOR_MEM_BLOCK_H
#define ALLOCATOR_MEM_BLOCK_H

#include <stdlib.h>
#include "mem_buffer.h"


namespace mem {

//! Значение означающее, что блок памяти не занят
constexpr bool freeBlock = true;
//! Значение означающее, что блок памяти занят
constexpr bool unfreeBlock = false;
//! Объявление класса буфера

class MemBlock {
public:
    explicit MemBlock(size_t sizeBlock, MemBuffer *buffer, MemBlock *prevBlock, MemBlock *nextBlock);
    ~MemBlock() = default;

    void setSizeBlock(size_t size);
    void setStatusBlock(bool status);
    void setPrevMemBlock(MemBlock *memBlock);
    void setNextMemBlock(MemBlock *memBlock);

    size_t getSizeBlock() const;
    bool getStatusBlock() const;
    MemBlock *getPrevMemBlock() const;
    MemBlock *getNextMemBlock() const;

    bool isLastMemBlock() const;
    bool isFirstMemBlock() const;

private:
    size_t sizeBlock_;
    bool statusBlock_;
    MemBuffer* buffer_;
    MemBlock* prevBlock_;
    MemBlock* nextBlock_;
};

MemBuffer &getMemBufferInstance();

} // namespace mem

#endif //ALLOCATOR_MEM_BLOCK_H
