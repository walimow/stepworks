cmake_minimum_required(VERSION 2.6)

project(test)
 
# Setup testing

enable_testing()

find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIR} )




# Add test cpp file
#[[
add_executable(runUnitTests
processing_test.cpp
)
]]


add_executable(runUnitTests

##[[
foab_test.cpp
xT_test.cpp         
process_item_test.cpp

foab_fab_test.cpp

processing_test.cpp
rtype_test.cpp
#wtype_test.cpp

filter_test.cpp

rgenerator_test.cpp

match_wte_test.cpp
match_wtex_test.cpp

application_test.cpp

rwprimitiv_test.cpp
process_stream_test.cpp

var_test.cpp                                  

step_test.cpp

eval_test.cpp
curf_test.cpp
tupleop_test.cpp
argtypetest.cpp
fo_test.cpp
lazy_test.cpp
rwmorph_test.cpp

steph_test.cpp
fmap_test.cpp
reposition_test.cpp

itx_test.cpp
stx_test.cpp
box_test.cpp
##]]#
boxm_test.cpp

hmap_test.cpp
iox_test.cpp

        strutil_test.cpp)

set(CMAKE_POSITION_INDEPENDENT_CODE ON) 

# Link test executable against gtest & gtest_main

target_link_libraries(runUnitTests ${GTEST_LIBRARY_DEBUG} ${GTEST_MAIN_LIBRARY_DEBUG} pthread ) #pthread i had to add (? -k.h.)


##target_link_libraries(runUnitTests gtest  pthread )

add_test(

    NAME runUnitTests

    COMMAND runUnitTests

)

 
