cmake_minimum_required(VERSION 3.16)
project(mujoco_demo)

set(MUJOCO_INCLUDE "~/Programs/mujoco-2.3.2/include")
set(MUJOCO_LIB "~/Programs/mujoco-2.3.2/lib/libmujoco.so")

add_subdirectory(vendor/fmt)

find_package(glfw3 REQUIRED)
# find_package(OpenGl REQUIRED)
include(FindOpenGL)

#####################################
# examples
#####################################
add_executable(basic sample/basic.cc)

target_include_directories(basic PUBLIC ${MUJOCO_INCLUDE})
target_link_libraries(basic PUBLIC ${MUJOCO_LIB} glfw )

#####################################
# main
#####################################

set(IMGUIDIR ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui)
set(IMGUISRC ${IMGUIDIR}/imgui.cpp ${IMGUIDIR}/imgui_demo.cpp ${IMGUIDIR}/imgui_draw.cpp ${IMGUIDIR}/imgui_tables.cpp ${IMGUIDIR}/imgui_widgets.cpp ${IMGUIDIR}/backends/imgui_impl_glfw.cpp ${IMGUIDIR}/backends/imgui_impl_opengl3.cpp)

add_executable(inverted_pendulum src/main.cpp ${IMGUISRC})
target_include_directories(inverted_pendulum PUBLIC include/ ${MUJOCO_INCLUDE} ${IMGUIDIR} ${IMGUIDIR}/backends)
target_link_libraries(inverted_pendulum PUBLIC ${MUJOCO_LIB} glfw fmt::fmt ${OPENGL_gl_LIBRARY} ${CMAKE_DL_LIBS})


