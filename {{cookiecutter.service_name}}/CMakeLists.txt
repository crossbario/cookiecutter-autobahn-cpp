cmake_minimum_required(VERSION 2.8)

project(service)

include(cmake/Includes/CMakeLists.txt)

set(CLIENT_SOURCES client.cpp)

add_executable(client ${CLIENT_SOURCES} ${PUBLIC_HEADERS})

target_link_libraries(client autobahn_cpp)
