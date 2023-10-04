#include "GUI_data.h"

#include "../Node_gui.h"

#include "../../Core/Node_core.h"
#include "../../Core/Core_param.h"
#include "../../Core/Vulkan/VK_engine.h"
#include "../../Core/Vulkan/VK_param.h"


//Constructor / Destructor
GUI_data::GUI_data(Node_gui* node_gui){
  //---------------------------

  this->node_gui = node_gui;
  this->node_core = node_gui->get_node_core();
  this->vk_engine = node_core->get_vk_engine();
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
