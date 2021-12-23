cmake_minimum_required(VERSION 3.0.0)
project(raymarch VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(raymarch
    ${CMAKE_SOURCE_DIR}/src/main.cpp
    ${CMAKE_SOURCE_DIR}/src/Parser.cpp
    ${CMAKE_SOURCE_DIR}/src/Camera.cpp
    ${CMAKE_SOURCE_DIR}/src/World.cpp
)

target_include_directories(raymarch PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
