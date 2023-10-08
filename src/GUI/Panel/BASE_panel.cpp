#include <Panel/BASE_panel.h>


//Constructor / Destructor
BASE_panel::BASE_panel(bool* show_window, string name){
  //---------------------------

  this->show_window = show_window;
  this->item_width = 150;
  this->name = name;

  //---------------------------
}
BASE_panel::~BASE_panel(){}

//Main function
void BASE_panel::window(){
  //---------------------------

  if(*show_window){
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1, 0.1, 0.1, 1));
    ImGui::SetNextWindowSizeConstraints(ImVec2(200, 100), ImVec2(1000, 1000));
    ImGui::Begin(name.c_str(), show_window, ImGuiWindowFlags_AlwaysAutoResize);

    this->design_window();

    ImGui::Separator();
    ImGui::End();
    ImGui::PopStyleColor();
  }

  //---------------------------
}

//Subfunction
void BASE_panel::design_window(){
  //---------------------------


  //---------------------------
}
