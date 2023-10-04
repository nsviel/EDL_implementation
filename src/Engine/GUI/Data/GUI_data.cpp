#include "GUI_data.h"

#include "../Node_gui.h"

#include "../../Render/Core_node.h"
#include "../../Render/Core_param.h"
#include "../../Render/Vulkan/VK_engine.h"
#include "../../Render/Vulkan/VK_param.h"


//Constructor / Destructor
GUI_data::GUI_data(Node_gui* node_gui){
  //---------------------------

  this->node_gui = node_gui;
  this->core_node = node_gui->get_core_node();
  this->vk_engine = core_node->get_vk_engine();
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
