#include "GUI_left_panel.h"

#include "../Node_gui.h"
#include "../Operation/GUI_option.h"

#include "../../Engine/Dimension/Dimension.h"
#include "../../Engine/Node_engine.h"
#include "../../Node.h"


//Constructor / Destructor
GUI_left_panel::GUI_left_panel(Node* node){
  //---------------------------

  this->node = node;
  Node_engine* node_engine = node->get_node_engine();
  this->dimManager = node_engine->get_dimManager();

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
  Node_gui* node_gui = node->get_node_gui();
  this->gui_option = node_gui->get_gui_option();
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
#include "../../Engine/Vulkan/Engine.h"
#include "../../Engine/Vulkan/Data/VK_data.h"
void GUI_left_panel::left_panel_content(){
  //---------------------------

  Node_engine* node_engine = node->get_node_engine();
  Engine* engineManager = node_engine->get_engineManager();
  VK_data* vk_data = engineManager->get_vk_data();

  if(ImGui::Button("load")){
    vk_data->load_model();
  }

  //---------------------------
}
