#include "GUI_panel.h"
#include "../Engine/Camera/WIN_camera.h"
#include "../Engine/Data/WIN_object.h"
#include "../Engine/Data/WIN_set.h"

#include "../GUI.h"
#include <GUI_param.h>

#include "../Engine/GUI_engine.h"
#include "../Element/Editor/GUI_editor_node.h"
#include "../Element/Data/GUI_database.h"
#include "../Element/Editor/GUI_editor_text.h"
#include "../Window/Style/GUI_indicator.h"
#include "../Window/Menu/GUI_menubar.h"
#include "../Engine/Profiler/GUI_timing.h"
#include "../Engine/Render/GUI_shader.h"
#include "../Engine/Data/GUI_object.h"

#include <GUI.h>
#include <Data/Load/Loader.h>
#include <Render/Render_node.h>
#include <Engine.h>
#include <Render/Render_param.h>


//Constructor / Destructor
GUI_panel::GUI_panel(GUI* gui){
  //---------------------------

  GUI_param* gui_param = gui->get_gui_param();

  this->gui = gui;
  this->render_node = gui->get_node_render();
  this->gui_object = gui->get_gui_object();
  this->gui_timing = gui->get_gui_profiling();
  this->gui_menubar = gui->get_gui_menubar();
  this->gui_shader = gui->get_gui_shader();
  this->gui_editor_text = gui->get_gui_editor_text();
  this->gui_engine = gui->get_gui_engine();
  this->gui_database = new GUI_database(gui);
  this->win_camera = new WIN_camera(gui, &gui_param->show_camera, "Camera");
  this->win_object = new WIN_object(gui, &gui_param->show_object, "Object");
  this->win_set = new WIN_set(gui, &gui_param->show_set, "Set");

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
  gui_timing->design_panel();
  gui_engine->design_panel();
  //gui->design_panel();
  gui_database->design_panel();
  gui_object->design_panel();
  win_camera->window();
  win_object->window();
  win_set->window();

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
