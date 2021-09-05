#ifndef UNTITLED1_MEM_BUFFER_H
#define UNTITLED1_MEM_BUFFER_H

#include <iostream>
#include <stdlib.h>

namespace mem {

class MemBuffer;
class MemBlock;

constexpr bool freeBlock = true;
constexpr bool unfreeBlock = false;


class MemBuffer {
public:
    explicit MemBuffer(const size_t sizeBuff);
    ~MemBuffer() = default;

    void allocateBuffer();
    MemBlock* allocMemBlock(const size_t size);

    bool isBufferOver(const size_t size) const;
    void* getBuffer() const;
    size_t getSizeBuffer() const;
    size_t getCountBlocks() const;

private:
    void* begin_;
    void* curFreeSpace_;
    size_t sizeBuff_;
    size_t countBlocks_;
};



class MemBlock {
public:
    MemBlock(const size_t sizeBlock);
    ~MemBlock() = default;

    size_t getSizeBlock() const;
    bool getStatusBlock() const;

private:
    size_t sizeBlock_;
    bool statusBlock_;
};

}

#endif //UNTITLED1_MEM_BUFFER_H
