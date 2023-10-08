#include "GUI_set.h"

#include <GUI.h>
#include <GUI_param.h>

#include <Operation/Transformation/Attribut.h>


//Constructor / Destructor
GUI_set::GUI_set(GUI* gui, bool* show_window, string name) : BASE_panel(show_window, name){
  //---------------------------

  this->gui_param = gui->get_gui_param();

  this->item_width = 150;

  //---------------------------
}
GUI_set::~GUI_set(){}

//Main function
void GUI_set::design_window(){
  //---------------------------

  this->set_info(set_selected);
  this->set_parameter(set_selected);

  //---------------------------
}

//Subfunction
void GUI_set::set_info(Set* set){
  //---------------------------

  this->name = "Set " + set->name;

  //---------------------------
}
void GUI_set::set_parameter(Set* set){
  ImGui::Columns(2);
  //---------------------------

  //Visibility
  ImGui::Text("Visibility");
  ImGui::NextColumn();
  if(ImGui::Checkbox("##4555", &set->is_visible)){
    //Setfunc setfunc;
    //setfunc.set_visibility(set, set->is_visible);
  }
  ImGui::NextColumn();

  //Name
  ImGui::SetColumnWidth(-1,75);
  ImGui::Text("Name");
  ImGui::NextColumn();
  static char str_n[256];
  strcpy(str_n, set->name.c_str());
  if(ImGui::InputText("##name", str_n, IM_ARRAYSIZE(str_n), ImGuiInputTextFlags_EnterReturnsTrue)){
    set->name = str_n;
  }
  ImGui::NextColumn();

  //Number of object
  ImGui::Text("Nb object");
  ImGui::NextColumn();
  string nb_object = thousandSeparator(set->nb_object);
  ImGui::Text("%s", nb_object.c_str());
  ImGui::NextColumn();

  //---------------------------
  ImGui::Columns(1);
}
