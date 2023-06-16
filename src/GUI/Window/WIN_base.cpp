#include "WIN_base.h"


//Constructor / Destructor
WIN_base::WIN_base(bool* show_window, string name){
  //---------------------------

  this->show_window = show_window;
  this->item_width = 150;
  this->name = name;

  //---------------------------
}
WIN_base::~WIN_base(){}

//Main function
void WIN_base::window(){
  //---------------------------

  if(*show_window){
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1, 0.1, 0.1, 1));
    ImGui::SetNextWindowSizeConstraints(ImVec2(200, 100), ImVec2(1000, 1000));
    ImGui::Begin(name.c_str(), show_window, ImGuiWindowFlags_AlwaysAutoResize);

    this->design_window();

    ImGui::Separator();
    if(ImGui::Button("Close")){
      *show_window = false;
    }
    ImGui::End();
    ImGui::PopStyleColor();
  }

  //---------------------------
}

//Subfunction
void WIN_base::design_window(){
  //---------------------------


  //---------------------------
}
