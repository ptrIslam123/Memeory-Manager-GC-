#ifndef UNTITLED1_MEM_BUFFER_H
#define UNTITLED1_MEM_BUFFER_H

#include <iostream>
#include <stdlib.h>

namespace mem {

class MemBuffer;
class MemBlock;

//! Значение означающее, что блок памяти не занят
constexpr bool freeBlock = true;
//! Значение означающее, что блок памяти занят
constexpr bool unfreeBlock = false;

/*
 * @brief Класс Буфер.
 * Содержит в себе все блоки памяти в программе
 */
class MemBuffer {
public:

    /*
     * @brief Инициализирует дефолтными значениями необходимые для работы класса переменные
     */
    explicit MemBuffer(const size_t sizeBuff);
    /*
     * @brief Уничтожает объекты раннее созданные для работы класса
     */
    ~MemBuffer();

    /*
     * @brief Выделает в heap`е буфер памяти, размера переданного через конструктор
     */
    void allocateBuffer();

    /*
     * @brief Аллоцирует в буфере новый блок памяти, если память позволяет
     * @return MemBlock* указатель на новый блок памяти в случае успеха
     * @return nullptr в случае не удачи
     */
    MemBlock* allocMemBlock(const size_t size);

    bool unitTwoFreeMemBlockInOneMemBlock(MemBlock *const lBlock, MemBlock *const rBlock);

    MemBlock* getPtrOnPrevMemBlock(MemBlock *const memBlock);
    MemBlock* getPtrOnNextMemBlock(MemBlock *const memBlock);
    MemBlock* getPtrOnFirstMemBlock();

    /*
     * @brief Проверяет, можем ли мы аллоцировать внутри буфера еще один блок памяти
     * @param размер памяти нужной нам
     * @return true, если есть еще место для нового блока памяти
     * @return false, если память уже не хватает для размещения нового
     */
    bool isBufferOver(const size_t size) const;

    /*
     * @brief Возвращает указатель на буфер
     * @return указатель на буфер
     */
    void* getBuffer() const;

    /*
     * @brief возвращает размер буфера памяти
     * @return размер буфера
     */
    size_t getSizeBuffer() const;

    /*
     * @brief возвращает количество блоков памяти уже аллоцированных в буфере
     * @return количество блоков памяти
     */
    size_t getCountBlocks() const;

private:
    friend MemBlock;
    //! Указатель на начало буфера памяти
    void* begin_;
    //! Указатель на память, находящуюся за последним блоком памяти в буфере
    void* curFreeSpace_;
    //!
    MemBlock* curMemBlock_;
    //! Размер буфера памяти
    size_t sizeBuff_;
    //! Количество созданных в буфере блоков памяти
    size_t countBlocks_;
};



class MemBlock {
public:
    explicit MemBlock(const size_t sizeBlock, MemBuffer* buffer, MemBlock* prevBlock, MemBlock* nextBlock);
    ~MemBlock() = default;

    void setSizeBlock(const size_t size);
    void setStatusBlock(const bool status);
    void setPrevMemBlock(MemBlock *const memBlock);
    void setNextMemBlock(MemBlock *const memBlock);

    size_t getSizeBlock() const;
    bool getStatusBlock() const;
    MemBlock* getPrevMemBlock() const;
    MemBlock* getNextMemBlock() const;

    bool isLastMemBlock() const;
    bool isFirstMemBlock() const;

private:
    size_t sizeBlock_;
    bool statusBlock_;
    MemBuffer* buffer_;
    MemBlock* prevBlock_;
    MemBlock* nextBlock_;
};

}

#endif //UNTITLED1_MEM_BUFFER_H
