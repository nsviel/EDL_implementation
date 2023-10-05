#include "GUI_data.h"

#include "../Node_gui.h"

#include "../../Render/Render_node.h"
#include "../../Render/Render_param.h"
#include "../../Render/Vulkan/VK_engine.h"
#include "../../Render/Vulkan/VK_param.h"


//Constructor / Destructor
GUI_data::GUI_data(Node_gui* node_gui){
  //---------------------------

  this->node_gui = node_gui;
  this->render_node = node_gui->get_render_node();
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
