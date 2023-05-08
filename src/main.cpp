#include <fmt/format.h>

#include <algorithm>
#include <imgui_widget.hpp>
#include <input_parser.hpp>
#include <mujoco_widget.hpp>
#include <vector>

static void glfw_error_callback(int error, const char* description) {
  fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

int main(int argc, char** argv) {
  mujoco_examples::MujocoInputParser input(argc, argv);

  glfwSetErrorCallback(glfw_error_callback);
  if (!glfwInit())
    return 1;

  auto imgui_window = mujoco_examples::glfw_setup_imgui();
  auto mujoco_window = mujoco_examples::glfw_setup_mujoco(input.parameters);

  while (!glfwWindowShouldClose(imgui_window) &&
         !glfwWindowShouldClose(mujoco_window)) {
    mujoco_examples::imgui_loop(imgui_window);
    mujoco_examples::mujoco_loop(mujoco_window);
  }

  mujoco_examples::glfw_destroy_imgui(imgui_window);
  mujoco_examples::glfw_destroy_mujoco(mujoco_window);
  glfwTerminate();
}
