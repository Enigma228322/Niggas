cmake_minimum_required(VERSION 3.27)
project(Turboflex)

set(CMAKE_CXX_STANDARD 17)
include_directories(include)
set(SOURCES example/niggas_is_working.cc src/niggapool.cc)
add_executable(niggas ${SOURCES})
