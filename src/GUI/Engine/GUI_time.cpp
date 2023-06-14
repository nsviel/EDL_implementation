#include "GUI_time.h"

#include "../Node_gui.h"

#include "../../Engine/Node_engine.h"
#include "../../Engine/Param_engine.h"
#include "../../Engine/Vulkan/VK_engine.h"
#include "../../Engine/Vulkan/VK_param.h"


//Constructor / Destructor
GUI_time::GUI_time(Node_gui* node_gui){
  //---------------------------

  this->node_gui = node_gui;
  this->node_engine = node_gui->get_node_engine();
  this->vk_engine = node_engine->get_vk_engine();
  this->vk_param = vk_engine->get_vk_param();

  this->width = 150;

  //---------------------------
}
GUI_time::~GUI_time(){}

//Main function
void GUI_time::design_time(){
  //---------------------------

  ImVec2 windowSize = ImGui::GetWindowSize();
  float widgetHeight = 100.0f; // Adjust the height of the widget as needed
  float widgetYPosition = windowSize.y - widgetHeight - ImGui::GetStyle().ItemSpacing.y;
  ImGui::SetCursorPos(ImVec2(8, widgetYPosition));

  this->time_drawig();
  this->time_general();

  //---------------------------
}

//Subfunctions
void GUI_time::time_drawig(){
  ImGuiIO io = ImGui::GetIO();
  //---------------------------

  //Time init
  ImGui::Text("Time draw frame ");
  ImGui::SameLine();
  ImGui::TextColored(ImVec4(0.5, 1, 0.5, 1), "%.1f", vk_param->time.draw_frame);
  ImGui::SameLine();
  ImGui::Text(" ms");

  //Time init
  ImGui::Text("Time renderpass scene ");
  ImGui::SameLine();
  ImGui::TextColored(ImVec4(0.5, 1, 0.5, 1), "%.1f", vk_param->time.renderpass_scene);
  ImGui::SameLine();
  ImGui::Text(" ms");

  //Time init
  ImGui::Text("Time renderpass render ");
  ImGui::SameLine();
  ImGui::TextColored(ImVec4(0.5, 1, 0.5, 1), "%.1f", vk_param->time.renderpass_render);
  ImGui::SameLine();
  ImGui::Text(" ms");

  //Time init
  ImGui::Text("Time renderpass ui ");
  ImGui::SameLine();
  ImGui::TextColored(ImVec4(0.5, 1, 0.5, 1), "%.1f", vk_param->time.renderpass_ui);
  ImGui::SameLine();
  ImGui::Text(" ms");

  //Time init
  ImGui::Text("Time initialization ");
  ImGui::SameLine();
  ImGui::TextColored(ImVec4(0.5, 1, 0.5, 1), "%.1f", vk_param->time.engine_init);
  ImGui::SameLine();
  ImGui::Text(" ms");

  //FPS
  ImGui::TextColored(ImVec4(0.5, 1, 0.5, 1), "%.1f", 1000.0f / vk_param->time.engine_fps);
  ImGui::SameLine();
  ImGui::Text(" ms/frame [");
  ImGui::SameLine();
  ImGui::TextColored(ImVec4(0.5, 1, 0.5, 1), "%.1f", vk_param->time.engine_fps); //io.Framerate
  ImGui::SameLine();
  ImGui::Text(" FPS ]");

  //---------------------------
}
void GUI_time::time_general(){
  ImGuiIO io = ImGui::GetIO();
  //---------------------------

  //Time init
  ImGui::Text("Time draw frame ");
  ImGui::SameLine();
  ImGui::TextColored(ImVec4(0.5, 1, 0.5, 1), "%.1f", vk_param->time.draw_frame);
  ImGui::SameLine();
  ImGui::Text(" ms");

  //Time init
  ImGui::Text("Time renderpass scene ");
  ImGui::SameLine();
  ImGui::TextColored(ImVec4(0.5, 1, 0.5, 1), "%.1f", vk_param->time.renderpass_scene);
  ImGui::SameLine();
  ImGui::Text(" ms");

  //Time init
  ImGui::Text("Time renderpass render ");
  ImGui::SameLine();
  ImGui::TextColored(ImVec4(0.5, 1, 0.5, 1), "%.1f", vk_param->time.renderpass_render);
  ImGui::SameLine();
  ImGui::Text(" ms");

  //Time init
  ImGui::Text("Time renderpass ui ");
  ImGui::SameLine();
  ImGui::TextColored(ImVec4(0.5, 1, 0.5, 1), "%.1f", vk_param->time.renderpass_ui);
  ImGui::SameLine();
  ImGui::Text(" ms");

  //Time init
  ImGui::Text("Time initialization ");
  ImGui::SameLine();
  ImGui::TextColored(ImVec4(0.5, 1, 0.5, 1), "%.1f", vk_param->time.engine_init);
  ImGui::SameLine();
  ImGui::Text(" ms");

  //FPS
  ImGui::TextColored(ImVec4(0.5, 1, 0.5, 1), "%.1f", 1000.0f / vk_param->time.engine_fps);
  ImGui::SameLine();
  ImGui::Text(" ms/frame [");
  ImGui::SameLine();
  ImGui::TextColored(ImVec4(0.5, 1, 0.5, 1), "%.1f", vk_param->time.engine_fps); //io.Framerate
  ImGui::SameLine();
  ImGui::Text(" FPS ]");

  //---------------------------
}
