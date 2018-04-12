cmake_minimum_required(VERSION 2.8)

project(service)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Includes/CMakeLists.txt)

set(CMAKE_EXE_LINKER_FLAGS " -static")

set(CLIENT_SOURCES client.cpp)

add_executable(client ${CLIENT_SOURCES} ${PUBLIC_HEADERS})

#target_link_libraries(client -static-libgcc -static-libstdc++)
target_link_libraries(client autobahn_cpp)
