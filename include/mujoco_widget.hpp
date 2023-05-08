#pragma once

#include <GLFW/glfw3.h>
#include <mujoco/mujoco.h>
#include <input_parser.hpp>

namespace mujoco_examples
{

// MuJoCo data structures
mjModel* m = NULL;                  // MuJoCo model
mjData* d = NULL;                   // MuJoCo data
mjvCamera cam;                      // abstract camera
mjvOption opt;                      // visualization options
mjvScene scn;                       // abstract scene
mjrContext con;                     // custom GPU context

// mouse interaction
bool button_left = false;
bool button_middle = false;
bool button_right =  false;
double lastx = 0;
double lasty = 0;

// keyboard callback
void keyboard(GLFWwindow* window, int key, int scancode, int act, int mods) {
  // backspace: reset simulation
  if (act==GLFW_PRESS && key==GLFW_KEY_BACKSPACE) {
    mj_resetData(m, d);
    mj_forward(m, d);
  }
}

// mouse button callback
void mouse_button(GLFWwindow* window, int button, int act, int mods) {
  // update button state
  button_left = (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT)==GLFW_PRESS);
  button_middle = (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE)==GLFW_PRESS);
  button_right = (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT)==GLFW_PRESS);

  // update mouse position
  glfwGetCursorPos(window, &lastx, &lasty);
}

// mouse move callback
void mouse_move(GLFWwindow* window, double xpos, double ypos) {
  // no buttons down: nothing to do
  if (!button_left && !button_middle && !button_right) {
    return;
  }

  // compute mouse displacement, save
  double dx = xpos - lastx;
  double dy = ypos - lasty;
  lastx = xpos;
  lasty = ypos;

  // get current window size
  int width, height;
  glfwGetWindowSize(window, &width, &height);

  // get shift key state
  bool mod_shift = (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT)==GLFW_PRESS ||
                    glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT)==GLFW_PRESS);

  // determine action based on mouse button
  mjtMouse action;
  if (button_right) {
    action = mod_shift ? mjMOUSE_MOVE_H : mjMOUSE_MOVE_V;
  } else if (button_left) {
    action = mod_shift ? mjMOUSE_ROTATE_H : mjMOUSE_ROTATE_V;
  } else {
    action = mjMOUSE_ZOOM;
  }

  // move camera
  mjv_moveCamera(m, action, dx/height, dy/height, &scn, &cam);
}

// scroll callback
void scroll(GLFWwindow* window, double xoffset, double yoffset) {
  // emulate vertical mouse motion = 5% of window height
  mjv_moveCamera(m, mjMOUSE_ZOOM, 0, 0.05*yoffset, &scn, &cam);
}

GLFWwindow* glfw_setup_mujoco(const mujoco_examples::MujocoInputParser::Parameters& parameters)
{
 // load model
  char error[1000];
  m = mj_loadXML(parameters.model.c_str(), 0, error, 1000);
  if (!m) { mju_error_s("Load model error: %s", error); }
  d = mj_makeData(m);

  // create window, make OpenGL context current, request v-sync
  auto window = glfwCreateWindow(1200, 900, "Mujoco Window", NULL, NULL);
  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);

  // initialize visualization data structures
  mjv_defaultCamera(&cam);
  mjv_defaultOption(&opt);
  mjv_defaultScene(&scn);
  mjr_defaultContext(&con);

  // create scene and context
  mjv_makeScene(m, &scn, 2000);
  mjr_makeContext(m, &con, mjFONTSCALE_150);
  
  opt.frame = mjtFrame::mjFRAME_BODY;
  opt.label = mjtLabel::mjLABEL_BODY;

  // install GLFW mouse and keyboard callbacks
  glfwSetKeyCallback(window, keyboard);
  glfwSetCursorPosCallback(window, mouse_move);
  glfwSetMouseButtonCallback(window, mouse_button);
  glfwSetScrollCallback(window, scroll);

  return window;
}

void mujoco_loop(GLFWwindow* mujoco_window)
{
  glfwMakeContextCurrent(mujoco_window);
    mjtNum simstart = d->time;
    while (d->time - simstart < 1.0/60.0) {
        mj_step(m, d);
    }

  // get sensor information
  auto cart_joint_id = mj_name2id(m, mjtObj::mjOBJ_SENSOR, "cart_slide_sensor");
  auto pendulum_joint_id = mj_name2id(m, mjtObj::mjOBJ_SENSOR, "pendulum_rotation_sensor");

  auto sensor_data = d->sensordata;
  fmt::print("cart position: {}, pendulum position: {}\n", sensor_data[cart_joint_id], sensor_data[pendulum_joint_id]);

  // set control information
  d->ctrl[0] = 400*sensor_data[pendulum_joint_id] + (20)*sensor_data[cart_joint_id];
  glClear(GL_COLOR_BUFFER_BIT);

  // render
  mjrRect viewport = {0, 0, 0, 0};
  glfwGetFramebufferSize(mujoco_window, &viewport.width, &viewport.height);
  mjv_updateScene(m, d, &opt, NULL, &cam, mjCAT_ALL, &scn);
  mjr_render(viewport, &scn, &con);

  // swap OpenGL buffers (blocking call due to v-sync)
  glfwSwapBuffers(mujoco_window);

  // process pending GUI events, call GLFW callbacks
  glfwPollEvents();
}

void glfw_destroy_mujoco(GLFWwindow* imgui_window)
{
  // Cleanup
  //free visualization storage
  mjv_freeScene(&scn);
  mjr_freeContext(&con);

  // free MuJoCo model and data
  mj_deleteData(d);
  mj_deleteModel(m);
}

}

