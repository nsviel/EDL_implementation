#include "WIN_object.h"

#include "../Node_gui.h"
#include "../GUI_param.h"

#include "../../Data/Node_data.h"
#include "../../Data/Scene/Control.h"

#include "image/IconsFontAwesome5.h"


//Constructor / Destructor
WIN_object::WIN_object(Node_gui* node_gui, bool* show_window, string name) : WIN_base(show_window, name){
  //---------------------------

  Node_data* node_data = node_gui->get_node_data();
  this->gui_param = node_gui->get_gui_param();
  this->controlManager = node_data->get_controlManager();

  this->item_width = 150;

  //---------------------------
}
WIN_object::~WIN_object(){}

//Main function
void WIN_object::design_window(){
  //---------------------------

  this->object_info(gui_param->object_selected);
  this->object_parameter(gui_param->object_selected);

  //---------------------------
}

//Subfunction
void WIN_object::object_info(Object* object){
  //---------------------------

  this->name = "Object " + object->name;

  //---------------------------
}
void WIN_object::object_parameter(Object* object){
  ImGui::Columns(2);
  //---------------------------

  //Visibility
  ImGui::Text("Visibility");
  ImGui::NextColumn();
  ImGui::Checkbox("##4555", &object->is_visible);
  ImGui::SameLine();
  if(ImGui::Button(ICON_FA_TRASH "##4567")){
    controlManager->object_deletion(object);
  }
  ImGui::NextColumn();

  //Name
  ImGui::SetColumnWidth(-1,75);
  ImGui::Text("Name");
  ImGui::NextColumn();
  static char str_n[256];
  strcpy(str_n, object->name.c_str());
  if(ImGui::InputText("##name", str_n, IM_ARRAYSIZE(str_n), ImGuiInputTextFlags_EnterReturnsTrue)){
    object->name = str_n;
  }
  ImGui::NextColumn();

  //Format
  ImGui::Text("Format ");
  ImGui::NextColumn();
  static char str_f[256];
  strcpy(str_f, object->file_format.c_str());
  if(ImGui::InputText("##format", str_f, IM_ARRAYSIZE(str_f), ImGuiInputTextFlags_EnterReturnsTrue)){
    object->file_format = str_f;
  }
  ImGui::NextColumn();

  //Number of points
  ImGui::Text("Nb point");
  ImGui::NextColumn();
  string nb_point = thousandSeparator(object->nb_point);
  ImGui::Text("%s", nb_point.c_str());
  ImGui::NextColumn();

  //Uniform collection color
  ImGui::Text("Uniform color");
  ImGui::NextColumn();
  ImGuiColorEditFlags flags = ImGuiColorEditFlags_NoInputs;
  flags |= ImGuiColorEditFlags_AlphaBar;
  if(ImGui::ColorEdit4("Color", (float*)&object->unicolor, flags)){
    //colorManager->set_color_new(object, object->unicolor);
  }
  ImGui::NextColumn();

  //Root pos
  vec3& root = object->root;
  ImGui::Text("Root ");
  ImGui::NextColumn();
  ImGui::Text("%.2f  %.2f  %.2f", root.x, root.y, root.z);
  ImGui::SameLine();
  if(ImGui::Button("R", ImVec2(15,0))){
    root = vec3(0,0,0);
  }
  ImGui::NextColumn();

  //Primitive size
  if(object->draw_type_name == "point"){
    this->size_point(object);
  }
  else if(object->draw_type_name == "line"){
    this->width_line(object);
  }

  //---------------------------
  ImGui::Columns(1);
  //ImGui::Separator();
}

//Primitive size
void WIN_object::width_line(Object* object){
  ImGuiStyle& style = ImGui::GetStyle();
  //---------------------------

  //Column 1
  ImGui::SetNextItemWidth(item_width);
  ImGui::AlignTextToFramePadding();
  ImGui::Text("Line width ");
  ImGui::NextColumn();

  //Column 2
  ImGui::PushButtonRepeat(true);
  if(ImGui::ArrowButton("##left", ImGuiDir_Left)){
    object->draw_line_width--;

    if(object->draw_line_width <= 1){
      object->draw_line_width = 1;
    }
  }
  ImGui::SameLine(0.0f, style.ItemInnerSpacing.x);
  if(ImGui::ArrowButton("##right", ImGuiDir_Right)){
    object->draw_line_width++;
  }
  ImGui::PopButtonRepeat();
  ImGui::SameLine();
  ImGui::Text("%d", object->draw_line_width);

  //---------------------------
}
void WIN_object::size_point(Object* object){
  ImGuiStyle& style = ImGui::GetStyle();
  //---------------------------

  //Column 1
  ImGui::SetNextItemWidth(item_width);
  ImGui::AlignTextToFramePadding();
  ImGui::Text("Point size ");
  ImGui::NextColumn();

  //Column 2
  ImGui::PushButtonRepeat(true);
  if(ImGui::ArrowButton("##left", ImGuiDir_Left)){
    object->draw_point_size--;

    if(object->draw_point_size <= 1){
      object->draw_point_size = 1;
    }
  }
  ImGui::SameLine(0.0f, style.ItemInnerSpacing.x);
  if(ImGui::ArrowButton("##right", ImGuiDir_Right)){
    object->draw_point_size++;
  }
  ImGui::PopButtonRepeat();
  ImGui::SameLine();
  ImGui::Text("%d", object->draw_point_size);

  //---------------------------
}
