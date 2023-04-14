#ifndef VK_STRUCT_H
#define VK_STRUCT_H

#include <vulkan/vulkan.h>
#include <vector>
#include <optional>
#include <cstdlib>
#include <stdint.h>

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


//List of required device extensions
const std::vector<const char*> required_extensions = {
  VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

//List of all validation layers
const std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
};

const int MAX_FRAMES_IN_FLIGHT = 2;


#endif
