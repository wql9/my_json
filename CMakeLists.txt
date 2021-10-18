cmake_minimum_required(VERSION 3.10)
project(lept_json)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_library(${PROJECT_NAME} SHARED
    lept_context.cpp
    lept_parse.cpp
    lept_value.cpp
    lept_stringify.cpp)
add_executable(leptjson_test test.cpp)
target_link_libraries(leptjson_test lept_json)