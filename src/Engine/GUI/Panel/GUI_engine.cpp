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
/*
  std::vector<VkImage> viewport_image;
  std::vector<VkImageView> viewport_image_view;
  std::vector<VkDeviceMemory> dst_image_memory;


  int vec_image_size = vk_param->swapchain.vec_frame.size();

	viewport_image.resize(vec_image_size);
	dst_image_memory.resize(vec_image_size);

	for(uint32_t i=0; i<vec_image_size; i++){
		// Create the linear tiled destination image to copy to and to read the memory from
		VkImageCreateInfo image_info{};
		image_info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
		image_info.imageType = VK_IMAGE_TYPE_2D;
		image_info.format = VK_FORMAT_B8G8R8A8_SRGB;
		image_info.extent.width = vk_param->swapchain.vec_frame[i]->color.width;
		image_info.extent.height = vk_param->swapchain.vec_frame[i]->color.height;
		image_info.extent.depth = 1;
		image_info.arrayLayers = 1;
		image_info.mipLevels = 1;
		image_info.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		image_info.samples = VK_SAMPLE_COUNT_1_BIT;
		image_info.tiling = VK_IMAGE_TILING_LINEAR;
		image_info.usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;

		// Create the image
		vkCreateImage(vk_param->device.device, &image_info, nullptr, &viewport_image[i]);

		// Create memory to back up the image
		VkMemoryRequirements memRequirements;
		VkMemoryAllocateInfo memAllocInfo{};
		memAllocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;

		// VkDeviceMemory dstImageMemory;
		vkGetImageMemoryRequirements(vk_param->device.device, viewport_image[i], &memRequirements);
		memAllocInfo.allocationSize = memRequirements.size;

		// Memory must be host visible to copy from
		memAllocInfo.memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
		vkAllocateMemory(vk_param->device.device, &memAllocInfo, nullptr, &dst_image_memory[i]);
		vkBindImageMemory(vk_param->device.device, viewport_image[i], dst_image_memory[i], 0);

		VkCommandBuffer copyCmd = beginSingleTimeCommands(m_ViewportCommandPool);

		insertImageMemoryBarrier(
				copyCmd,
				viewport_image[i],
				VK_ACCESS_TRANSFER_READ_BIT,
				VK_ACCESS_MEMORY_READ_BIT,
				VK_IMAGE_LAYOUT_UNDEFINED,
				VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
				VK_PIPELINE_STAGE_TRANSFER_BIT,
				VK_PIPELINE_STAGE_TRANSFER_BIT,
				VkImageSubresourceRange{VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1});

		endSingleTimeCommands(copyCmd, m_ViewportCommandPool);
	}

  //create image view
  viewport_image_view.resize(viewport_image.size());

  for (uint32_t i = 0; i < viewport_image.size(); i++){
    viewport_image_view[i] = createImageView(viewport_image[i], VK_FORMAT_B8G8R8A8_SRGB, VK_IMAGE_ASPECT_COLOR_BIT);
  }
*/


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
