cmake_minimum_required(VERSION 3.14)
project(NNIE_tutorial)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_COMPILER /home/liuky/HDD_1/soft/aarch-linux-gnu/bin/aarch64-linux-gnu-g++)
set(CMAKE_C_COMPILER /home/liuky/HDD_1/soft/aarch-linux-gnu/bin/aarch64-linux-gnu-gcc)

include_directories(3rd_party/hisi/include)
include_directories(include)

file(GLOB SRCS
        src/utils_service.cpp
        src/algorithm_service.cpp
        src/array_queue.cpp
#        src/chapter2_main.cpp
        src/chapter3_main.cpp
        src/video_service.cpp
        )

add_executable(NNIE_tutorial ${SRCS})

target_link_libraries(NNIE_tutorial pthread m dl)