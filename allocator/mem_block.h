#ifndef ALLOCATOR_MEM_BLOCK_H
#define ALLOCATOR_MEM_BLOCK_H

#include <stdlib.h>

namespace mem {

//! Значение означающее, что блок памяти не занят
constexpr bool freeBlock = true;
//! Значение означающее, что блок памяти занят
constexpr bool unfreeBlock = false;
//! Объявление класса буфера
class MemBuffer;

class MemBlock {
public:
    explicit MemBlock(const size_t sizeBlock, MemBuffer *buffer, MemBlock *prevBlock, MemBlock *nextBlock);
    ~MemBlock() = default;

    void setSizeBlock(const size_t size);
    void setStatusBlock(const bool status);
    void setPrevMemBlock(MemBlock *const memBlock);
    void setNextMemBlock(MemBlock *const memBlock);

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

} // namespace mem



#endif //ALLOCATOR_MEM_BLOCK_H
