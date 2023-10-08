#include "GUI_profiling.h"

#include <GUI.h>

#include <Render/Render_node.h>
#include <Render/Render_param.h>
#include <Render/Vulkan/VK_engine.h>
#include <Render/Vulkan/VK_param.h>


//Constructor / Destructor
GUI_profiling::GUI_profiling(GUI* gui){
  //---------------------------

  this->gui = gui;
  this->render_node = gui->get_node_render();
  this->vk_engine = render_node->get_vk_engine();
  this->vk_param = vk_engine->get_vk_param();

  this->width = 150;
  this->profiler = new ImGuiUtils::ProfilersWindow();

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
  //---------------------------

  //auto& gpuProfilerData = inFlightQueue->GetLastFrameGpuProfilerData();
  //auto& cpuProfilerData = inFlightQueue->GetLastFrameCpuProfilerData();
  //profiler->gpuGraph.LoadFrameData(gpuProfilerData.data(), gpuProfilerData.size());
  //profiler->cpuGraph.LoadFrameData(cpuProfilerData.data(), cpuProfilerData.size());
  profiler->Render();

  //---------------------------
}

//Subfunctions
