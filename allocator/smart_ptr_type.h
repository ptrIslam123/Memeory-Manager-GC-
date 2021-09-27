#ifndef ALLOCATOR_SMART_PTR_TYPE_H
#define ALLOCATOR_SMART_PTR_TYPE_H

#include <assert.h>

namespace mem {

template<typename T>
struct SafeSmartPtr {
    static void checkPoint(T *ptr) {
        assert(ptr != nullptr);
    }
};

template<typename T>
struct NoSafeSmartPtr {
    static void checkPoint() {}
};

}

#endif //ALLOCATOR_SMART_PTR_TYPE_H
