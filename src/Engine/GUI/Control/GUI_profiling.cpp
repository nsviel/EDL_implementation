#include "GUI_profiling.h"

#include "../Node_gui.h"

#include "../../Core/Core_node.h"
#include "../../Core/Core_param.h"
#include "../../Core/Vulkan/VK_engine.h"
#include "../../Core/Vulkan/VK_param.h"


//Constructor / Destructor
GUI_profiling::GUI_profiling(Node_gui* node_gui){
  //---------------------------

  this->node_gui = node_gui;
  this->core_node = node_gui->get_core_node();
  this->vk_engine = core_node->get_vk_engine();
  this->vk_param = vk_engine->get_vk_param();

  this->width = 150;

  //---------------------------
}
GUI_profiling::~GUI_profiling(){}

//Main function
void GUI_profiling::design_panel(){
  //---------------------------

  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
  ImGui::SetNextWindowSizeConstraints(ImVec2(100, 100), ImVec2(500, 500));
  ImGui::Begin("Profiling");
  this->design_profiling();
  ImGui::End();
  ImGui::PopStyleVar();

  //---------------------------
}
void GUI_profiling::design_profiling(){
  ImGui::BeginChild("Profiling", ImVec2(0, 150), false);
  //---------------------------

  ImGui::TextColored(ImVec4(0.7f, 0.7f, 0.7f, 1.0f),"Profiling");

  this->device_model();

  bool update = time_update();
  this->time_drawig(update);
  this->time_general(update);

  //---------------------------
  ImGui::EndChild();
}

//Subfunctions
void GUI_profiling::device_model(){
  //---------------------------

  ImGui::Text("Device model ");
  ImGui::SameLine();
  ImGui::TextColored(ImVec4(0.5, 1, 0.5, 1), "%s", vk_param->device.model.c_str());

  //---------------------------
}
bool GUI_profiling::time_update(){
  //---------------------------

  static timer_time t1 = timer.start_t();
  float duration = timer.stop_ms(t1) / 1000;
  if(duration >= 0.5){
    t1 = timer.start_t();
    return true;
  }

  //---------------------------
  return false;
}
void GUI_profiling::time_drawig(bool update){
  ImGuiIO io = ImGui::GetIO();
  //---------------------------

  static float mean_draw_frame;
  static float mean_renderpass_scene;
  static float mean_renderpass_edl;
  static float mean_renderpass_ui;
  if(update){
    mean_draw_frame = fct_mean_and_clear(vk_param->time.draw_frame);
    mean_renderpass_scene = fct_mean_and_clear(vk_param->time.renderpass_scene);
    mean_renderpass_edl = fct_mean_and_clear(vk_param->time.renderpass_edl);
    mean_renderpass_ui = fct_mean_and_clear(vk_param->time.renderpass_ui);
  }

  ImGui::Text("Time draw frame ");
  ImGui::SameLine();
  ImGui::TextColored(ImVec4(0.5, 1, 0.5, 1), "%.1f", mean_draw_frame);
  ImGui::SameLine();
  ImGui::Text(" ms");

  //Time init
  ImGui::Text("Time renderpass scene ");
  ImGui::SameLine();
  ImGui::TextColored(ImVec4(0.5, 1, 0.5, 1), "%.1f", mean_renderpass_scene);
  ImGui::SameLine();
  ImGui::Text(" ms");

  //Time init
  ImGui::Text("Time renderpass EDL ");
  ImGui::SameLine();
  ImGui::TextColored(ImVec4(0.5, 1, 0.5, 1), "%.1f", mean_renderpass_edl);
  ImGui::SameLine();
  ImGui::Text(" ms");

  //Time init
  ImGui::Text("Time renderpass ui ");
  ImGui::SameLine();
  ImGui::TextColored(ImVec4(0.5, 1, 0.5, 1), "%.1f", mean_renderpass_ui);
  ImGui::SameLine();
  ImGui::Text(" ms");

  //---------------------------
}
void GUI_profiling::time_general(bool update){
  ImGuiIO io = ImGui::GetIO();
  //---------------------------

  static float mean_engine_fps;
  if(update){
    mean_engine_fps = fct_mean_and_clear(vk_param->time.engine_fps);
  }

  //Time init
  ImGui::Text("Time initialization ");
  ImGui::SameLine();
  ImGui::TextColored(ImVec4(0.5, 1, 0.5, 1), "%.1f", vk_param->time.engine_init);
  ImGui::SameLine();
  ImGui::Text(" ms");

  //FPS
  ImGui::TextColored(ImVec4(0.5, 1, 0.5, 1), "%.1f", 1000.0f / mean_engine_fps);
  ImGui::SameLine();
  ImGui::Text(" ms/frame [");
  ImGui::SameLine();
  ImGui::TextColored(ImVec4(0.5, 1, 0.5, 1), "%.1f", mean_engine_fps); //io.Framerate
  ImGui::SameLine();
  ImGui::Text(" FPS ]");

  //---------------------------
}
