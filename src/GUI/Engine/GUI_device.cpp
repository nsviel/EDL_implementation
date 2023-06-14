#include "GUI_device.h"

#include "../Node_gui.h"

#include "../../Engine/Node_engine.h"
#include "../../Engine/Param_engine.h"
#include "../../Engine/Vulkan/VK_engine.h"
#include "../../Engine/Vulkan/VK_param.h"


//Constructor / Destructor
GUI_device::GUI_device(Node_gui* node_gui){
  //---------------------------

  this->node_gui = node_gui;
  this->node_engine = node_gui->get_node_engine();
  this->vk_engine = node_engine->get_vk_engine();
  this->vk_param = vk_engine->get_vk_param();

  this->width = 150;

  //---------------------------
}
GUI_device::~GUI_device(){}

//Main function
void GUI_device::design_device(){
  //---------------------------

  ImGui::TextColored(ImVec4(0.4f,0.4f,0.4f,1.0f),"Profiling");

  //Device model
  ImGui::Text("Device model ");
  ImGui::SameLine();
  ImGui::TextColored(ImVec4(0.5, 1, 0.5, 1), "%s", vk_param->device.model.c_str());

  //---------------------------
}
