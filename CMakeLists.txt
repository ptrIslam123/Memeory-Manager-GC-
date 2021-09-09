cmake_minimum_required(VERSION 3.20)
project(allocator)

set(CMAKE_CXX_STANDARD 17)

add_executable(allocator
        main.cpp

        allocator/mem_buffer.cpp

        test/mem_buffer_test.cpp)
