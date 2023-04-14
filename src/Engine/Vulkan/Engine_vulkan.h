#ifndef ENGINE_VULKAN_H
#define ENGINE_VULKAN_H

#include "VK_struct.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <optional>
#include <cstdlib>
#include <stdint.h>


class Node_engine;
class Engine_window;
class VK_instance;
class VK_device;
class VK_swapchain;
class VK_renderpass;
class VK_pipeline;
class VK_framebuffer;
class VK_command;


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
  void create_sync_objects();

  //Misc function
  void recreate_swapChain();
  void cleanup_swapChain();


  inline VK_device* get_vk_device(){return vk_device;}
  inline VK_framebuffer* get_vk_framebuffer(){return vk_framebuffer;}
  inline Engine_window* get_engine_window(){return engine_window;}

  inline VkInstance get_vk_instance(){return instance;}
  inline VkPhysicalDevice get_physical_device(){return physical_device;}
  inline VkDevice get_device(){return device;}
  inline VkSurfaceKHR get_vk_surface(){return surface;}
  inline VkQueue get_queue_graphics(){return queue_graphics;}
  inline VkQueue get_queue_presentation(){return queue_presentation;}
  inline VkRenderPass get_renderPass(){return renderPass;}
  inline VkSwapchainKHR get_swapChain(){return swapChain;}
  inline VkFormat get_swapChain_image_format(){return swapChain_image_format;}
  inline VkExtent2D get_swapChain_extent(){return swapChain_extent;}
  inline VkPipeline get_graphicsPipeline(){return graphicsPipeline;}

  inline std::vector<VkImage> get_swapChain_images(){return swapChain_images;}
  inline std::vector<VkImageView> get_swapChain_image_views(){return swapChain_image_views;}
  inline std::vector<VkFramebuffer> get_swapChain_fbo(){return swapChain_fbo;}

private:
  Node_engine* node_engine;
  Engine_window* engine_window;
  VK_instance* vk_instance;
  VK_device* vk_device;
  VK_swapchain* vk_swapchain;
  VK_renderpass* vk_renderpass;
  VK_pipeline* vk_pipeline;
  VK_framebuffer* vk_framebuffer;
  VK_command* vk_command;

  VkInstance instance;
  VkDebugUtilsMessengerEXT debugMessenger;
  VkDevice device;
  VkPhysicalDevice physical_device;
  VkSurfaceKHR surface;
  VkRenderPass renderPass;
  VkPipelineLayout pipelineLayout;
  VkPipeline graphicsPipeline;
  VkCommandPool commandPool;
  VkQueue queue_graphics;
  VkQueue queue_presentation;
  VkSwapchainKHR swapChain;
  VkFormat swapChain_image_format;
  VkExtent2D swapChain_extent;

  std::vector<VkCommandBuffer> commandBuffers;
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
