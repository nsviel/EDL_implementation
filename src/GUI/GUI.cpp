#include "GUI.h"

#include "Panel/Panel.h"
#include "Panel/GUI_panel.h"

#include "Element/Editor/GUI_editor_text.h"
#include "Element/Editor/GUI_editor_node.h"
#include "Element/Initialization/GUI_init.h"

#include "Window/Window.h"
#include "Window/Menu/GUI_mainmenubar.h"
#include "Window/Menu/GUI_option.h"
#include "Window/Control/GUI_control.h"
#include "Window/Style/GUI_style.h"
#include "Window/Control/Control.h"

#include "Engine/GUI_engine.h"
#include "Engine/Camera/GUI_camera.h"
#include "Engine/Data/GUI_object.h"
#include "Engine/Data/GUI_set.h"
#include "Engine/Profiler/GUI_timing.h"
#include "Engine/Render/GUI_shader.h"
#include "Engine/Data/GUI_scene.h"

#include <Engine.h>
#include <Render/Render_node.h>
#include <Render/GPU/GPU_gui.h>
#include <Render/Vulkan/VK_engine.h>


//Constructor / Destructor
GUI::GUI(Engine* engine){
  //---------------------------

  this->engine = engine;
  this->window = window;
  this->render_node = engine->get_node_render();
  this->data_node = engine->get_data_node();

  this->controlManager = new Control(this);
  this->panel = new Panel();
  this->gui_timing = new GUI_timing(this);
  this->gui_shader = new GUI_shader(this);
  this->gui_option = new GUI_option(this);
  this->gui_object = new GUI_object(this, &panel->show_object, "Object");
  this->gui_set = new GUI_set(this, &panel->show_set, "Set");
  this->gui_scene = new GUI_scene(this);
  this->gui_init = new GUI_init(this);
  this->gui_menubar = new GUI_mainmenubar(this);
  this->gui_editor_text = new GUI_editor_text(this);
  this->gui_control = new GUI_control(this);
  this->gui_engine = new GUI_engine(this);
  this->gui_panel = new GUI_panel(this);
  this->gui_style = new GUI_style(this);
  //this->gui_editor_node = new GUI_editor_node(this);
  this->gui_camera = new GUI_camera(this, &panel->show_camera, "Camera");

  //---------------------------
}
GUI::~GUI(){
  //---------------------------

  delete panel;
  delete gui_panel;
  delete gui_control;
  delete gui_option;
  delete gui_scene;
  delete gui_timing;

  //---------------------------
}

//Main function
void GUI::init(){
  //---------------------------

  gui_style->gui_style();
  gui_panel->set_initial_panel_focus();

  //---------------------------
}
void GUI::loop(){
  Render_node* render_node = engine->get_node_render();
  VK_engine* vk_engine = render_node->get_vk_engine();
  GPU_gui* gpu_gui = vk_engine->get_gpu_gui();
  //---------------------------

  ImGui_ImplVulkan_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  gui_panel->draw_panels();
  gui_camera->window();
  gui_object->window();
  gui_set->window();
  gpu_gui->loop_end();

  //---------------------------
}
