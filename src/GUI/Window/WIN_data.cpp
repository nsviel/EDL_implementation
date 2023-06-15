#include "WIN_data.h"

#include "../Node_gui.h"
#include "../GUI_param.h"


//Constructor / Destructor
WIN_data::WIN_data(Node_gui* node_gui, bool* show_window, string name) : WIN_base(show_window, name){
  //---------------------------

  this->gui_param = node_gui->get_gui_param();

  this->item_width = 150;

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

  option_line_width(gui_param->object_selected);

  //---------------------------
}
void WIN_data::option_line_width(Object* object){
  ImGuiStyle& style = ImGui::GetStyle();
  //---------------------------

  //Point size
  ImGui::SetNextItemWidth(item_width);
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
  ImGui::Columns(1);

  ImGui::SetNextItemWidth(item_width);
  bool truc = true;
  if(ImGui::Checkbox("Activated", &truc)){
  }

  //---------------------------
}
