#include <iostream>
#include "allocator/smart_ptr.h"
#include "allocator/smart_ptr_type.h"


struct Foo {
    Foo(int x, int y):
        x_(x), y_(y) {
        std::cout << "Foo(int x, int y)\n";
    }
    Foo(const Foo& other) {
        std::cout << "Foo(const Foo& other)\n";
        x_ = other.x_;
        y_ = other.y_;
    }
    ~Foo() {
        std::cout << "~Foo()\n";
    }



    int x_, y_;
};

Foo operator+ (const Foo &lFoo, const Foo &rFoo) {
    return Foo((lFoo.x_ + rFoo.x_), (lFoo.y_ + rFoo.y_));
}

int main() {
    using namespace mem;

    SmartPtr<Foo, SafeSmartPtr<Foo>> f1(Foo(10, 23));
    SmartPtr<Foo, SafeSmartPtr<Foo>> f2(Foo(100, 230));

    *f1 = *f1 + *f2;
    std::cout << "-----------\n";
    std::cout << f1->x_ << "\n";
    std::cout << f1->y_ << "\n";
    std::cout << "-----------\n";

    return 0;
}
