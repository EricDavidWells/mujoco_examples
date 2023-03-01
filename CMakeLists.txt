cmake_minimum_required(VERSION 3.16)
project(mujoco_demo)

set(CMAKE_C_STANDARD 17)

include(GNUInstallDirs)

set(MUJOCO_BUILD_EXAMPLES OFF)
set(MUJOCO_BUILD_TESTS OFF)
set(MUJOCO_TEST_PYTHON_UTIL OFF)

# add_subdirectory(vendor/fmt)
add_subdirectory(vendor/mujoco)

find_package(glfw3 REQUIRED)
# find_package(OpenGl REQUIRED)
include(FindOpenGL)

#####################################
# main
#####################################

set(IMGUIDIR ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui)
set(IMGUISRC ${IMGUIDIR}/imgui.cpp ${IMGUIDIR}/imgui_demo.cpp ${IMGUIDIR}/imgui_draw.cpp ${IMGUIDIR}/imgui_tables.cpp ${IMGUIDIR}/imgui_widgets.cpp ${IMGUIDIR}/backends/imgui_impl_glfw.cpp ${IMGUIDIR}/backends/imgui_impl_opengl3.cpp)

add_executable(inverted_pendulum src/main.cpp)
target_include_directories(inverted_pendulum PUBLIC include/ ${IMGUIDIR} ${IMGUIDIR}/backends)
target_link_libraries(inverted_pendulum PUBLIC mujoco::mujoco glfw fmt::fmt)

install(TARGETS inverted_pendulum DESTINATION ${CMAKE_INSTALL_BINDIR})
install(DIRECTORY model DESTINATION ${CMAKE_INSTALL_DATADIR})
