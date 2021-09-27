#ifndef ALLOCATOR_SMART_PTR_H
#define ALLOCATOR_SMART_PTR_H

#include "pointer.h"
#include "allocator.h"

namespace mem {

/**
 * @brief Класс реализующий сущность умных указателей
 * @tparam T Тип данных, на который будет указывать данный класс
 * @tparam SmartPtrType Тип тип умных указателей(SafeSmartPointer or NoSafeSmartPointer)
 * @tparam AllocatorType Тип аллокатора
 */
template<typename T, typename SmartPtrType, typename AllocatorType = Allocator<T>>
class SmartPtr : public Pointer {
public:
    /**
     * @brief Конструктор по умолчанию.
     * @details  Инициализирует все переменные по умолчанию, указатель на данные nullptr
     */
    SmartPtr();
    /**
     * @brief Конструктор, конструирует умный указатель значением Т
     * @param value Значение, на которое будет указывать указатель
     */
    explicit SmartPtr(const T &value);

    /**
     * @brief Деструктор, очищает память под данные
     */
    ~SmartPtr();

    SmartPtr(const SmartPtr &other);
    SmartPtr(SmartPtr &&other);

    void operator=(const T &value);
    void operator=(T &&value);

    void operator=(const SmartPtr &other);
    void operator=(SmartPtr &&other);

    /**
     *  @brief Перегружает оператор *
     * @return ссылку на объект типа Т
     */
    T& operator*();

    /**
     * @brief Перегружает оператор ->
     * @return Указатель на объект Т
     */
    T* operator->();

private:
    void *getPointer() override;
    void setPointer(void *ptr) override;

    AllocatorType allocator_; //!< Объект аллокатор
    SmartPtrType checkPointer_; //!< Объект тип умного указателя
    T *data_; //!< Указатель на данные объекта, который хранит умный указатель
};

template<typename T, typename SmartPtrType, typename AllocatorType>
SmartPtr<T, SmartPtrType, AllocatorType>::SmartPtr():
    allocator_(),
    checkPointer_(),
    data_(nullptr) {
}

template<typename T, typename SmartPtrType, typename AllocatorType>
SmartPtr<T, SmartPtrType, AllocatorType>::SmartPtr(const T &value):
    allocator_(),
    checkPointer_(),
    data_(nullptr) {
    data_ = allocator_.allocate(sizeof (T), this);
    allocator_.construct(data_, value);
}

template<typename T, typename SmartPtrType, typename AllocatorType>
SmartPtr<T, SmartPtrType, AllocatorType>::~SmartPtr() {
    if (data_ != nullptr) {
        allocator_.destruct(data_);
        allocator_.deallocate(data_, this);
        data_ = nullptr;
    }
}

template<typename T, typename SmartPtrType, typename AllocatorType>
SmartPtr<T, SmartPtrType, AllocatorType>::SmartPtr(const SmartPtr &other) {
}

template<typename T, typename SmartPtrType, typename AllocatorType>
SmartPtr<T, SmartPtrType, AllocatorType>::SmartPtr(SmartPtr &&other) {
}

template<typename T, typename SmartPtrType, typename AllocatorType>
void SmartPtr<T, SmartPtrType, AllocatorType>::operator=(const T &value) {
    data_ = allocator_.allocate(sizeof (T), this);
    allocator_.construct(data_, value);
}

template<typename T, typename SmartPtrType, typename AllocatorType>
void SmartPtr<T, SmartPtrType, AllocatorType>::operator=(T &&value) {
    data_ = allocator_.allocate(sizeof (T), this);
    allocator_.construct(data_, std::move(value));
}

template<typename T, typename SmartPtrType, typename AllocatorType>
void SmartPtr<T, SmartPtrType, AllocatorType>::operator=(const SmartPtr &other) {
}

template<typename T, typename SmartPtrType, typename AllocatorType>
void SmartPtr<T, SmartPtrType, AllocatorType>::operator=(SmartPtr &&other) {
}

template<typename T, typename SmartPtrType, typename AllocatorType>
void *SmartPtr<T, SmartPtrType, AllocatorType>::getPointer() {
    return nullptr;
}

template<typename T, typename SmartPtrType, typename AllocatorType>
void SmartPtr<T, SmartPtrType, AllocatorType>::setPointer(void *ptr) {
}

template<typename T, typename SmartPtrType, typename AllocatorType>
T& SmartPtr<T, SmartPtrType, AllocatorType>::operator*() {
    checkPointer_.checkPoint(data_);
    return *data_;
}

template<typename T, typename SmartPtrType, typename AllocatorType>
T *SmartPtr<T, SmartPtrType, AllocatorType>::operator->() {
    checkPointer_.checkPoint(data_);
    return data_;
}

}

#endif //ALLOCATOR_SMART_PTR_H
