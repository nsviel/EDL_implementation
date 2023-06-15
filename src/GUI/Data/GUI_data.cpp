#include "GUI_data.h"

#include "../Node_gui.h"

#include "../../Engine/Node_engine.h"
#include "../../Engine/Param_engine.h"
#include "../../Engine/Vulkan/VK_engine.h"
#include "../../Engine/Vulkan/VK_param.h"


//Constructor / Destructor
GUI_data::GUI_data(Node_gui* node_gui){
  //---------------------------

  this->node_gui = node_gui;
  this->node_engine = node_gui->get_node_engine();
  this->vk_engine = node_engine->get_vk_engine();
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
void GUI_data::option_line_width(){
  Object* object = new Object();
  ImGuiStyle& style = ImGui::GetStyle();
  //---------------------------

  //Point size
  ImGui::Columns(2);
  ImGui::AlignTextToFramePadding();
  ImGui::Text("Line width ");
  ImGui::NextColumn();
  ImGui::PushButtonRepeat(true);
  static int line_width = 1;
  if(object != nullptr){
    line_width = object->draw_line_width;
  }
  if (ImGui::ArrowButton("##left", ImGuiDir_Left) && object != nullptr){
    object->draw_line_width--;

    if(object->draw_line_width <= 1){
      object->draw_line_width = 1;
    }
  }
  ImGui::SameLine(0.0f, style.ItemInnerSpacing.x);
  if (ImGui::ArrowButton("##right", ImGuiDir_Right) && object != nullptr){
    object->draw_line_width++;

    line_width = object->draw_line_width;
  }
  ImGui::PopButtonRepeat();
  ImGui::SameLine();
  ImGui::Text("%d", line_width);
  ImGui::NextColumn();

  //---------------------------
}
