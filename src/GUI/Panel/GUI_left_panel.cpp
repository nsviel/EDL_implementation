#include "GUI_left_panel.h"
#include "GUI_editor.h"

#include "../Node_gui.h"
#include "../Menu/GUI_menubar.h"
#include "../Control/GUI_profiling.h"
#include "../Engine/GUI_shader.h"
#include "../Panel/GUI_filemanager.h"

#include "../../Load/Node_load.h"
#include "../../Load/Processing/Loader.h"
#include "../../Engine/Node_engine.h"
#include "../../Engine/Dimension/Dimension.h"
#include "../../Node.h"
#include "../../Engine/Param_engine.h"

#include "../../../extern/imgui/TextEditor.h"
#include "../../../extern/imgui/imgui.h"


//Constructor / Destructor
GUI_left_panel::GUI_left_panel(Node_gui* node_gui){
  //---------------------------

  this->node_engine = node_gui->get_node_engine();
  this->dimManager = node_engine->get_dimManager();
  this->node_gui = node_gui;
  this->gui_filemanager = node_gui->get_gui_filemanager();
  this->gui_profiling = node_gui->get_gui_profiling();
  this->gui_menubar = node_gui->get_gui_menubar();
  this->gui_shader = node_gui->get_gui_shader();
  this->gui_editor = node_gui->get_gui_editor();

  //---------------------------
}
GUI_left_panel::~GUI_left_panel(){}

//Main function
void GUI_left_panel::draw_left_panel(){
  Tab* tab_left = dimManager->get_tab("left_panel");
  //---------------------------

  ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_MenuBar;
  ImGui::SetNextWindowPos(ImVec2(tab_left->pos.x, tab_left->pos.y));
  ImGui::SetNextWindowSize(ImVec2(tab_left->dim.x, tab_left->dim.y));
  ImGui::SetNextWindowSizeConstraints(ImVec2(tab_left->dim_min.x, tab_left->dim_min.y), ImVec2(tab_left->dim_max.x, tab_left->dim_max.y));
  ImGui::Begin("LeftPanel", NULL, window_flags);

  this->update_dim();
  this->design_top();
  this->design_bot();

  ImGui::PopStyleVar();
  ImGui::End();

  //---------------------------
}
void GUI_left_panel::design_top(){
  Tab* tab_panel_left = dimManager->get_tab("left_panel");
  //---------------------------

  // Panel menu
  gui_menubar->design_menubar();

  gui_filemanager->design_panel();
  gui_editor->design_panel();
  gui_shader->design_panel();
  gui_profiling->design_panel();

  //---------------------------
}
void GUI_left_panel::design_bot(){
  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
  //---------------------------










  //Example to build docker element
  ImGui::Begin("Left");
  ImGui::Text("Hello, left!");
  ImGui::End();

  ImGui::Begin("Down");
  ImGui::Text("Hello, down!");
  ImGui::End();

  //---------------------------
  ImGui::PopStyleVar();
}

//Subfunction
void GUI_left_panel::update_dim(){
  Tab* tab_left = dimManager->get_tab("left_panel");
  //---------------------------

  float dim_x = ImGui::GetWindowSize().x;
  if(dim_x != tab_left->dim.x){
    tab_left->dim.x = ImGui::GetWindowSize().x;
    dimManager->update();
  }

  //---------------------------
}
