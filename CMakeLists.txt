cmake_minimum_required(VERSION 3.0.0)
project(Sputnic VERSION 0.1.0)

set(SOURCE_EXE main.cpp)
set(SOURCE_LIB lib_src/sgp4sdp4.cpp lib_src/sgp_math.cpp lib_src/sgp_time.cpp 
lib_src/TerminalOptions.hpp)

add_library(sgp4sdp4 STATIC ${SOURCE_LIB})
add_executable(main ${SOURCE_EXE})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
target_link_libraries(main sgp4sdp4)
