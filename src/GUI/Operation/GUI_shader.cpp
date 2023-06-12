#include "GUI_shader.h"

#include "../Node_gui.h"

#include "../../Engine/Node_engine.h"
#include "../../Engine/Dimension/Dimension.h"


//Constructor / Destructor
GUI_shader::GUI_shader(Node_gui* node_gui){
  //---------------------------

  Node_engine* node_engine = node_gui->get_node_engine();
  this->dimManager = node_engine->get_dimManager();

  this->item_width = 150;

  //---------------------------
}
GUI_shader::~GUI_shader(){}

//Main function
void GUI_shader::design_shader(){
  ImGui::TextColored(ImVec4(0.4f,0.4f,0.4f,1.0f),"EDL");
  //---------------------------
/*
  ImGui::SetNextItemWidth(item_width);
  bool* with_edl = shader_edl->get_with_edl();
  if(ImGui::Checkbox("Activated", with_edl)){
    shader_edl->update_shader();
  }

  ImGui::SetNextItemWidth(item_width);
  float* edl_radius = shader_edl->get_edl_radius();
  if(ImGui::SliderFloat("Radius", edl_radius, 1.0f, 3.0f)){
    shader_edl->update_shader();
  }

  ImGui::SetNextItemWidth(item_width);
  float* edl_strength = shader_edl->get_edl_strength();
  if(ImGui::SliderFloat("Strength", edl_strength, 1.0f, 1000.0f)){
    shader_edl->update_shader();
  }
*/
  //---------------------------
}
