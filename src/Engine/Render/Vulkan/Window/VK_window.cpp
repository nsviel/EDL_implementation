#include "VK_window.h"

#include "../Instance/VK_instance.h"

#include "../VK_engine.h"
#include "../VK_param.h"
#include "../Camera/VK_viewport.h"

#include "../../Render_node.h"
#include "../../Dimension/Dimension.h"
#include <Window/Window_manager.h>


//Constructor / Destructor
VK_window::VK_window(VK_engine* vk_engine){
  //---------------------------

  Render_node* core_node = vk_engine->get_core_node();

  this->vk_param = vk_engine->get_vk_param();
  this->dimManager = core_node->get_dimManager();
  this->vk_instance = vk_engine->get_vk_instance();
  this->vk_viewport = vk_engine->get_vk_viewport();

  this->window_dim = vk_param->window.dim;

  //---------------------------
}
VK_window::~VK_window(){}

//Main function
void VK_window::init_window(){
  //---------------------------

  glfwInit();
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

  this->window = glfwCreateWindow(window_dim.x, window_dim.y, vk_param->window.title.c_str(), nullptr, nullptr);
  this->window_dim = get_framebuffer_size();
  this->get_required_extensions();
  dimManager->set_window(window);

  glfwSetWindowSizeLimits(window, vk_param->window.dim_min.x, vk_param->window.dim_min.y, GLFW_DONT_CARE, GLFW_DONT_CARE);

  if (!glfwVulkanSupported()){
    printf("GLFW: Vulkan Not Supported\n");
    exit(0);
  }

  //---------------------------
}
void VK_window::clean_surface(){
  //---------------------------

  vkDestroySurfaceKHR(vk_param->instance.instance, surface, nullptr);

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
  //---------------------------

  VkResult result = glfwCreateWindowSurface(vk_param->instance.instance, window, nullptr, &surface);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create window surface!");
  }

  //---------------------------
}
void VK_window::check_for_resizing(){
  bool is_resized = false;
  //---------------------------

  vec2 dim = get_framebuffer_size();
  if(dim.x != window_dim.x || dim.y != window_dim.y){
    is_resized = true;
    window_dim = dim;

    //update dimension
    dimManager->update();
  }

  //---------------------------
  vk_param->window.is_resized = is_resized;
}
vec2 VK_window::get_framebuffer_size(){
  vec2 dim = vec2(0);
  //---------------------------

  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  dim.x = width;
  dim.y = height;

  //---------------------------
  return dim;
}
void VK_window::get_required_extensions(){
  //---------------------------

  uint32_t glfw_extension_nb = 0;
  const char** glfw_extensions = glfwGetRequiredInstanceExtensions(&glfw_extension_nb);
  vector<const char*> extensions(glfw_extensions, glfw_extensions + glfw_extension_nb);

  for(int i=0; i<extensions.size(); i++){
    vk_param->instance.extension.push_back(extensions[i]);
  }

  //---------------------------
}
