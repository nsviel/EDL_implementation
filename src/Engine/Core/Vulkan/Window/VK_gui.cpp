#include "VK_gui.h"
#include "VK_window.h"

#include "../Instance/VK_instance.h"

#include "../VK_engine.h"
#include "../VK_param.h"
#include "../Device/VK_device.h"
#include "../Device/VK_physical_device.h"
#include "../Data/VK_buffer.h"
#include "../Renderpass/VK_renderpass.h"
#include "../Command/VK_command_buffer.h"
#include "../Command/VK_command.h"
#include "../Presentation/VK_frame.h"
#include "../Image/VK_image.h"

#include "image/IconsFontAwesome5.h"


//Constructor / Destructor
VK_gui::VK_gui(VK_engine* vk_engine){
  //---------------------------

  this->vk_engine = vk_engine;
  this->vk_param = vk_engine->get_vk_param();
  this->vk_command_buffer = vk_engine->get_vk_command_buffer();
  this->vk_command = vk_engine->get_vk_command();
  this->vk_window = vk_engine->get_vk_window();
  this->vk_instance = vk_engine->get_vk_instance();
  this->vk_device = vk_engine->get_vk_device();
  this->vk_renderpass = vk_engine->get_vk_renderpass();
  this->vk_physical_device = vk_engine->get_vk_physical_device();
  this->vk_frame = vk_engine->get_vk_frame();
  this->vk_buffer = vk_engine->get_vk_buffer();
  this->vk_image = vk_engine->get_vk_image();

  //---------------------------
}
VK_gui::~VK_gui(){}

//Main function
void VK_gui::clean_gui(){
  VK_device* vk_device = vk_engine->get_vk_device();
  //---------------------------

  vkDestroyDescriptorPool(vk_param->device.device, imguiPool, nullptr);

  ImGui_ImplVulkan_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  //---------------------------
}
void VK_gui::command_gui(Struct_renderpass* renderpass){
  //---------------------------

  ImGui_ImplVulkan_RenderDrawData(draw_data, renderpass->command_buffer);

  //---------------------------
}

//Init function
void VK_gui::init_gui(){
  //---------------------------

  this->gui_vulkan();
  this->gui_select_font();
  this->gui_load_font();

  //---------------------------
}
void VK_gui::gui_vulkan(){
  GLFWwindow* window = vk_window->get_window();
  VkSurfaceKHR surface = vk_window->get_surface();
  VkRenderPass renderPass = vk_param->renderpass_ui.renderpass;
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

  VkResult result = vkCreateDescriptorPool(vk_param->device.device, &pool_info, nullptr, &imguiPool);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create gui");
  }

  // Setup Platform/Renderer bindings
  ImGui_ImplGlfw_InitForVulkan(window, true);
  ImGui_ImplVulkan_InitInfo init_info = {};
  init_info.Instance = vk_param->instance.instance;
  init_info.PhysicalDevice = vk_param->device.physical_device;
  init_info.Device = vk_param->device.device;
  init_info.Queue = vk_param->device.queue_graphics;
  init_info.DescriptorPool = imguiPool;
  init_info.PipelineCache = VK_NULL_HANDLE;
  init_info.MinImageCount = 3;
  init_info.ImageCount = 3;
  init_info.MSAASamples = VK_SAMPLE_COUNT_1_BIT;

  ImGui_ImplVulkan_Init(&init_info, renderPass);

  //---------------------------
}
void VK_gui::gui_select_font(){
  ImGuiIO io = ImGui::GetIO();
  static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
  //---------------------------

  //Configuration - texte
  ImFontConfig config_text;
  config_text.GlyphExtraSpacing.x = 1.0f;

  //Configuration - icon
  ImFontConfig config_icon;
  config_icon.MergeMode = true;
  config_icon.GlyphMinAdvanceX = 15.0f; //Monospace icons

  float font_size = 13.0f;
  for(int i=0; i<10; i++){
    io.Fonts->AddFontFromFileTTF("../src/GUI/Style/Font/DroidSans.ttf", font_size, &config_text);
    io.Fonts->AddFontFromFileTTF("../src/GUI/Style/Font/fontawesome-webfont.ttf", font_size - 0.5f, &config_icon, icons_ranges);
    font_size += 1.0f;
  }

  //Buid the font database
  io.Fonts->Build();

  //---------------------------
}
void VK_gui::gui_load_font(){
  VkCommandPool command_pool = vk_command_buffer->get_command_pool();
  //---------------------------

  VkResult result = vkResetCommandPool(vk_param->device.device, command_pool, 0);
  if(result != VK_SUCCESS){
    throw std::runtime_error("gui font error");
  }

  VkCommandBufferBeginInfo begin_info = {};
  begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
  begin_info.flags |= VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
  result = vkBeginCommandBuffer(vk_param->renderpass_ui.command_buffer, &begin_info);
  if(result != VK_SUCCESS){
    throw std::runtime_error("gui font error");
  }

  ImGui_ImplVulkan_CreateFontsTexture(vk_param->renderpass_ui.command_buffer);

  VkSubmitInfo end_info = {};
  end_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
  end_info.commandBufferCount = 1;
  end_info.pCommandBuffers = &vk_param->renderpass_ui.command_buffer;
  result = vkEndCommandBuffer(vk_param->renderpass_ui.command_buffer);
  if(result != VK_SUCCESS){
    throw std::runtime_error("gui font error");
  }

  result = vkQueueSubmit(vk_param->device.queue_graphics, 1, &end_info, VK_NULL_HANDLE);
  if(result != VK_SUCCESS){
    throw std::runtime_error("gui font error");
  }

  result = vkDeviceWaitIdle(vk_param->device.device);
  if(result != VK_SUCCESS){
    throw std::runtime_error("gui font error");
  }

  ImGui_ImplVulkan_DestroyFontUploadObjects();

  //---------------------------
}
void VK_gui::gui_image(){
  VkCommandPool command_pool = vk_command_buffer->get_command_pool();
  //---------------------------

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
    memAllocInfo.memoryTypeIndex = vk_buffer->findMemoryType(memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
    vkAllocateMemory(vk_param->device.device, &memAllocInfo, nullptr, &dst_image_memory[i]);
    vkBindImageMemory(vk_param->device.device, viewport_image[i], dst_image_memory[i], 0);

    VkCommandBuffer copyCmd = vk_command->singletime_command_begin();

    vk_command->image_layout_transition(copyCmd, &vk_param->swapchain.vec_frame[i]->color, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

    vk_command->singletime_command_end(copyCmd);
  }

  //create image view
  viewport_image_view.resize(viewport_image.size());

  for (uint32_t i = 0; i < viewport_image.size(); i++){
    viewport_image_view[i] = vk_image->create_image_view(viewport_image[i], VK_FORMAT_B8G8R8A8_SRGB, VK_IMAGE_ASPECT_COLOR_BIT);
  }

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
