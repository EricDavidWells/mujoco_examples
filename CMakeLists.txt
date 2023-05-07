cmake_minimum_required(VERSION 3.16)
project(mujoco_demo)

set(CMAKE_C_STANDARD 17)

include(GNUInstallDirs)

<<<<<<< HEAD
find_package(glfw3 REQUIRED)
# find_package(OpenGl REQUIRED)
include(FindOpenGL)
=======
set(MUJOCO_BUILD_EXAMPLES OFF)
set(MUJOCO_BUILD_TESTS OFF)
set(MUJOCO_TEST_PYTHON_UTIL OFF)
>>>>>>> fe8a6901d9a0a40598be6063e30b8d1458209e6c

# add_subdirectory(vendor/fmt)
add_subdirectory(vendor/mujoco)

<<<<<<< HEAD
target_include_directories(basic PUBLIC ${MUJOCO_INCLUDE})
target_link_libraries(basic PUBLIC ${MUJOCO_LIB} glfw )
=======
find_package(glfw3 REQUIRED)
find_package(fmt REQUIRED)
# find_package(OpenGl REQUIRED)
include(FindOpenGL)
>>>>>>> fe8a6901d9a0a40598be6063e30b8d1458209e6c

#####################################
# main
#####################################

set(IMGUIDIR ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui)
set(IMGUISRC ${IMGUIDIR}/imgui.cpp ${IMGUIDIR}/imgui_demo.cpp ${IMGUIDIR}/imgui_draw.cpp ${IMGUIDIR}/imgui_tables.cpp ${IMGUIDIR}/imgui_widgets.cpp ${IMGUIDIR}/backends/imgui_impl_glfw.cpp ${IMGUIDIR}/backends/imgui_impl_opengl3.cpp)

add_executable(inverted_pendulum src/main.cpp ${IMGUISRC})
target_include_directories(inverted_pendulum PUBLIC include/ ${MUJOCO_INCLUDE} ${IMGUIDIR} ${IMGUIDIR}/backends)
<<<<<<< HEAD
target_link_libraries(inverted_pendulum PUBLIC ${MUJOCO_LIB} glfw fmt::fmt OpenGL::GL ${CMAKE_DL_LIBS})
=======
target_link_libraries(inverted_pendulum PUBLIC mujoco::mujoco glfw fmt::fmt OpenGL::GL ${CMAKE_DL_LIBS})
>>>>>>> fe8a6901d9a0a40598be6063e30b8d1458209e6c


install(TARGETS inverted_pendulum DESTINATION ${CMAKE_INSTALL_BINDIR})
install(DIRECTORY model DESTINATION ${CMAKE_INSTALL_DATADIR})
