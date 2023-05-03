#ifndef VK_STRUCT_H
#define VK_STRUCT_H

#include "../../common.h"

#include <vulkan/vulkan.h>
#include <vector>
#include <optional>
#include <cstdlib>
#include <stdint.h>

struct MVP{
  glm::mat4 model;
  glm::mat4 view;
  glm::mat4 proj;
};



struct struct_queueFamily_indices {
  std::optional<uint32_t> family_graphics;
  std::optional<uint32_t> family_presentation;
  bool is_complete() {
    return family_graphics.has_value() && family_presentation.has_value();
  }
};

struct struct_swapChain_details {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> mode_presentation;
};

struct Struct_texture{
  VkImage textureImage;
  VkDeviceMemory textureImageMemory;
  VkImageView textureImageView;
  VkSampler textureSampler;
  VkDescriptorImageInfo imageInfo;
};

struct Vertex {
  glm::vec3 pos;
  glm::vec3 color;
  glm::vec2 texCoord;
};



#endif
