cmake_minimum_required(VERSION 4.2)
project(snack)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

include_directories(./easyX/include)
link_directories(./easyX/lib64)

add_executable(snack main.cpp
        basic.cpp
        World.cpp
        Client/Socket_Client.cpp
        Thread/poll.cpp
        InputMethod/InputMethod.cpp
)

target_link_libraries(snack
        ${CMAKE_SOURCE_DIR}/easyX/lib64/EasyXa.lib
        ws2_32
        )
