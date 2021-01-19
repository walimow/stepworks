cmake_minimum_required(VERSION 2.6)
project(stepworks)

add_definitions ( -Wall   -lstdc++ )

if (MAKE_GCC7)
  add_definitions( -std=c++2a)
else()
  add_definitions( -std=c++2a)
endif()

add_compile_options(-pthread)

set (CMAKE_BUILD_TYPE Debug)

include_directories(
./include 
# ./../../src/immer-master
)

set( ST_INCLUDES  include/util/iox.hpp include/box/boxm.hpp
        include/util/ignore.hpp include/util/tostrx.hpp include/eal/val.hpp include/box/constr.hpp include/box/mkbox.hpp
        include/box/apply.hpp
        include/detect/detect_allocator.hpp
        include/detect/detect_tostring.hpp
        include/util/log.hpp include/detect/detect_tuple.hpp
        include/detect/detect_fo.hpp include/rw/wf.hpp
        include/detect/detect_totext.hpp
        include/util/symbolizer.hpp
        include/detect/detect_push_back.hpp
        include/detect/detect_insert.hpp
        include/cmorph/imorph/apply.hpp
        include/cmorph/imorph/process.hpp include/cmorph/amorph/h/apply.hpp include/cmorph/amorph/select.hpp include/util/call.hpp include/cmorph/amorph/hv/apply.hpp include/cmorph/amorph/hv/select.hpp include/cmorph/amorph/hv/process.hpp include/detect/detect_fa2box.hpp include/cmorph/imorph/boxtrans.hpp)

add_executable(stepworks main.cpp ${ST_INCLUDES})

add_subdirectory(test)
add_subdirectory(samples)

install(TARGETS stepworks RUNTIME DESTINATION bin)
