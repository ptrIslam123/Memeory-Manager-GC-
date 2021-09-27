#ifndef ALLOCATOR_ALLOCATOR_H
#define ALLOCATOR_ALLOCATOR_H

#include <stdlib.h>

#include "pointer.h"
#include "mem_block.h"

namespace mem {

/**
 * @brief Класс реализующий сущность аллокатор
 * @details Данный класс является уникальным (не копируемым), так как каждый алокатор должен владеть
 * уникальным указателем на блок памяти из буфера памяти.
 * @tparam T Тип данных, с которым аллокатор будет в дальнейшем работать
 */
template<typename T>
class Allocator {
public:
    /**
     * @brief Конструктор, инициализирует все локальные переменные класса, а именно memBufferInstance_
     * будет указывать на инстансе экземпляра буфера памяти.
     */
    Allocator();

    /**
     * @brief Деструктор класса
     */
    ~Allocator() = default;

    Allocator(const Allocator<T>& other) = delete;
    Allocator(Allocator<T>&& other) = delete;

    Allocator<T> operator=(const Allocator<T>& other) = delete;
    Allocator<T> operator=(Allocator<T>&& other) = delete;

    /**
     * @brief Аллоцирует память
     * @param size размер аллоцируемой памяти
     * @param pointer указатель на класс умный указатель, памятью которой он владеет
     * @return указатель на запрошенную память в случае успеха, nullptr иначе
     */
    T* allocate(size_t size, Pointer *pointer);

    /**
     * @brief Деаллоцирует память по переданному указателю
     * @param data Указатель на память
     * @param pointer Указатель на класс умный указатель, памятью которой он владеет
     */
    void deallocate(T *data, Pointer *pointer);

    /**
     * @brief Вызывает конструктор у объекта с переданными ему аргументами
     * @tparam Args Список типов
     * @param data Указатель на объект у которого надо вызвать конструктор
     * @param args список аргументов передаваемых в вызываемый конструктор объекта
     */
    template<typename ... Args>
    void construct(T *data, Args&& ... args);

    /**
     * @brief Вызывает деструктор у объекта
     * @param data Указатель на объект, у которого нужно вызвать деструктор
     */
    void destruct(T *data);

private:
    T *getData(MemBlock *memBlock);
    MemBlock* getMemBlock(T *data);

    MemBlock *memBlock_; //!< указатель на блок памяти, выделенный с помощью менеджера памяти
    MemBuffer *const memBufferInstance_; //!< Константный указатель на экземпляр менеджера памяти
};

template<typename T>
Allocator<T>::Allocator():
    memBlock_(nullptr), memBufferInstance_(&getMemBufferInstance()) {
}

template<typename T>
T *Allocator<T>::allocate(size_t size, Pointer *) {
    memBlock_ = memBufferInstance_->allocMemBlock(size);
    return getData(memBlock_);
}

template<typename T>
void Allocator<T>::deallocate(T *data, Pointer *) {
    memBufferInstance_->deallocateMemBlock(getMemBlock(data));
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
