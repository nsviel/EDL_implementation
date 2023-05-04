#include "GUI.h"

#include "../Engine/Dimension/Dimension.h"
#include "../Engine/Node_engine.h"


//Constructor / Destructor
GUI::GUI(Node_engine* node_engine){
  //---------------------------

  this->node_engine = node_engine;
  this->dimManager = node_engine->get_dimManager();

  //---------------------------
}
GUI::~GUI(){
  //---------------------------


  //---------------------------
}

//Main function


//Loop functions
void GUI::loop(){
  Tab* tab_left = dimManager->get_tab("left_panel");
  //---------------------------

  ImGui::ShowDemoWindow();


  //Left panel
  ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoBringToFrontOnFocus;
  ImGui::SetNextWindowPos(ImVec2(tab_left->pos.x, tab_left->pos.y));
  ImGui::SetNextWindowSize(ImVec2(tab_left->dim.x, tab_left->dim.y));
  ImGui::SetNextWindowSizeConstraints(ImVec2(tab_left->dim_min.x, tab_left->dim_min.y), ImVec2(tab_left->dim_max.x, tab_left->dim_max.y));
  ImGui::Begin("LeftPanel##botOuter", NULL, window_flags);

  //Update panel dimension
  float dim_x = ImGui::GetWindowSize().x;
  if(dim_x != tab_left->dim.x){
    tab_left->dim.x = ImGui::GetWindowSize().x;
    dimManager->update();
  }

  ImGui::Button("hello");


  ImGui::PopStyleVar();
  ImGui::End();

  //---------------------------
}
