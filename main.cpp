#include <iostream>
#include "allocator/smart_ptr.h"
#include "allocator/smart_ptr_type.h"
#include "test/mem_buffer_test.h"

mem::MemBlock *print(mem::MemBlock *memBlock, size_t ) {
    printBlock(memBlock);
    return nullptr;
}

struct Foo {
    Foo(int i): i_(i) {
        std::cout << "Foo()" << std::endl;
    }

    ~Foo() {
        std::cout << "~Foo()" << std::endl;
    }

    int i_;
};


int main() {
    using namespace mem;
    typedef Foo Type;
    typedef SmartPtr<Type, SafeSmartPtr<Type>, Allocator<Type>> SmartP;

    SmartP i(Foo(10));


    return 0;
}
