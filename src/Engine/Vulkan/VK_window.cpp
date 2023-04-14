#include "VK_window.h"

#include "../Node_engine.h"

#include <stdint.h>
#include <iostream>


//Constructor / Destructor
VK_window::VK_window(){
  //---------------------------

  this->render_dim = glm::vec2(800, 600);

  //---------------------------
}
VK_window::~VK_window(){}


//Main function
void VK_window::init_window(){
  //---------------------------

  glfwInit();
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

  this->window = glfwCreateWindow(render_dim.x, render_dim.y, "Vulkan", nullptr, nullptr);
  this->render_dim = get_framebuffer_size();

  //---------------------------
}
void VK_window::clean_window(){
  //---------------------------

  glfwDestroyWindow(window);
  glfwTerminate();

  //---------------------------
}

//Subfunction
VkSurfaceKHR VK_window::create_window_surface(VkInstance instance){
  //---------------------------

  VkResult result = glfwCreateWindowSurface(instance, window, nullptr, &surface);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create window surface!");
  }

  //---------------------------
  return surface;
}
glm::vec2 VK_window::get_framebuffer_size(){
  glm::vec2 dim = glm::vec2(0);
  //---------------------------

  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  dim.x = width;
  dim.y = height;

  //---------------------------
  return dim;
}
bool VK_window::check_for_resizing(){
  bool is_resized = false;
  //---------------------------

  glm::vec2 dim = get_framebuffer_size();
  if(dim.x != render_dim.x || dim.y != render_dim.y){
    is_resized = true;
    render_dim = dim;
  }

  //---------------------------
  return is_resized;
}
