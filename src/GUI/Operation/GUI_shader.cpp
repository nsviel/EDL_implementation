#include "GUI_shader.h"

#include "../Node_gui.h"

#include "../../Engine/Node_engine.h"
#include "../../Engine/Dimension/Dimension.h"
#include "../../Engine/Shader/Source/EDL/Shader_edl.h"


//Constructor / Destructor
GUI_shader::GUI_shader(Node_gui* node_gui){
  //---------------------------

  Node_engine* node_engine = node_gui->get_node_engine();
  this->dimManager = node_engine->get_dimManager();
  this->shader_edl = node_engine->get_shader_edl();

  this->item_width = 100;

  //---------------------------
}
GUI_shader::~GUI_shader(){}

//Main function
void GUI_shader::design_shader(){
  Struct_edl* edl_param = shader_edl->get_edl_param();
  //---------------------------

  ImGui::TextColored(ImVec4(0.4f,0.4f,0.4f,1.0f),"EDL");

  ImGui::SetNextItemWidth(item_width);
  if(ImGui::Checkbox("Activated", &edl_param->activated)){
    shader_edl->update_shader();
  }

  ImGui::SetNextItemWidth(item_width);
  if(ImGui::SliderFloat("Radius", &edl_param->radius, 1.0f, 3.0f)){
    shader_edl->update_shader();
  }

  ImGui::SetNextItemWidth(item_width);
  if(ImGui::SliderFloat("Strength", &edl_param->strength, 1.0f, 1000.0f)){
    shader_edl->update_shader();
  }

  //---------------------------
}
