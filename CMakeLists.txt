cmake_minimum_required(VERSION 3.12)
project(determinant)

set(CMAKE_CXX_STANDARD 14)

add_executable(determinant main.cpp matrix.cpp matrix.hpp handler.cpp handler.hpp argparse.hpp)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(determinant Threads::Threads)