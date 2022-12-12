project(MUDOnYourFace)
cmake_minimum_required(VERSION 3.23)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(MOYFNetworking)

add_subdirectory(MOYFClient)
add_subdirectory(MOYFServer)