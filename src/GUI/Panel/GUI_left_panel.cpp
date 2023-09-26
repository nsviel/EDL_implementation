#include "GUI_left_panel.h"
#include "GUI_editor.h"

#include "../Node_gui.h"
#include "../Menu/GUI_menubar.h"
#include "../Control/GUI_profiling.h"
#include "../Engine/GUI_shader.h"
#include "../Data/GUI_filemanager.h"

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

  // Panel scene tree
  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
  vec2* gui_ltp_dim = dimManager->get_gui_ltp_dim();
  ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar;
  ImGui::SetNextWindowSize(ImVec2(tab_panel_left->dim.x, 105));
  ImGui::Begin("LeftPanel##topInner", NULL, window_flags);
  {
    gui_filemanager->tree_view(tab_panel_left->dim.x);
  }
  ImGui::End();
  ImGui::SetCursorPos(ImVec2(8, 125));
  ImGui::PopStyleVar();

  //---------------------------
}
void GUI_left_panel::design_bot(){
  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
  //---------------------------

  gui_shader->design_shader();
  gui_profiling->design_profiling();
  gui_editor->design_editor();







  static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;

  // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
  // because it would be confusing to have two docking targets within each others.
  ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

  ImGuiViewport* viewport = ImGui::GetMainViewport();
  ImGui::SetNextWindowPos(viewport->Pos);
  ImGui::SetNextWindowSize(viewport->Size);
  ImGui::SetNextWindowViewport(viewport->ID);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
  window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
  window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;


  // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
  if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
  window_flags |= ImGuiWindowFlags_NoBackground;


  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
  ImGui::Begin("DockSpace", nullptr, window_flags);
  ImGui::PopStyleVar();
  ImGui::PopStyleVar(2);


  // DockSpace
  ImGuiIO& io = ImGui::GetIO();
  if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
  {
  	ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
  	ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
  }

  ImGui::End();

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
