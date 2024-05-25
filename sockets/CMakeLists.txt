cmake_minimum_required(VERSION 3.25)
project(sockets C)

set(CMAKE_C_STANDARD 11)

add_executable(sockets main.c)
link_libraries(ws2_32 wsock32)
target_link_libraries(sockets ws2_32)