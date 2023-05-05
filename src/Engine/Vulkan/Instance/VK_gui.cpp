#include "VK_gui.h"
#include "VK_window.h"
#include "VK_instance.h"

#include "../Device/VK_device.h"
#include "../Pipeline/VK_renderpass.h"
#include "../Engine_vulkan.h"
#include "../Command/VK_command.h"
#include "../VK_parameter.h"


//Constructor / Destructor
VK_gui::VK_gui(Engine_vulkan* engine_vulkan){
  //---------------------------

  this->engine_vulkan = engine_vulkan;
  this->vk_command = engine_vulkan->get_vk_command();
  this->vk_window = engine_vulkan->get_vk_window();
  this->vk_instance = engine_vulkan->get_vk_instance();
  this->vk_device = engine_vulkan->get_vk_device();
  this->vk_renderpass = engine_vulkan->get_vk_renderpass();

  //---------------------------
}
VK_gui::~VK_gui(){
  //---------------------------


  //---------------------------
}

//Main function
void VK_gui::cleanup(){
  VK_device* vk_device = engine_vulkan->get_vk_device();
  //---------------------------

  VkDevice device = vk_device->get_device();
  vkDestroyDescriptorPool(device, imguiPool, nullptr);

  ImGui_ImplVulkan_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  //---------------------------
}
void VK_gui::command_gui(VkCommandBuffer command_buffer){
  //---------------------------

  ImGui_ImplVulkan_RenderDrawData(draw_data, command_buffer);

  //---------------------------
}

//Init function
void VK_gui::init_gui(){
  //---------------------------

  this->gui_vulkan();
  this->gui_font();
  this->gui_style();

  //---------------------------
}
void VK_gui::gui_vulkan(){
  GLFWwindow* window = vk_window->get_window();
  VkInstance instance = vk_instance->get_instance();
  VkPhysicalDevice physical_device = vk_device->get_physical_device();
  VkDevice device = vk_device->get_device();
  VkSurfaceKHR surface = vk_window->get_surface();
  VkQueue queue_graphics = vk_device->get_queue_graphics();
  VkRenderPass renderPass = vk_renderpass->get_renderPass();
  //---------------------------

  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGui::StyleColorsDark();

  // Create Descriptor Pool
  VkDescriptorPoolSize pool_sizes[] ={
    { VK_DESCRIPTOR_TYPE_SAMPLER, 1000 },
    { VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1000 },
    { VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, 1000 },
    { VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 1000 },
    { VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER, 1000 },
    { VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER, 1000 },
    { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1000 },
    { VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 1000 },
    { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, 1000 },
    { VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC, 1000 },
    { VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT, 1000 }
  };
  VkDescriptorPoolCreateInfo pool_info = {};
  pool_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
  pool_info.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
  pool_info.maxSets = 1000 * IM_ARRAYSIZE(pool_sizes);
  pool_info.poolSizeCount = (uint32_t)IM_ARRAYSIZE(pool_sizes);
  pool_info.pPoolSizes = pool_sizes;

  VkResult result = vkCreateDescriptorPool(device, &pool_info, nullptr, &imguiPool);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create gui");
  }

  // Setup Platform/Renderer bindings
  ImGui_ImplGlfw_InitForVulkan(window, true);
  ImGui_ImplVulkan_InitInfo init_info = {};
  init_info.Instance = instance;
  init_info.PhysicalDevice = physical_device;
  init_info.Device = device;
  init_info.Queue = queue_graphics;
  init_info.DescriptorPool = imguiPool;
  init_info.PipelineCache = VK_NULL_HANDLE;
  init_info.MinImageCount = 3;
  init_info.ImageCount = 3;
  init_info.MSAASamples = VK_SAMPLE_COUNT_1_BIT;

  ImGui_ImplVulkan_Init(&init_info, renderPass);

  //---------------------------
}
void VK_gui::gui_style(){
  ImGuiStyle& style = ImGui::GetStyle();
  ImGuiIO& io = ImGui::GetIO();
  //---------------------------

  //Formatting
  style.FrameBorderSize = 0.0f;
  style.WindowPadding.x = 5.0f;

  //Rounding
  style.WindowRounding = 0.0f;
  style.TabRounding = 0.0f;
  style.GrabRounding = 0.0f;
  style.ScrollbarRounding = 0.0f;
  style.ChildRounding = 0.0f;
  style.FrameRounding = 0.0f;
  style.PopupRounding = 0.0f;
  //style.IndentSpacing = 0.0f; //Pas d'indentation des tree

  //Colors
  ImGui::PushStyleColor(ImGuiCol_FrameBg, IM_COL32(112, 112, 112, 127)); //Frame background
  ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(200, 200, 200, 127)); //Button color
  ImGui::PushStyleColor(ImGuiCol_Header, IM_COL32(76, 76, 76, 124));
  ImGui::PushStyleColor(ImGuiCol_Tab, IM_COL32(117, 117, 117, 220));
  ImGui::PushStyleColor(ImGuiCol_Border, IM_COL32(0, 0, 0, 255));

  //IO parameters
  io.ConfigWindowsResizeFromEdges = true;

  //---------------------------
}
void VK_gui::gui_font(){
  VkDevice device = vk_device->get_device();
  VkCommandPool command_pool = vk_command->get_command_pool();
  VkQueue queue_graphics = vk_device->get_queue_graphics();
  //---------------------------

  // Use any command queue
  std::vector<VkCommandBuffer> command_buffer_vec = vk_command->get_command_buffer_vec();
  VkCommandBuffer command_buffer = command_buffer_vec[currentFrame];

  VkResult result = vkResetCommandPool(device, command_pool, 0);
  if(result != VK_SUCCESS){
    throw std::runtime_error("gui font error");
  }

  VkCommandBufferBeginInfo begin_info = {};
  begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
  begin_info.flags |= VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
  result = vkBeginCommandBuffer(command_buffer, &begin_info);
  if(result != VK_SUCCESS){
    throw std::runtime_error("gui font error");
  }

  ImGui_ImplVulkan_CreateFontsTexture(command_buffer);

  VkSubmitInfo end_info = {};
  end_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
  end_info.commandBufferCount = 1;
  end_info.pCommandBuffers = &command_buffer;
  result = vkEndCommandBuffer(command_buffer);
  if(result != VK_SUCCESS){
    throw std::runtime_error("gui font error");
  }

  result = vkQueueSubmit(queue_graphics, 1, &end_info, VK_NULL_HANDLE);
  if(result != VK_SUCCESS){
    throw std::runtime_error("gui font error");
  }

  result = vkDeviceWaitIdle(device);
  if(result != VK_SUCCESS){
    throw std::runtime_error("gui font error");
  }

  ImGui_ImplVulkan_DestroyFontUploadObjects();

  //---------------------------
}

//Loop functions
void VK_gui::loop_start(){
  //---------------------------

  ImGui_ImplVulkan_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  //---------------------------
}
void VK_gui::loop_end(){
  //---------------------------

  ImGui::Render();
  this->draw_data = ImGui::GetDrawData();

  //---------------------------
}
