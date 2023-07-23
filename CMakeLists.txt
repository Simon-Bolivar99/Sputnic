cmake_minimum_required(VERSION 3.0.0)
project(Sputnic VERSION 0.1.0)
find_package (Boost  COMPONENTS program_options filesystem REQUIRED)

file(GLOB CPPS "lib_src/*.cpp")
set(SOURCE_EXE main.cpp)

add_library(sgp4sdp4 STATIC ${CPPS} ${Boost_INCLUDE_DIRS})
add_executable(main ${SOURCE_EXE})

target_link_libraries(main sgp4sdp4 Boost::program_options Boost::filesystem) 
