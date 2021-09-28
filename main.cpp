#include <iostream>
#include "allocator/smart_ptr.h"
#include "allocator/smart_ptr_type.h"
#include "test/mem_buffer_test.h"




int main() {
    using namespace mem;
    typedef int Type;
    typedef SmartPtr<Type, SafeSmartPtr<Type>, Allocator<Type>> PtrInt;



    return 0;
}
