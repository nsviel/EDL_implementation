#include "GUI_object.h"
#include <Panel/Panel.h>

#include <GUI.h>
#include <Data/Data_node.h>
#include <Data/Scene/Scene.h>
#include <image/IconsFontAwesome5.h>


//Constructor / Destructor
GUI_object::GUI_object(GUI* gui, bool* show_window, string name) : BASE_panel(show_window, name){
  //---------------------------

  Data_node* data_node = gui->get_data_node();
  this->panel = gui->get_panel();
  this->sceneManager = data_node->get_sceneManager();

  this->item_width = 150;

  //---------------------------
}
GUI_object::~GUI_object(){}

//Main function
void GUI_object::design_window(){
  //---------------------------

  this->object_info(object_selected);
  this->object_parameter(object_selected);

  //---------------------------
}

//Subfunction
void GUI_object::object_info(Object* object){
  //---------------------------

  this->name = "Object " + object->name;

  //---------------------------
}
void GUI_object::object_parameter(Object* object){
  ImGui::Columns(2);
  //---------------------------

  //Visibility
  ImGui::Text("Visibility");
  ImGui::NextColumn();
  ImGui::Checkbox("##4555", &object->is_visible);
  if(object->is_suppressible){
    ImGui::SameLine();
    if(ImGui::Button(ICON_FA_TRASH "##4567")){
      sceneManager->delete_scene_object(object);
      panel->show_object = false;
    }
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
    //Number of points
    ImGui::Text("Nb point");
    ImGui::NextColumn();
    string nb_point = thousandSeparator(object->nb_point);
    ImGui::Text("%s", nb_point.c_str());
    ImGui::NextColumn();

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
void GUI_object::width_line(Object* object){
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
void GUI_object::size_point(Object* object){
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
