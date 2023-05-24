cmake_minimum_required(VERSION 3.0.0)
project(Sputnic VERSION 0.1.0)

include(CTest)
enable_testing()

set(SOURCE_EXE Sputnic.cpp)
set(SOURCE_LIB sgpsdp.h)

add_library(sgpsdp STATIC ${SOURCE_LIB})
add_executable(Sputnic ${SOURCE_EXE})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
target_link_libraries(Sputnic sgpsdp)
include(CPack)