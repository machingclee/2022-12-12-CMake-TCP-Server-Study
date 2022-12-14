cmake_minimum_required(VERSION 3.22.2)
project(MOYFNetworking)

set(CMAKE_CXX_STANDARD 20)

set(BOOST_ROOT "C:\\Users\\user\\Repos\\C++Libraries\\boost_1_80_0")
find_package(Boost 1.80.0 REQUIRED)
file(GLOB_RECURSE SOURCES src/*.cpp)
add_library(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME}
        PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        ${Boost_INCLUDE_DIRS}
        PRIVATE

        )

target_link_libraries(${PROJECT_NAME}
        PRIVATE
        ${Boost_LIBRARIES}
        )