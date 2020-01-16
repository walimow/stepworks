cmake_minimum_required(VERSION 2.6)
project(stepworks)

add_definitions ( -Wall   -lstdc++ )

if (MAKE_GCC7)
  add_definitions( -std=c++17)
else()
  add_definitions( -std=c++1z)
endif()

add_compile_options(-pthread)

set (CMAKE_BUILD_TYPE Debug)

include_directories(
./include 
./../../src/immer-master
)

add_executable(stepworks main.cpp)

add_subdirectory(test)
add_subdirectory(samples)

install(TARGETS stepworks RUNTIME DESTINATION bin)
