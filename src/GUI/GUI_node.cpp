#include "GUI_node.h"
#include "GUI_param.h"

#include "Panel/GUI_panel.h"
#include "Editor/GUI_editor_text.h"
#include "Editor/GUI_editor_node.h"
#include "Panel/GUI_engine.h"
#include "Window/Menu/GUI_menubar.h"
#include "Window/Menu/GUI_option.h"
#include "Window/Menu/GUI_init.h"
#include "Control/GUI_control.h"
#include "Control/GUI_profiling.h"
#include "Engine/Render/GUI_shader.h"
#include "Panel/GUI_object.h"
#include "Window/GUI_windows.h"
#include "Style/GUI_style.h"
#include "Control/Control.h"

#include <Window/Window.h>
#include <Render/Render_node.h>
#include <Render/GPU/GPU_gui.h>
#include <Render/Vulkan/VK_engine.h>
#include <Engine.h>


//Constructor / Destructor
GUI_node::GUI_node(Engine* engine){
  //---------------------------

  this->engine = engine;
  this->window = window;
  this->render_node = engine->get_node_render();
  this->data_node = engine->get_data_node();

  this->controlManager = new Control(this);
  this->gui_param = new GUI_param();
  this->gui_profiling = new GUI_profiling(this);
  this->gui_shader = new GUI_shader(this);
  this->gui_option = new GUI_option(this);
  this->gui_object = new GUI_object(this);
  this->gui_init = new GUI_init(this);
  this->gui_menubar = new GUI_menubar(this);
  this->gui_editor_text = new GUI_editor_text(this);
  this->gui_control = new GUI_control(this);
  this->gui_engine = new GUI_engine(this);
  this->gui_panel = new GUI_panel(this);
  this->gui_windows = new GUI_windows(this);
  this->gui_style = new GUI_style(this);
  //this->gui_editor_node = new GUI_editor_node(this);

  //---------------------------
}
GUI_node::~GUI_node(){
  //---------------------------

  delete gui_param;
  delete gui_panel;
  delete gui_control;
  delete gui_option;
  delete gui_object;
  delete gui_profiling;

  //---------------------------
}

//Main function
void GUI_node::init(){
  //---------------------------

  gui_style->gui_style();
  gui_panel->set_initial_panel_focus();

  //---------------------------
}
void GUI_node::loop(){
  Render_node* render_node = engine->get_node_render();
  VK_engine* vk_engine = render_node->get_vk_engine();
  GPU_gui* gpu_gui = vk_engine->get_gpu_gui();
  //---------------------------

  ImGui_ImplVulkan_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  gui_panel->draw_panels();
  gui_windows->draw_windows();
  gpu_gui->loop_end();

  //---------------------------
}
