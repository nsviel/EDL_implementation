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

  this->object_info(gui_param->object_selected);
  this->object_parameter(gui_param->object_selected);


  //---------------------------
}

//Subfunction
void WIN_data::object_info(Object* object){
  //---------------------------

  this->name = object->name;

  //---------------------------
}
void WIN_data::object_parameter(Object* object){
  float truc = 0;
  ImGui::SliderFloat("FOV (°)", &truc, 100.0f, 1.0f);
  ImGui::Columns(2);
  //---------------------------

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

  //Number of points
  ImGui::Text("Nb point");
  ImGui::NextColumn();
  string nb_point = thousandSeparator(object->nb_point);
  ImGui::Text("%s", nb_point.c_str());
  ImGui::NextColumn();

  //Visibility
  ImGui::Text("Visibility");
  ImGui::NextColumn();
  ImGui::Checkbox("##4555", &object->is_visible);
  ImGui::NextColumn();

  //Uniform collection color
  ImGui::Text("Uniform color");
  ImGui::NextColumn();
  ImGuiColorEditFlags flags = ImGuiColorEditFlags_NoInputs;
  flags |= ImGuiColorEditFlags_AlphaBar;
  if(ImGui::ColorEdit4("Color", (float*)&object->unicolor, flags)){
    //colorManager->set_color_new(collection, object->unicolor);
  }
  ImGui::NextColumn();

/*



  ImGui::Separator();*/

  /*


  //Format
  ImGui::Text("Format ");
  ImGui::NextColumn();
  static char str_f[256];
  strcpy(str_f, collection->file_format.c_str());
  if(ImGui::InputText("##format", str_f, IM_ARRAYSIZE(str_f), ImGuiInputTextFlags_EnterReturnsTrue)){
    collection->file_format = str_f;
  }
  ImGui::NextColumn();

  //Number of cloud
  ImGui::Text("Nb cloud ");
  ImGui::NextColumn();
  string nb_obj = to_string(collection->nb_obj);
  ImGui::Text("%s", nb_obj.c_str());
  ImGui::NextColumn();

  //Number of points
  ImGui::Text("Nb point ");
  ImGui::NextColumn();
  string nb_point = thousandSeparator(collection->nb_point);
  ImGui::Text("%s", nb_point.c_str());
  ImGui::NextColumn();

  //Root pos
  vec3& root = cloud->root;
  ImGui::Text("Root ");
  ImGui::NextColumn();
  ImGui::Text("%.2f  %.2f  %.2f", root.x, root.y, root.z);
  ImGui::SameLine();
  if(ImGui::Button("R", ImVec2(15,0))){
    root = vec3(0,0,0);
  }
  ImGui::Columns(1);
  ImGui::Separator();
  */

  //---------------------------
  ImGui::Columns(1);
  ImGui::Separator();
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
