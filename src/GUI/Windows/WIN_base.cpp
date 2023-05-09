#include "WIN_base.h"

#include "../Node_gui.h"

#include "image/IconsFontAwesome5.h"


//Constructor / Destructor
WIN_base::WIN_base(Node_gui* node_gui, bool* show_window, const char* icon){
  //---------------------------

  this->node_gui = node_gui;
  this->show_window = show_window;
  this->item_width = 150;
  this->icon = icon;

  //---------------------------
}
WIN_base::~WIN_base(){}

//Main function
void WIN_base::window(){
  //---------------------------

  if(*show_window){
    ImGui::Begin(icon, show_window, ImGuiWindowFlags_AlwaysAutoResize);

    this->design_window();

    ImGui::Separator();
    if(ImGui::Button("Close")){
      *show_window = false;
    }
    ImGui::End();
  }

  //---------------------------
}

//Subfunction
void WIN_base::design_window(){
  //---------------------------


  //---------------------------
}
