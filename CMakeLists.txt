cmake_minimum_required(VERSION 3.10)

AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR}/src MAIN_SRC)

project(multithread_example CXX)

set(CMAKE_CXX_STANDARD 14)

add_executable(${PROJECT_NAME} src/main.cpp ${MAIN_SRC})

find_package(Threads REQUIRED)
target_link_libraries(multithread_example Threads::Threads)
