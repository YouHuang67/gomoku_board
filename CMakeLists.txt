cmake_minimum_required(VERSION 3.0.0)
project(gomoku_board VERSION 0.1.0)

include(CTest)
enable_testing()

set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")

file(GLOB SOURCES "include/*.h" "src/*.cpp")
add_executable(gomoku_board ${SOURCES})

target_include_directories(gomoku_board
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/include
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
