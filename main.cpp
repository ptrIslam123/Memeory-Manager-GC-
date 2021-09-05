#include <iostream>
#include "allocator/mem_buffer.h"
#include "test/tests.h"

void printBlock(const mem::MemBlock* block) {
    std::cout << "{\n\tblock.size : " << block->getSizeBlock() << "\n"
    << "\tblock.status : " << block->getStatusBlock() << "\n}\n";
}


int main() {

    using namespace mem;

    allocMemBlockTest(300, 25);



    return 0;
}
