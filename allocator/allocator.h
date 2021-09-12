#ifndef ALLOCATOR_ALLOCATOR_H
#define ALLOCATOR_ALLOCATOR_H

#include <stdlib.h>

#include "pointer.h"
#include "mem_block.h"

namespace mem {

template<typename T>
class Allocator {
public:
    Allocator();
    ~Allocator() = default;

    Allocator(const Allocator<T>& other) = delete;
    Allocator(Allocator<T>&& other) = delete;

    Allocator<T> operator= (const Allocator<T>& other) = delete;
    Allocator<T> operator= (Allocator<T>&& other) = delete;

    T* allocate(size_t size, Pointer *pointer);
    void deallocate(T *data, Pointer *pointer);

    template<typename ... Args>
    void construct(T *data, Args&& ... args);
    void destruct(T *data);

private:
    T *getData(MemBlock *memBlock);
    MemBlock* getMemBlock(T *data);

private:
    MemBlock *memBlock_;
};

template<typename T>
Allocator<T>::Allocator():
    memBlock_(nullptr) {
}

template<typename T>
T *Allocator<T>::allocate(size_t size, Pointer *) {
    memBlock_ = getMemBufferInstance().allocMemBlock(size);
    return getData(memBlock_);
}

template<typename T>
void Allocator<T>::deallocate(T *data, Pointer *) {
    getMemBufferInstance().deallocateMemBlock(getMemBlock(data));
}

template<typename T>
template<typename... Args>
void Allocator<T>::construct(T *data, Args &&... args) {
    new (data) T(std::forward<Args ...>(args ...));
}

template<typename T>
void Allocator<T>::destruct(T *data) {
    data->~T();
}


template<typename T>
T *Allocator<T>::getData(MemBlock *memBlock) {
    return (T*)((char*)memBlock + memBlock->getSizeBlock());
}

    template<typename T>
    MemBlock *Allocator<T>::getMemBlock(T *data) {
        return (MemBlock*)((char*)data - memBlock_->getSizeBlock());
    }

}

#endif //ALLOCATOR_ALLOCATOR_H
