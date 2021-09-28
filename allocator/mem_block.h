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

//! Объявление типа класса блок памяти
class MemBlock;

/**
 * @brief Шаблонный метод для получения указателя на данные из объекта блок памяти
 * @tparam T Тип указателя на данные
 * @param block Указатель на указатель на объект типа блок памяти
 * @return Возвращает указатель на данные
 */
template<class T>
T *getData(MemBlock **block);

/**
 * @brief Шаблонная функция для получения указателя на объект типа блок памяти
 * @tparam T Тип указателя на указатель данных объекта
 * @param ptr Указатель на указатель объекта данных
 * @return Возвращает указатель на объект типа блок памяти
 */
template<class T>
MemBlock *getMemBlock(T **ptr);

/**
 * @brief Класс определяющий сущность блок(кусочек) памяти в буфере
 * @details Каждый кусочек памяти состоит из 2-х частей,
 * хедера с информацией о куске памяти и самой памяти под данные
 *
 *      struct MemBlock
 *
 *      |-----------|
 *      | sizeBlock |
 *      |-----------|
 *      |statusBlock|
 *      |-----------|
 *      | *buffer   |
 *      |-----------|
 *      |*prevBlock |
 *      |-----------|
 *      |*nextBlock |
 *      |-----------|
 *      |   DATA    |
 *      |-----------|
 *      |           |
 *      |    .      |
 *      |    .      |
 *      |    .      |
 *      |-----------|
 *
 */
class MemBlock {
public:
    /**
     * @brief
     * @param sizeBlock
     * @param buffer
     * @param prevBlock
     * @param nextBlock
     */
    explicit MemBlock(size_t sizeBlock, MemBuffer *buffer, MemBlock *prevBlock, MemBlock *nextBlock);

    /**
     * @brief
     */
    ~MemBlock() = default;

    /**
     * @brief
     * @param size
     */
    void setSizeBlock(size_t size);

    /**
     * @brief
     * @param status
     */
    void setStatusBlock(bool status);

    /**
     * @brief
     * @param memBlock
     */
    void setPrevMemBlock(MemBlock *memBlock);

    /**
     * @brief
     * @param memBlock
     */
    void setNextMemBlock(MemBlock *memBlock);

    /**
     * @brief
     * @return
     */
    size_t getSizeBlock() const;

    /**
     * @brief
     * @return
     */
    bool getStatusBlock() const;

    /**
     * @brief
     * @return
     */
    MemBlock *getPrevMemBlock() const;

    /**
     * @brief
     * @return
     */
    MemBlock *getNextMemBlock() const;

    /**
     * @brief
     * @return
     */
    bool isLastMemBlock() const;

    /**
     * @brief
     * @return
     */
    bool isFirstMemBlock() const;

private:
    size_t sizeBlock_;
    bool statusBlock_;
    MemBuffer *buffer_;
    MemBlock *prevBlock_;
    MemBlock *nextBlock_;
};



template<class T>
T *getData(MemBlock **block) {
    return (T*)((char*)(*block) + sizeof (MemBlock));
}


template<class T>
MemBlock *getMemBlock(T **ptr) {
    return (MemBlock*)((char*)(*ptr) - sizeof (MemBlock));
}

MemBuffer &getMemBufferInstance();

} // namespace mem

#endif //ALLOCATOR_MEM_BLOCK_H
