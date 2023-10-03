#include "VK_window.h"

#include "../Instance/VK_instance.h"

#include "../VK_engine.h"
#include "../VK_param.h"
#include "../Camera/VK_viewport.h"

#include "../../Node_engine.h"
#include "../../Dimension/Dimension.h"
#include <Window/Window_manager.h>


//Constructor / Destructor
VK_window::VK_window(VK_engine* vk_engine){
  //---------------------------

  Node_engine* node_engine = vk_engine->get_node_engine();

  this->vk_param = vk_engine->get_vk_param();
  this->dimManager = node_engine->get_dimManager();
  this->vk_instance = vk_engine->get_vk_instance();
  this->vk_viewport = vk_engine->get_vk_viewport();

  this->window_dim = vk_param->window.dim;

  //---------------------------
}
VK_window::~VK_window(){}

//Main function
void VK_window::init_window(Window_manager* window_manager){
  //---------------------------

  this->window_manager = window_manager;
  this->window = window_manager->get_window();
  this->window_dim = get_framebuffer_size();
  this->get_required_extensions();
  dimManager->set_window(window_manager->get_window());
  window_manager->set_window_size_minimum(vk_param->window.dim_min.x, vk_param->window.dim_min.y);

  //---------------------------
}
void VK_window::clean_surface(){
  //---------------------------

  vkDestroySurfaceKHR(vk_param->instance.instance, surface, nullptr);

  //---------------------------
}
void VK_window::clean_window(){
  //---------------------------

  window_manager->destroy_window();

  //---------------------------
}

//Subfunction
void VK_window::create_window_surface(){
  //---------------------------

  window_manager->create_window_surface(vk_param->instance.instance, surface);

  //---------------------------
}
void VK_window::check_for_resizing(){
  //---------------------------

  vk_param->window.is_resized = window_manager->check_for_resizing();

  //---------------------------
}
vec2 VK_window::get_framebuffer_size(){
  //---------------------------

  return window_manager->get_framebuffer_size();

  //---------------------------
}
void VK_window::get_required_extensions(){
  //---------------------------

  vector<const char*> extensions = window_manager->get_required_extensions();
  for(int i=0; i<extensions.size(); i++){
    vk_param->instance.extension.push_back(extensions[i]);
  }

  //---------------------------
}
