#include "VK_surface.h"
#include "../VK_engine.h"
#include "../VK_param.h"
#include "../../Render_node.h"
#include "../../../../Element/Window/Dimension.h"

#include <Window/Window.h>


//Constructor / Destructor
VK_surface::VK_surface(VK_engine* vk_engine){
  //---------------------------

  Render_node* render_node = vk_engine->get_render_node();

  this->vk_param = vk_engine->get_vk_param();
  this->window = vk_engine->get_window();

  //---------------------------
}
VK_surface::~VK_surface(){}

//Main function
void VK_surface::init_window(){
  //---------------------------

  this->get_required_extensions();

  //---------------------------
}
void VK_surface::clean_surface(){
  //---------------------------

  vkDestroySurfaceKHR(vk_param->instance.instance, surface, nullptr);

  //---------------------------
}

//Subfunction
void VK_surface::create_window_surface(){
  //---------------------------

  window->create_window_surface(vk_param->instance.instance, surface);

  //---------------------------
}
void VK_surface::check_for_resizing(){
  bool is_resized = false;
  //---------------------------

  //ICI PROBLEM QUAND TRANSLATION TO WINDOW CLASS !!!
  vec2 dim = window->compute_window_dim();
  if(dim.x != window_dim.x || dim.y != window_dim.y){
    is_resized = true;
    window_dim = dim;

    //update dimension
    //dimManager->update();
  }

  //---------------------------
  vk_param->window.is_resized = is_resized;
}
void VK_surface::get_required_extensions(){
  //---------------------------

  vector<const char*> extensions = window->get_required_extensions();

  for(int i=0; i<extensions.size(); i++){
    vk_param->instance.extension.push_back(extensions[i]);
  }

  //---------------------------
}