
#include "GUI.h"

#include "../Vulkan/Instance/VK_window.h"
#include "../Vulkan/Instance/VK_instance.h"
#include "../Vulkan/Device/VK_device.h"
#include "../Vulkan/Pipeline/VK_renderpass.h"
#include "../Vulkan/Engine_vulkan.h"
#include "../Vulkan/Command/VK_command.h"
#include "../Vulkan/VK_parameter.h"

#include "../Node_engine.h"


//Constructor / Destructor
GUI::GUI(Node_engine* node_engine){
  //---------------------------

  this->engine_vulkan = node_engine->get_engine_vulkan();
  this->vk_window = engine_vulkan->get_vk_window();
  this->vk_instance = engine_vulkan->get_vk_instance();
  this->vk_device = engine_vulkan->get_vk_device();
  this->vk_renderpass = engine_vulkan->get_vk_renderpass();

  //---------------------------
}
GUI::~GUI(){
  //---------------------------


  //---------------------------
}

static void check_vk_result(VkResult err)
{
    if (err == 0)
        return;
    fprintf(stderr, "[vulkan] Error: VkResult = %d\n", err);
    if (err < 0)
        abort();
}

//Main function
void GUI::init(){
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
  VkDescriptorPoolSize pool_sizes[] =
  {
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
  //init_info.QueueFamily = 0;
  init_info.DescriptorPool = imguiPool;
  init_info.PipelineCache = VK_NULL_HANDLE;
  //init_info.Allocator = nullptr;
  init_info.MinImageCount = 3;
  init_info.ImageCount = 3;
  //init_info.Subpass = 0;
  init_info.MSAASamples = VK_SAMPLE_COUNT_1_BIT;
  init_info.CheckVkResultFn = check_vk_result;

  ImGui_ImplVulkan_Init(&init_info, renderPass);


  // Upload Fonts
  {
      // Use any command queue
      VK_command* vk_command = engine_vulkan->get_vk_command();
      VkCommandPool command_pool = vk_command->get_command_pool();
      std::vector<VkCommandBuffer> command_buffer_vec = vk_command->get_command_buffer_vec();
      VkCommandBuffer command_buffer = command_buffer_vec[currentFrame];
sayHello();
      VkResult err = vkResetCommandPool(device, command_pool, 0);
      check_vk_result(err);
      VkCommandBufferBeginInfo begin_info = {};
      begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
      begin_info.flags |= VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
      err = vkBeginCommandBuffer(command_buffer, &begin_info);
      check_vk_result(err);
sayHello();
      ImGui_ImplVulkan_CreateFontsTexture(command_buffer);

      VkSubmitInfo end_info = {};
      end_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
      end_info.commandBufferCount = 1;
      end_info.pCommandBuffers = &command_buffer;
      err = vkEndCommandBuffer(command_buffer);
      check_vk_result(err);
      err = vkQueueSubmit(queue_graphics, 1, &end_info, VK_NULL_HANDLE);
      check_vk_result(err);

      err = vkDeviceWaitIdle(device);
      check_vk_result(err);
      ImGui_ImplVulkan_DestroyFontUploadObjects();
  }


  //---------------------------
}
void GUI::cleanup(){
  VkDevice device = vk_device->get_device();
  //---------------------------

  vkDestroyDescriptorPool(device, imguiPool, nullptr);

  ImGui_ImplVulkan_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  //---------------------------
}

void GUI::loop(){
  //---------------------------

//sayHello();
  // Start the Dear ImGui frame
ImGui_ImplVulkan_NewFrame();
ImGui_ImplGlfw_NewFrame();
ImGui::NewFrame();


ImGui::Text("Hello, world %d", 123);
if (ImGui::Button("Save"))
{
  // do stuff
}

  ImGui::ShowDemoWindow();
  ImGui::Render();
  this->draw_data = ImGui::GetDrawData();
  // Record dear imgui primitives into command buffer
  //ImGui_ImplVulkan_RenderDrawData(draw_data, fd->CommandBuffer);


  //---------------------------
}
void GUI::command_gui(VkCommandBuffer command_buffer){
  //---------------------------

  ImGui_ImplVulkan_RenderDrawData(draw_data, command_buffer);

  //---------------------------
}
void GUI::loop_start(){
  GLFWwindow* window = vk_window->get_window();
  //---------------------------

  // Start the Dear ImGui frame
  ImGui_ImplVulkan_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  ImGui::Text("Hello, world %d", 123);
if (ImGui::Button("Save"))
{
    // do stuff
}


  ImGui::Render();
  //ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), cmd);

  //imgui commands
  //ImGui::ShowDemoWindow();


  //---------------------------
}
void GUI::loop_end(){
  //---------------------------

  // Rendering
  ImGui::Render();
  //ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), cmd);

  //---------------------------
}
void GUI::show_basic_stuff(){
  //---------------------------

  ImGui::Text("Hello, world %d", 123);
  if (ImGui::Button("Save")){}

  //---------------------------
}
