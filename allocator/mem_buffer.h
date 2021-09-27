#ifndef UNTITLED1_MEM_BUFFER_H
#define UNTITLED1_MEM_BUFFER_H

#include <iostream>
#include <stdlib.h>

namespace mem {

//! Объявление класса блока памяти
class MemBlock;

/*
 * @brief Класс Буфер.
 * Содержит в себе все блоки памяти в программе
 */
class MemBuffer {
public:

    /*
     * @brief Инициализирует дефолтными значениями необходимые для работы класса переменные
     */
    explicit MemBuffer(size_t sizeBuff);
    /*
     * @brief Уничтожает объекты раннее созданные для работы класса
     */
    ~MemBuffer();

    /*
     * @brief Выделает буфер памяти, размера переданного через конструктор
     */
    void allocateBuffer();

    /*
     * @brief Аллоцирует в буфере новый блок памяти, если память позволяет
     * @return MemBlock* указатель на новый блок памяти в случае успеха
     * @return nullptr в случае не удачи
     */
    MemBlock* allocMemBlock(size_t size);

    /*
     * @brief Деаллоцирует в буфере переданный блок памяти
     *
     * @param memBlock Указатель на блок памяти, который нужно освободить
     * @return true в случае если блок памяти деаллоцировали
     * @return false иначе
     */
    bool deallocateMemBlock(MemBlock *memBlock);

    /*
     * @brief Объединяет два свободных блока в один блок суммарного размера
     *
     * @param lBlock Указатель на левый блок памяти
     * @param rBlock Указатель на правый блок памяти
     * @return размер объединенного блока памяти в случае успеха
     * @return 0, если хотя бы один из блоков памяти оказался занятым
     */
    size_t unitTwoFreeMemBlockInOneMemBlock(MemBlock *lBlock, MemBlock *rBlock);

    /*
     * @brief Объединяет два блока памяти не проверяя, свободны ли эти два блока
     *
     * @param lBlock Указатель на левый блок памяти
     * @param rBlock Указатель на правый блок памяти
     * @return размер объединенного блока памяти в случае успеха
     * @return 0, если хотя бы один из блоков памяти оказался занятым
     */
    size_t unitTwoBlockInOne(MemBlock *lBlock, MemBlock *rBlock);

    /*
     * @brief Получить указатель на предыдущий блок памяти
     *
     * @return Указатель на предыдущий блок памяти
     */
    MemBlock* getPrevMemBlock(MemBlock *memBlock);

    /*
    * @brief Получить указатель на следующий блок памяти
    *
    * @return Указатель на следующий блок памяти
    */
    MemBlock* getNextMemBlock(MemBlock *memBlock);

    /*
    * @brief Получить указатель на первый блок памяти
    *
    * @return Указатель на первый блок памяти
    */
    MemBlock* getFirstMemBlock();

    /*
    * @brief Получить указатель на последний блок памяти
    *
    * @return Указатель на последний блок памяти
    */
    MemBlock* getLastMemBlock();

    /*
     * @brief Проверяет, можем ли мы аллоцировать внутри буфера еще один блок памяти
     * @param размер памяти нужной нам
     * @return true, если есть еще место для нового блока памяти
     * @return false, если память уже не хватает для размещения нового
     */
    bool isBufferOver(size_t size) const;

    /*
     * @brief Возвращает указатель на буфер
     * @return указатель на буфер
     */
    void* getBuffer() const;

    /*
     * @brief возвращает размер буфера памяти
     * @return размер буфера
     */
    size_t getSizeFreeSpace() const;

    /*
     * @brief возвращает количество блоков памяти уже аллоцированных в буфере
     * @return количество блоков памяти
     */
    size_t getCountBlocks() const;

private:
    friend MemBlock;
    //! Указатель на начало буфера памяти
    void *begin_;
    //! Указатель на память, находящуюся за последним блоком памяти в буфере
    void *curFreeSpace_;
    //! Указатель на последний валидный блок памяти в буфере
    MemBlock *lastMemBlock_;
    //! Размер буфера памяти
    size_t sizeBuff_;
    //! Количество созданных в буфере блоков памяти
    size_t countBlocks_;
};


MemBuffer& getMemBuffer();

} //namespace mem

#endif //UNTITLED1_MEM_BUFFER_H
