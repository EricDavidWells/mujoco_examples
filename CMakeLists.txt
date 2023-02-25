cmake_minimum_required(VERSION 3.16)
project(mujoco_demo)

set(MUJOCO_INCLUDE "~/Programs/mujoco-2.3.2/include")
set(MUJOCO_LIB "~/Programs/mujoco-2.3.2/lib/libmujoco.so")

add_subdirectory(vendor/fmt)

find_package(glfw3 REQUIRED)

#####################################
# examples
#####################################
add_executable(basic sample/basic.cc)

target_include_directories(basic PUBLIC ${MUJOCO_INCLUDE})
target_link_libraries(basic PUBLIC ${MUJOCO_LIB} glfw)

#####################################
# main
#####################################

add_Executable(inverted_pendulum src/main.cpp)
target_include_directories(inverted_pendulum PUBLIC include/ ${MUJOCO_INCLUDE})
target_link_libraries(inverted_pendulum PUBLIC ${MUJOCO_LIB} glfw fmt::fmt)


