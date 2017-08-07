cmake_minimum_required(VERSION 2.8)

#add_executable(open1 open1.c)
project(lib)

add_library(lib STATIC d_list.cpp)

#add_definitions(-g)

#link_directories(/home/gelya/usr/local/lib)

include_directories(.)

#target_link_libraries(log PocoFoundation)
