#include "GUI_panel.h"
#include "GUI_engine.h"
#include "../Editor/GUI_editor_node.h"
#include "GUI_database.h"

#include "../Editor/GUI_editor_text.h"
#include "../GUI_node.h"
#include "../Style/GUI_indicator.h"
#include "../Menu/GUI_menubar.h"
#include "../Control/GUI_profiling.h"
#include "../Engine/GUI_shader.h"
#include "../Panel/GUI_object.h"

#include <Data/Load/Loader.h>
#include <Render/Render_node.h>
#include <Engine.h>
#include <Render/Render_param.h>


//Constructor / Destructor
GUI_panel::GUI_panel(GUI_node* gui_node){
  //---------------------------

  this->gui_node = gui_node;
  this->render_node = gui_node->get_node_render();
  this->gui_node = gui_node;
  this->gui_object = gui_node->get_gui_object();
  this->gui_profiling = gui_node->get_gui_profiling();
  this->gui_menubar = gui_node->get_gui_menubar();
  this->gui_shader = gui_node->get_gui_shader();
  this->gui_editor_text = gui_node->get_gui_editor_text();
  this->gui_engine = gui_node->get_gui_engine();
  this->gui_database = new GUI_database(gui_node);

  //---------------------------
}
GUI_panel::~GUI_panel(){}

//Main function
void GUI_panel::draw_panels(){
  //---------------------------

  this->docker_space_main();
  gui_menubar->design_menubar();
  gui_editor_text->design_panel();
  gui_shader->design_panel();
  gui_profiling->design_panel();
  gui_engine->design_panel();
  //gui_node->design_panel();
  gui_database->design_panel();
  gui_object->design_panel();

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
void GUI_panel::set_initial_panel_focus(){
  //---------------------------

  ImGui::SetWindowFocus("Object");

  //---------------------------
}
