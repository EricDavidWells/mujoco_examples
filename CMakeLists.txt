cmake_minimum_required(VERSION 3.16)
project(mujoco_demo)

set(CMAKE_C_STANDARD 17)

include(GNUInstallDirs)

find_package(glfw3 REQUIRED)
find_package(fmt REQUIRED)
find_package(imgui REQUIRED)
find_package(implot REQUIRED)
include(FindOpenGL)
set(MUJOCO_BUILD_EXAMPLES OFF)
set(MUJOCO_BUILD_TESTS OFF)
set(MUJOCO_TEST_PYTHON_UTIL OFF)

add_subdirectory(vendor/mujoco)

# find_package(OpenGl REQUIRED)

#####################################
# main
#####################################

add_executable(inverted_pendulum src/main.cpp ${IMGUISRC})
target_include_directories(inverted_pendulum PUBLIC include/ ${MUJOCO_INCLUDE})
target_link_libraries(inverted_pendulum PUBLIC mujoco::mujoco glfw fmt::fmt OpenGL::GL imgui::imgui implot::implot)

install(TARGETS inverted_pendulum DESTINATION ${CMAKE_INSTALL_BINDIR})
install(DIRECTORY model DESTINATION ${CMAKE_INSTALL_DATADIR})
