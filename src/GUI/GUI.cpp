#include "GUI.h"

#include "../Engine/Core/Dimension.h"
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
  vec2 dim_win = dimManager->get_win_dim();
  //---------------------------

  ImGui::ShowDemoWindow();

say(dim_win);

    //Options
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoBringToFrontOnFocus;
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(250, 100));
    //ImGui::SetNextWindowSizeConstraints(ImVec2(1, 10), ImVec2(500, win_dim.y));
    ImGui::Begin("LeftPanel##botOuter", NULL, window_flags);

    ImGui::Button("hello");


    ImGui::PopStyleVar();
    ImGui::End();

  //---------------------------
}
