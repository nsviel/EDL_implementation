#include "VK_window.h"

#include "../Instance/VK_instance.h"
#include "../Engine_vulkan.h"

#include "../../Node_engine.h"

#include <stdint.h>
#include <iostream>


//Constructor / Destructor
VK_window::VK_window(Engine_vulkan* engine_vulkan){
  //---------------------------

  this->render_dim = glm::vec2(800, 600);
  this->vk_instance = engine_vulkan->get_vk_instance();

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

  if (!glfwVulkanSupported()){
    printf("GLFW: Vulkan Not Supported\n");
    exit(0);
  }

  //---------------------------
}
void VK_window::clean_surface(){
  //---------------------------

  VkInstance instance = vk_instance->get_instance();
  vkDestroySurfaceKHR(instance, surface, nullptr);

  //---------------------------
}
void VK_window::clean_window(){
  //---------------------------

  glfwDestroyWindow(window);
  glfwTerminate();

  //---------------------------
}

//Subfunction
void VK_window::create_window_surface(){
  VkInstance instancee = vk_instance->get_instance();
  //---------------------------

  VkResult result = glfwCreateWindowSurface(instancee, window, nullptr, &surface);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create window surface!");
  }

  //---------------------------
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
