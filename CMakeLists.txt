project(ragf)

cmake_minimum_required(VERSION 3.0)

include_directories("src")

set(cxx_main_flags "-std=c++14 -O2")
set(cxx_warning_flags "-Wall -Wextra")
set(
  CMAKE_CXX_FLAGS
  "${CMAKE_CXX_FLAGS} ${cxx_main_flags} ${cxx_warning_flags}"
)
set(c_main_flags "-std=c11 -O2")
set(c_warning_flags "-Wall -Wextra")
set(
  CMAKE_C_FLAGS
  "${CMAKE_C_FLAGS} ${c_main_flags} ${c_warning_flags}"
)

# Forcing Qt Creator to display headers
file(
  GLOB_RECURSE
  header_files
  "src/*.hpp"
  "src/*.h"
)
add_custom_target(headers SOURCES ${header_files})

add_subdirectory("src/core")

add_executable(${PROJECT_NAME} local/main.cpp)
target_link_libraries(
  ${PROJECT_NAME}
  ragf_core
  /home/quasilyte/CODE/GIT/embedded_asm/build/run.o
)
