#ifndef ALLOCATOR_MEM_BLOCK_H
#define ALLOCATOR_MEM_BLOCK_H

#include <cstdlib>

namespace mem {

//! Значение означающее, что блок памяти не занят
constexpr bool freeBlock = true;
//! Значение означающее, что блок памяти занят
constexpr bool unfreeBlock = false;
//! Объявление класса буфера

//! Объявление типа класса блок памяти
class MemBlock;

//!
class MemBuffer;

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
 * @param ptr Указатель на указатель объекта данных
 * @return Возвращает указатель на объект типа блок памяти
 */
MemBlock *getMemBlock(void **ptr);

/**
 * @brief Класс определяющий сущность блок(кусочек) памяти в буфере
 * @details Каждый кусочек памяти состоит из 2-х частей,
 * хедера с информацией о куске памяти и самой памяти под данные
 *
 *      struct MemBlock
 *
 *      |-----------|
 *      | sizeBlock | Размер блока памяти целиком без хедера с информацией о блоке
 *      |-----------|
 *      |statusBlock| Статус блока (свободный/занятый)
 *      |-----------|
 *      | *buffer   | Указатель на сам буфер
 *      |-----------|
 *      |*prevBlock | Указатель на предыдущий блок памяти в буфере
 *      |-----------|
 *      |*nextBlock | Указатель на следующий блок памяти в буфере
 *      |-----------|
 *      |   DATA    | Сами данные
 *      |-----------|
 *
 */
class MemBlock {
public:
    /**
     * @brief Класс реализующий сущность блока(кусочка) памяти в буфере
     * @param sizeBlock Размер блока памяти
     * @param buffer Указатель на буфер
     * @param prevBlock Указатель на предыдущий блок памяти
     * @param nextBlock Указатель на следующий блок памяти
     */
    explicit MemBlock(size_t sizeBlock, MemBuffer *buffer, MemBlock *prevBlock, MemBlock *nextBlock);

    /**
     * @brief Деструктор блока памяти
     */
    ~MemBlock() = default;

    /**
     * @brief Устанавливает размер блока памяти
     * @param size Размер блока
     */
    void setSizeBlock(size_t size);

    /**
     * @brief Устанавливает статус блока
     * @param status Статус блока
     */
    void setStatusBlock(bool status);

    /**
     * @brief Устанавливает указатель на предыдущий блок памяти
     * @param memBlock Указатель на предыдущий блок памяти
     */
    void setPrevMemBlock(MemBlock *memBlock);

    /**
     * @brief Устанавливает указатель на следующий блок памяти
     * @param memBlock Указатель на следующий блок памяти
     */
    void setNextMemBlock(MemBlock *memBlock);

    /**
     * @brief Возвращает размер блока памяти
     * @return Размер блока памяти
     */
    size_t getSizeBlock() const;

    /**
     * @brief Возвращает статус блока памяти
     * @return Статус
     */
    bool getStatusBlock() const;

    /**
     * @brief Возвращает указатель на предыдущий блок памяти
     * @return Указатель на предыдущий блок памяти
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

} // namespace mem

#endif //ALLOCATOR_MEM_BLOCK_H
