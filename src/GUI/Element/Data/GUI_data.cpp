#include "GUI_data.h"

#include "../../GUI_node.h"

#include <Render/Render_node.h>
#include <Render/Render_param.h>
#include <Render/Vulkan/VK_engine.h>
#include <Render/Vulkan/VK_param.h>


//Constructor / Destructor
GUI_data::GUI_data(GUI_node* gui_node){
  //---------------------------

  this->gui_node = gui_node;
  this->render_node = gui_node->get_node_render();
  this->vk_engine = render_node->get_vk_engine();
  this->vk_param = vk_engine->get_vk_param();

  this->width = 150;

  //---------------------------
}
GUI_data::~GUI_data(){}

//Main function
void GUI_data::design_data(){
  //---------------------------



  //---------------------------
}

//Subfunctions
