//https://github.com/thedmd/imgui-node-editor
#include "GUI_editor_node.h"
#include <GUI.h>


//Constructor / Destructor
GUI_editor_node::GUI_editor_node(GUI_editor_node* gui){
  //---------------------------


  //---------------------------
}
GUI_editor_node::~GUI_editor_node(){}

//Main function
void GUI_editor_node::design_panel(){
  //---------------------------

  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
  ImGui::SetNextWindowSizeConstraints(ImVec2(100, 100), ImVec2(500, 500));
  ImGui::Begin("Node editor");
  this->node_editor();
  ImGui::End();
  ImGui::PopStyleVar();

  //---------------------------
}

//Subfunction
void GUI_editor_node::node_editor(){
  //---------------------------

  //Example exampe;

  //if (exampe.Create())
    //  return exampe.Run();

  //---------------------------
}
