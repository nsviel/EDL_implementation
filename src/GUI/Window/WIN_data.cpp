#include "WIN_data.h"

#include "../Node_gui.h"
#include "../GUI_param.h"

#include "../../Engine/Node_engine.h"
#include "../../Engine/Param_engine.h"
#include "../../Engine/Camera/struct_camera.h"


//Constructor / Destructor
WIN_data::WIN_data(Node_gui* node_gui, bool* show_window, string name) : WIN_base(show_window, name){
  //---------------------------

  Node_engine* node_engine = node_gui->get_node_engine();
  Param_engine* param_engine = node_engine->get_param_engine();
  this->camera = &param_engine->camera;

  //---------------------------
}
WIN_data::~WIN_data(){}

//Main function
void WIN_data::design_window(){
  //---------------------------

  this->object_parameter();

  //---------------------------
}

//Subfunction
void WIN_data::object_parameter(){
  //---------------------------


  //---------------------------
}
void WIN_data::option_line_width(){
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
