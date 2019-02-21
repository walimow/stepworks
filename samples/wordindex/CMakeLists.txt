cmake_minimum_required(VERSION 2.6)
project(wordindex)

add_definitions ( -Wall   -lstdc++ )

if (MAKE_GCC7)
  add_definitions( -std=c++17)
else()
  add_definitions( -std=c++1z)
endif()

#system-generic error
add_definitions(-DBOOST_ERROR_CODE_HEADER_ONLY)

set (CMAKE_BUILD_TYPE Debug)

include_directories(
./include 
)

add_executable(wordindex wordindex.cpp)

FIND_PACKAGE(Boost COMPONENTS system filesystem program_options REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(wordindex ${Boost_LIBRARIES})

install(TARGETS wordindex RUNTIME DESTINATION bin)
