#include "Engine_window.h"

#include "../Node_engine.h"

#include <stdint.h>
#include <iostream>


//Constructor / Destructor
Engine_window::Engine_window(Node_engine* node_engine){
  //---------------------------

  this->render_dim = glm::vec2(800, 600);

  //---------------------------
}
Engine_window::~Engine_window(){}


//Main function
void Engine_window::init_window(){
  //---------------------------

  glfwInit();
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

  this->window = glfwCreateWindow(render_dim.x, render_dim.y, "Vulkan", nullptr, nullptr);
  this->render_dim = get_framebuffer_size();

  //---------------------------
}
void Engine_window::clean_window(){
  //---------------------------

  glfwDestroyWindow(window);
  glfwTerminate();

  //---------------------------
}

//Subfunction
glm::vec2 Engine_window::get_framebuffer_size(){
  glm::vec2 dim = glm::vec2(0);
  //---------------------------

  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  dim.x = width;
  dim.y = height;

  //---------------------------
  return dim;
}
bool Engine_window::check_for_resizing(){
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
