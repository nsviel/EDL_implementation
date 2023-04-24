#ifndef VK_STRUCT_H
#define VK_STRUCT_H

#include "../../common.h"

#include <vulkan/vulkan.h>
#include <vector>
#include <optional>
#include <cstdlib>
#include <stdint.h>

struct UniformBufferObject {
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 proj;
};

static uint32_t currentFrame = 0;


//List of all validation layers
const std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
};

static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,VkDebugUtilsMessageTypeFlagsEXT messageType,const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,void* pUserData){
  //---------------------------

  std::cerr << "--------------------------" << std::endl;
  std::cerr << "[\033[1;32mVL\033[0m] " << pCallbackData->pMessage << std::endl;

  //---------------------------
  return VK_FALSE;
}

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


const int MAX_FRAMES_IN_FLIGHT = 2;


struct Vertex {
  glm::vec2 pos;
  glm::vec3 color;

  static VkVertexInputBindingDescription getBindingDescription() {
    VkVertexInputBindingDescription bindingDescription{};
    bindingDescription.binding = 0;
    bindingDescription.stride = sizeof(Vertex);
    bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
    return bindingDescription;
  }

  static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions() {
    std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions{};
    attributeDescriptions[0].binding = 0;
    attributeDescriptions[0].location = 0;
    attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
    attributeDescriptions[0].offset = offsetof(Vertex, pos);
    attributeDescriptions[1].binding = 0;
    attributeDescriptions[1].location = 1;
    attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
    attributeDescriptions[1].offset = offsetof(Vertex, color);
    return attributeDescriptions;
  }

};

const std::vector<Vertex> vertices = {
    {{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
    {{0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
    {{0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
    {{-0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}}
};
const std::vector<uint16_t> indices = {
    0, 1, 2, 2, 3, 0
};



#endif
