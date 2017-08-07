cmake_minimum_required(VERSION 2.8)

set(EX buddy)

set(SOURCE main.cpp buddy_alloc.cpp)

add_executable(${EX} ${SOURCE})

set(CMAKE_CXX_FLAGS "-std=c++11 -g")

#add_definitions(-g)

#link_directories(/home/gelya/usr/local/lib)

include_directories(. lib /usr/include/python3.5)

add_subdirectory(lib)

find_package(PythonLibs REQUIRED)

target_link_libraries(${EX} ${PYTHON_LIBRARIES})
target_link_libraries(${EX} lib)
