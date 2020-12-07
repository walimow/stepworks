cmake_minimum_required(VERSION 3.0)
project(stepworks)

add_definitions ( -Wall   -lstdc++ )

add_definitions( -std=c++2a)


add_compile_options(-pthread)

set (CMAKE_BUILD_TYPE Debug)

include_directories(
./include 
# ./../../src/immer-master
)

set( ST_INCLUDES  include/util/iox.hpp include/box/boxm.hpp
        include/util/ignore.hpp include/util/tostrx.hpp include/eal/val.hpp include/box/constr.hpp include/box/mkbox.hpp
         include/box/apply.hpp
        include/detect/detect_allocator.hpp include/detect/detect_tostring.hpp)

add_executable(stepworks main.cpp ${ST_INCLUDES})

add_subdirectory(test)
add_subdirectory(samples)

install(TARGETS stepworks RUNTIME DESTINATION bin)
