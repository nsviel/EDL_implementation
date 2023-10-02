#include "GUI_engine.h"
#include "../Node_gui.h"
#include "../Control/GUI_control.h"
#include "../../Core/Node_engine.h"
#include "../../Core/Vulkan/VK_engine.h"
#include "../../Core/Vulkan/VK_param.h"
#include "../../../../extern/imgui/guizmo/ImGuizmo.h"

//Constructor / Destructor
GUI_engine::GUI_engine(Node_gui* node_gui){
  //---------------------------

  Node_engine* node_engine = node_gui->get_node_engine();
  VK_engine* vk_engine = node_engine->get_vk_engine();
  this->vk_param = vk_engine->get_vk_param();
  this->gui_control = node_gui->get_gui_control();

  //---------------------------
}
GUI_engine::~GUI_engine(){}

//Main function
void GUI_engine::design_panel(){
  //---------------------------

  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
  ImGui::SetNextWindowSizeConstraints(ImVec2(100, 100), ImVec2(500, 500));
  ImGui::Begin("Engine");
  this->engine_window();
  ImGui::End();
  ImGui::PopStyleVar();

  //---------------------------
}

//Subfunction
uint32_t GUI_engine::findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties){
  //---------------------------

  VkPhysicalDeviceMemoryProperties memProperties;
  vkGetPhysicalDeviceMemoryProperties(vk_param->device.physical_device, &memProperties);

  for(uint32_t i=0; i<memProperties.memoryTypeCount; i++){
    if((typeFilter &(1<<i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties){
      return i;
    }
  }

  throw std::runtime_error("failed to find suitable memory type!");

  //---------------------------
}
void GUI_engine::engine_window(){
  //---------------------------

  Frame* frame_edl = vk_param->renderpass_edl.get_rendering_frame();
  Struct_image* image = &frame_edl->color;
  this->descriptor = ImGui_ImplVulkan_AddTexture(image->sampler, image->view, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
  ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
  ImGui::Image(descriptor, ImVec2{viewportPanelSize.x, viewportPanelSize.y});


ImVec2 windowPos = ImGui::GetWindowPos();
ImVec2 windowSize = ImGui::GetWindowSize();
ImVec2 center = ImVec2(windowPos.x + windowSize.x * 0.5f, windowPos.y + windowSize.y * 0.5f);

  if(ImGui::IsItemHovered()){
    gui_control->make_control(center);
  }

  //---------------------------
}
