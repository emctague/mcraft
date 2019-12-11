cmake_minimum_required(VERSION 3.15)
project(MCraft)

set(CMAKE_CXX_STANDARD 20)

if(EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()
else()
    message(WARNING "The file conanbuildinfo.cmake doesn't exist, you have to run conan install first")
endif()

add_executable(MCraft main.cpp Window.cpp Window.h)
target_link_libraries(MCraft ${CONAN_LIBS})
