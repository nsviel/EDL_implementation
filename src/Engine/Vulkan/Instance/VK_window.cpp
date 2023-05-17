#include "VK_window.h"

#include "../Engine.h"
#include "../Param_vulkan.h"
#include "../Instance/VK_instance.h"
#include "../Camera/VK_viewport.h"

#include "../../Node_engine.h"
#include "../../Dimension/Dimension.h"


//Constructor / Destructor
VK_window::VK_window(Engine* engineManager){
  //---------------------------

  Node_engine* node_engine = engineManager->get_node_engine();

  this->param_vulkan = engineManager->get_param_vulkan();
  this->dimManager = node_engine->get_dimManager();
  this->vk_instance = engineManager->get_vk_instance();
  this->vk_viewport = engineManager->get_vk_viewport();

  this->window_dim = param_vulkan->window_dim;

  //---------------------------
}
VK_window::~VK_window(){}

//Main function
void VK_window::init_window(){
  //---------------------------

  glfwInit();
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

  this->window = glfwCreateWindow(window_dim.x, window_dim.y, param_vulkan->title.c_str(), nullptr, nullptr);
  this->window_dim = get_framebuffer_size();
  dimManager->set_window(window);

  glfwSetWindowSizeLimits(window, param_vulkan->window_dim_min.x, param_vulkan->window_dim_min.y, GLFW_DONT_CARE, GLFW_DONT_CARE);

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
  if(dim.x != window_dim.x || dim.y != window_dim.y){
    is_resized = true;
    window_dim = dim;

    //update dimension
    dimManager->update();
  }

  //---------------------------
  return is_resized;
}
