cmake_minimum_required(VERSION 3.29)

project(String_Task)

set(CMAKE_CXX_STANDARD 20)


add_subdirectory(third_party/googletest)

add_executable(String_Task
        main.cpp
        String.h
        String.cpp)

add_executable(tests
        String.cpp
        tests/test.cpp
        String.h
)

target_link_libraries(tests gtest)
