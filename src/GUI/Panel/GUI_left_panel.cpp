#include "GUI_left_panel.h"

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
  this->left_panel_menu();
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
void GUI_left_panel::left_panel_menu(){
  static bool show_demo = false;
  //---------------------------

  if(ImGui::BeginMenuBar()){
    if(ImGui::BeginMenu("File")){
      ImGui::Checkbox("Demo", &show_demo);
      ImGui::EndMenu();
    }
    if(ImGui::BeginMenu("Option")){
      gui_option->design_option();
      ImGui::EndMenu();
    }
    if(ImGui::BeginMenu("Init")){
      ImGui::MenuItem("(demo menu)", NULL, false, false);
      ImGui::EndMenu();
    }
  }
  ImGui::EndMenuBar();

  if(show_demo){
    ImGui::ShowDemoWindow();
  }

  //---------------------------
}
void GUI_left_panel::left_panel_content(){
  //---------------------------

  gui_filemanager->tree_view();

  if(ImGui::Button("load")){
    //loaderManager->load_model();
  }

  //---------------------------
}
