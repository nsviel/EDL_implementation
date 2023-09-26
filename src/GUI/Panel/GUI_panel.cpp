#include "GUI_panel.h"
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
GUI_panel::GUI_panel(Node_gui* node_gui){
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
GUI_panel::~GUI_panel(){}

//Main function
void GUI_panel::draw_panels(){
  Tab* tab_left = dimManager->get_tab("left_panel");
  //---------------------------

  this->docker_space_main();
  dimManager->update();
  gui_menubar->design_menubar();
  gui_filemanager->design_panel();
  gui_editor->design_panel();
  gui_shader->design_panel();
  gui_profiling->design_panel();

  static bool show_demo_window = true;
  if (show_demo_window){
    ImGui::ShowDemoWindow(&show_demo_window);
  }

  //---------------------------
}

//Subfunction
void GUI_panel::docker_space_main(){
  //---------------------------

  static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;

  // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
  // because it would be confusing to have two docking targets within each others.
  ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

  ImGuiViewport* viewport = ImGui::GetMainViewport();
  ImGui::SetNextWindowPos(viewport->Pos);
  ImGui::SetNextWindowSize(viewport->Size);
  ImGui::SetNextWindowViewport(viewport->ID);

  window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
  window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
  window_flags |= ImGuiWindowFlags_NoBackground;

  // Main dock space
  ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
  ImGui::Begin("dock_space_main", nullptr, window_flags);
  ImGui::PopStyleVar(3);

  ImGuiIO& io = ImGui::GetIO();
  if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable){
  	ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
  	ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
  }

  ImGui::End();

  //---------------------------
}
