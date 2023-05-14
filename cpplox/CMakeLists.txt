cmake_minimum_required(VERSION 3.12.0)
project(cpplox VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 20)

include(CTest)
enable_testing()

add_executable(cpplox main.cc lox.cc token.cc value.cc callable.cc vm/debug.cc vm/value.cc vm/object_manager.cc vm/object.cc vm/clock.cc)
add_executable(value_test value_test.cc value.cc)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
