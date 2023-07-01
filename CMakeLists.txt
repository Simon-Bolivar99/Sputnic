cmake_minimum_required(VERSION 3.0.0)
project(Sputnic VERSION 0.1.0)
find_package (Boost  COMPONENTS program_options filesystem REQUIRED) 
find_package(PkgConfig REQUIRED)
pkg_check_modules(deps REQUIRED IMPORTED_TARGET glib-2.0)
include_directories (${Boost_INCLUDE_DIR} "/usr/include/glib-2.0" "/usr/lib/x86_64-linux-gnu/glib-2.0/include/")
set(SOURCE_EXE main.cpp)
set(SOURCE_LIB lib_src/sgp4sdp4.cpp lib_src/sgp_math.cpp lib_src/sgp_time.cpp 
lib_src/TerminalOptions.cpp lib_src/sgp_obs.cpp lib_src/sgp_in.cpp)


add_library(sgp4sdp4 STATIC ${SOURCE_LIB} ${Boost_INCLUDE_DIRS})
add_executable(main ${SOURCE_EXE})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
target_link_libraries(main sgp4sdp4 Boost::program_options Boost::filesystem PkgConfig::deps) 
