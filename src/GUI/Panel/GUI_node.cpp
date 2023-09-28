//https://github.com/thedmd/imgui-node-editor
#include "GUI_node.h"
#include "node.h"
#include "../Node_gui.h"


//Constructor / Destructor
GUI_node::GUI_node(Node_gui* node_gui){
  //---------------------------


  //---------------------------
}
GUI_node::~GUI_node(){}

//Main function
void GUI_node::design_panel(){
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
void GUI_node::node_editor(){
  //---------------------------

  Example exampe("Simple", argc, argv);

  if (exampe.Create())
      return exampe.Run();

  //---------------------------
}
