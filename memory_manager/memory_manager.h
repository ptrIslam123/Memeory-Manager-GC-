#ifndef ALLOCATOR_MEMORY_MANAGER_H
#define ALLOCATOR_MEMORY_MANAGER_H

#include "../allocator/mem_buffer.h"
#include "../allocator/mem_block.h"

namespace mem {

constexpr size_t sizeMemoryManager = 100;

template<size_t N>
class MemoryManager {
public:
    MemoryManager();

    MemBlock *allocateMemory(size_t sizeByte);
    void deallocateMemory(void **ptr);
    static constexpr size_t size();

private:
    enum class ActiveBuffer {
        First_buffer,
        Second_buffer
    };

    void swapBuffers();
    MemBuffer *getActiveBuffer();
    void moveMemoryRegion();

    constexpr static size_t sizeBuffer = N;
    MemBuffer firstBuffer_;
    MemBuffer secondBuffer_;
    ActiveBuffer activeBuffer_;
};

template<size_t N>
MemoryManager<N>::MemoryManager():
        firstBuffer_(N),
        secondBuffer_(N),
        activeBuffer_(ActiveBuffer::First_buffer){
            firstBuffer_.allocateBuffer();
            secondBuffer_.allocateBuffer();
}

template<size_t N>
MemBlock *MemoryManager<N>::allocateMemory(size_t sizeByte) {
    MemBlock *freeMemBlock = getActiveBuffer()->allocMemBlock(sizeByte);;
    if (freeMemBlock != nullptr) {
        return freeMemBlock;
    }

    swapBuffers();
    return getActiveBuffer()->allocMemBlock(sizeByte);
}

template<size_t N>
void MemoryManager<N>::deallocateMemory(void **ptr) {
    getActiveBuffer()->deallocateMemBlock(getMemBlock(ptr));
}

template<size_t N>
void MemoryManager<N>::swapBuffers() {
    if (activeBuffer_ == ActiveBuffer::First_buffer) {

    } else {

    }
}

template<size_t N>
void MemoryManager<N>::moveMemoryRegion() {

}

template<size_t N>
MemBuffer *MemoryManager<N>::getActiveBuffer()  {
    switch (activeBuffer_) {
        case ActiveBuffer::First_buffer:
            return &(firstBuffer_);
        case ActiveBuffer::Second_buffer:
            return &(secondBuffer_);
        default:
            return nullptr;
    }
}

template<size_t N>
constexpr size_t MemoryManager<N>::size() {
    return sizeBuffer;
}

MemoryManager<sizeMemoryManager>& getMemoryManagerInstance() {
    static MemoryManager<sizeMemoryManager> memoryManager;
    return memoryManager;
}

} //namespace mem

#endif //ALLOCATOR_MEMORY_MANAGER_H
