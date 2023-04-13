#ifndef ENGINE_VULKAN_H
#define ENGINE_VULKAN_H

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <optional>
#include <cstdlib>
#include <stdint.h>

#ifndef STRUCT_FOO
#define STRUCT_FOO
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
#endif
class Node_engine;
class Engine_window;
class VK_instance;
class VK_device;


class Engine_vulkan
{
public:
  //Constructor / Destructor
  Engine_vulkan(Node_engine* node_engine);
  ~Engine_vulkan();

public:
  //Main functions
  void init_vulkan();
  void main_loop();
  void draw_frame();
  void clean_vulkan();

  //Subfunction
  void create_instance();
  void create_window_surface();
  void create_logical_device();
  void create_swapChain();
  void create_image_views();
  void create_render_pass();
  void create_graphics_pipeline();
  void create_framebuffers();
  void create_command_pool();
  void create_command_buffers();
  void create_sync_objects();

  //Misc function
  void select_physical_device();
  bool is_device_suitable(VkPhysicalDevice device);
  bool check_extension_support(VkPhysicalDevice device);
  struct_swapChain_details find_swapChain_details(VkPhysicalDevice device);
  struct_queueFamily_indices find_queue_families(VkPhysicalDevice device);
  std::vector<char> read_file(const std::string& filename);

  //Swap chian settings
  VkSurfaceFormatKHR swapChain_surface_format(const std::vector<VkSurfaceFormatKHR>& availableFormats);
  VkPresentModeKHR swapChain_presentation_mode(const std::vector<VkPresentModeKHR>& availablePresentModes);
  VkExtent2D swapChain_extent_setting(const VkSurfaceCapabilitiesKHR& capabilities);
  void recreate_swapChain();
  void cleanup_swapChain();

  //Graphics pipeline
  VkShaderModule create_shader_module(const std::vector<char>& code);
  void record_command_buffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

  //Validation layers
  bool check_validationLayer_support();
  std::vector<const char*> get_required_extensions();
  void setup_debug_messenger();

  inline VkInstance get_vk_instance(){return instance;}
  inline VkPhysicalDevice get_vk_gpu(){return physical_device;}
  inline VkDevice get_vk_device(){return device;}
  inline VkSurfaceKHR get_vk_surface(){return surface;}
  inline VkQueue get_queue_graphics(){return queue_graphics;}
  inline VkRenderPass get_renderPass(){return renderPass;}

private:
  Node_engine* node_engine;
  Engine_window* engine_window;
  VK_instance* vk_instance;
  VK_device* vk_device;

  VkInstance instance;



  VkDebugUtilsMessengerEXT debugMessenger;
  VkDevice device;
  VkPhysicalDevice physical_device;
  VkSurfaceKHR surface;

  VkRenderPass renderPass;
  VkPipelineLayout pipelineLayout;
  VkPipeline graphicsPipeline;
  VkCommandPool commandPool;
  std::vector<VkCommandBuffer> commandBuffers;

  VkQueue queue_graphics;
  VkQueue queue_presentation;

  VkSwapchainKHR swapChain;
  VkFormat swapChain_image_format;
  VkExtent2D swapChain_extent;
  std::vector<VkImage> swapChain_images;
  std::vector<VkImageView> swapChain_image_views;
  std::vector<VkFramebuffer> swapChain_fbo;

  std::vector<VkSemaphore> imageAvailableSemaphores;
  std::vector<VkSemaphore> renderFinishedSemaphores;
  std::vector<VkFence> inFlightFences;

  bool framebufferResized = false;
  bool with_validation_layer = true;
};

#endif
