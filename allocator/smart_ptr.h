#ifndef ALLOCATOR_SMART_PTR_H
#define ALLOCATOR_SMART_PTR_H

#include "pointer.h"
#include "allocator.h"

namespace mem {

template<typename T, typename SmartPtrType, typename AllocatorType = Allocator<T>>
class SmartPtr : public Pointer {
public:
    explicit SmartPtr(const T &value);
    SmartPtr(const SmartPtr<T, SmartPtrType, AllocatorType> &other) = delete;
    SmartPtr(SmartPtr<T, SmartPtrType, AllocatorType> &&other) = delete;
    ~SmartPtr();

    SmartPtr<T, SmartPtrType, AllocatorType> operator= (const SmartPtr<T, SmartPtrType, AllocatorType> &other) = delete;
    SmartPtr<T, SmartPtrType, AllocatorType> operator= (SmartPtr<T, SmartPtrType, AllocatorType> &&other) = delete;

    T& operator* ();
    T* operator-> ();

    void *getPointer() override;
    void setPointer(void *ptr) override;

private:
    AllocatorType allocator_;
    SmartPtrType checkPointer_;
    T *data_;
};

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
    allocator_.destruct(data_);
    allocator_.deallocate(data_, this);
    data_ = nullptr;
}

template<typename T, typename SmartPtrType, typename AllocatorType>
void *SmartPtr<T, SmartPtrType, AllocatorType>::getPointer() {
    return data_;
}

template<typename T, typename SmartPtrType, typename AllocatorType>
void SmartPtr<T, SmartPtrType, AllocatorType>::setPointer(void *ptr) {
    data_ = (T*)(ptr);
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
