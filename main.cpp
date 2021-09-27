#include <iostream>
#include "allocator/smart_ptr.h"
#include "allocator/smart_ptr_type.h"
#include "test/mem_buffer_test.h"

template<class T>
T* getData(mem::MemBlock *block) {
    return (T*)((char*)block + sizeof (mem::MemBlock));
}

template<class T>
mem::MemBlock *getBlock(T ptr) {
    return (mem::MemBlock*)(ptr - sizeof(mem::MemBlock));
}

int main() {
    using namespace mem;
    typedef int Type;
    typedef SmartPtr<Type, SafeSmartPtr<Type>, Allocator<Type>> PtrInt;

    MemBuffer buffer(100);
    buffer.allocateBuffer();

    MemBlock *m1 =  buffer.allocMemBlock(sizeof (int));
    MemBlock *m2 = buffer.allocMemBlock(sizeof (int));

    printBlock(m1);
    printBlock(m2);

    int *i1 = getData<int>(m1);
    int *i2 = getData<int>(m2);

    *i1 = 12;
    *i2 = 23;

    std::cout << *i1 << "\t" << *i2 << "\n";

    MemBlock *cm1 = getBlock(i1);
    MemBlock *cm2 = getBlock(i2);

    printBlock(cm1);
    printBlock(cm2);

    return 0;
}
