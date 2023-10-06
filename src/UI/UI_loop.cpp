#include "UI_loop.h"
#include "../Engine/Engine.h"
#include "../Engine/Render/Render_node.h"
#include "../Engine/Render/GPU/GPU_gui.h"
#include "../Engine/Render/Vulkan/VK_engine.h"
#include "../Engine/Render/Camera/Camera.h"
#include "../Engine/GUI/GUI_node.h"



//Constructor / Destructor
UI_loop::UI_loop(){
  //---------------------------


  //---------------------------
}
UI_loop::~UI_loop(){}

//Main function
void UI_loop::init(Engine* engine){
  GUI_node* gui_node = engine->get_gui_node();
  //---------------------------

  gui_node->init();

  //---------------------------
}
void UI_loop::loop(Engine* engine){
  GUI_node* gui_node = engine->get_gui_node();
  Render_node* render_node = engine->get_node_render();
  VK_engine* vk_engine = render_node->get_vk_engine();
  GPU_gui* gpu_gui = vk_engine->get_gpu_gui();
  //---------------------------

  this->loop_start();
  gui_node->loop();
  gpu_gui->loop_end();

  //---------------------------
}

//Subfunction
void UI_loop::loop_start(){
  //---------------------------

  ImGui_ImplVulkan_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  //---------------------------
}
void UI_loop::loop_end(){
  //---------------------------

  ImGui::Render();
  this->draw_data = ImGui::GetDrawData();

  //---------------------------
}
void UI_loop::loop_draw(VkCommandBuffer command){
  //---------------------------

  ImGui_ImplVulkan_RenderDrawData(draw_data, command);

  //---------------------------
}
