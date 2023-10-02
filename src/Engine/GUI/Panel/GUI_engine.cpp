#include "GUI_engine.h"
#include "../Node_gui.h"
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

  Struct_image* image = &vk_param->swapchain.get_frame_current()->color;

  VkDescriptorSet m_Dset;
  //m_Dset = ImGui_ImplVulkan_AddTexture(image->sampler, image->view, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);



  //ImGui::Image((ImTextureID)m_Dset, ImVec2(image->width, image->height));

float truc = 0;
ImGui::SliderFloat("FOV (°)", &truc, 100.0f, 1.0f);




  vector<Frame*>& vec_frame = this->vk_param->swapchain.vec_frame;

  //Get descriptor set from Vulkan swapchain
  vector<VkDescriptorSet> descriptor_set;
  descriptor_set.resize(vec_frame.size());
  for(uint32_t i=0; i<vec_frame.size(); i++){
    //descriptor_set[i] = ImGui_ImplVulkan_AddTexture(vec_frame[i]->color.sampler, vec_frame[i]->color.view, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
  }

//  ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
//  ImGui::Image(descriptor_set[vk_param->swapchain.frame_current_ID], ImVec2{viewportPanelSize.x, viewportPanelSize.y});







  //---------------------------
}
