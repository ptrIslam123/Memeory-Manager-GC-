#ifndef ALLOCATOR_POINTER_H
#define ALLOCATOR_POINTER_H

namespace mem {

    class Pointer {
        virtual void *getPointer() = 0;
        virtual void setPointer(void *ptr) = 0;
    };
}

#endif //ALLOCATOR_POINTER_H
