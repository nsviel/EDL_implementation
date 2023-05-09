#include "GUI_left_panel.h"
#include "GUI_menubar.h"

#include "../Node_gui.h"
#include "../Operation/GUI_option.h"
#include "../Module/GUI_filemanager.h"

#include "../../Load/Node_load.h"
#include "../../Load/Processing/Loader.h"
#include "../../Engine/Node_engine.h"
#include "../../Engine/Dimension/Dimension.h"
#include "../../Node.h"


//Constructor / Destructor
GUI_left_panel::GUI_left_panel(Node_gui* node_gui){
  //---------------------------

  Node_engine* node_engine = node_gui->get_node_engine();
  this->dimManager = node_engine->get_dimManager();
  this->node_gui = node_gui;
  this->gui_filemanager = node_gui->get_gui_filemanager();
  this->gui_option = node_gui->get_gui_option();
  this->gui_menubar = node_gui->get_gui_menubar();

  //---------------------------
}
GUI_left_panel::~GUI_left_panel(){
  //---------------------------


  //---------------------------
}

//Main function


//Loop functions
void GUI_left_panel::draw_left_panel(){
  Tab* tab_left = dimManager->get_tab("left_panel");
  //---------------------------

  ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_MenuBar;
  ImGui::SetNextWindowPos(ImVec2(tab_left->pos.x, tab_left->pos.y));
  ImGui::SetNextWindowSize(ImVec2(tab_left->dim.x, tab_left->dim.y));
  ImGui::SetNextWindowSizeConstraints(ImVec2(tab_left->dim_min.x, tab_left->dim_min.y), ImVec2(tab_left->dim_max.x, tab_left->dim_max.y));
  ImGui::Begin("LeftPanel##botOuter", NULL, window_flags);

  this->left_panel_dim();
  gui_menubar->design_menubar();
  this->left_panel_content();

  ImGui::PopStyleVar();
  ImGui::End();

  //---------------------------
}
void GUI_left_panel::left_panel_dim(){
  Tab* tab_left = dimManager->get_tab("left_panel");
  //---------------------------

  float dim_x = ImGui::GetWindowSize().x;
  if(dim_x != tab_left->dim.x){
    tab_left->dim.x = ImGui::GetWindowSize().x;
    dimManager->update();
  }

  //---------------------------
}
void GUI_left_panel::left_panel_content(){
  Tab* tab_panel_left = dimManager->get_tab("left_panel");
  //---------------------------

  vec2* gui_ltp_dim = dimManager->get_gui_ltp_dim();
  ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar;
  ImGui::SetNextWindowSize(ImVec2(tab_panel_left->dim.x, 100));
  ImGui::SetNextWindowPos(ImVec2(0, 20));
  ImGui::Begin("LeftPanel##topInner", NULL, window_flags);
  gui_filemanager->tree_view();
  ImGui::End();
  ImGui::SetCursorPos(ImVec2(0, 125));

  Node_load* Node_load = node_gui->get_node_load();
  Loader* loaderManager = Node_load->get_loaderManager();
  if(ImGui::Button("load")){
    loaderManager->load_object_zenity();
  }

  //---------------------------
}
