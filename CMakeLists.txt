cmake_minimum_required(VERSION 3.16)
project(mujoco_demo)

set(CMAKE_C_STANDARD 17)

include(GNUInstallDirs)

set(MUJOCO_BUILD_EXAMPLES OFF)
set(MUJOCO_BUILD_TESTS OFF)
set(MUJOCO_TEST_PYTHON_UTIL OFF)

add_subdirectory(vendor/fmt)
add_subdirectory(vendor/mujoco)

find_package(glfw3 REQUIRED)

#####################################
# main
#####################################

add_executable(inverted_pendulum src/main.cpp)
target_include_directories(inverted_pendulum PUBLIC include/)
target_link_libraries(inverted_pendulum PUBLIC mujoco::mujoco glfw fmt::fmt)

install(TARGETS inverted_pendulum DESTINATION ${CMAKE_INSTALL_BINDIR})
install(DIRECTORY model DESTINATION ${CMAKE_INSTALL_DATADIR})

message(WARNING "config location: " ${CONFIG_PACKAGE_LOCATION})
