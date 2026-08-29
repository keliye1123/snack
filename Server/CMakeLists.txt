cmake_minimum_required(VERSION 4.2)
project(Snack_Server)

set(CMAKE_CXX_STANDARD 20)

add_executable(Snack_Server
        serve.cpp
        poll.cpp
)
