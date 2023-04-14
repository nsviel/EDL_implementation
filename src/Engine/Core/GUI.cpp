#include "GUI.h"

#include "../Vulkan/VK_window.h"
#include "../Vulkan/Engine_vulkan.h"

#include "../Node_engine.h"

#include "../../../extern/imgui/imgui.h"
#include "../../../extern/imgui/imgui_impl_glfw.h"
#include "../../../extern/imgui/imgui_impl_vulkan.h"

//Constructor / Destructor
GUI::GUI(Node_engine* node_engine){
  //---------------------------


  this->engine_vulkan = node_engine->get_engine_vulkan();
  this->vk_window = engine_vulkan->get_vk_window();

  //---------------------------
}
GUI::~GUI(){
  //---------------------------


  //---------------------------
}

//Main function
void GUI::init(){
  GLFWwindow* window = vk_window->get_window();
  VkInstance instance = engine_vulkan->get_vk_instance();
  VkPhysicalDevice physical_device = engine_vulkan->get_physical_device();
  VkDevice device = engine_vulkan->get_device();
  VkSurfaceKHR surface = engine_vulkan->get_vk_surface();
  VkQueue queue_graphics = engine_vulkan->get_queue_graphics();
  VkRenderPass renderPass = engine_vulkan->get_renderPass();
  //---------------------------

  //1: create descriptor pool for IMGUI
	// the size of the pool is very oversize, but it's copied from imgui demo itself.
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

	VkDescriptorPool imguiPool;
	VkResult result = vkCreateDescriptorPool(device, &pool_info, nullptr, &imguiPool);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to create gui");
  }

  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();

  // Setup Platform/Renderer backends
  ImGui_ImplGlfw_InitForVulkan(window, true);
  ImGui_ImplVulkan_InitInfo init_info = {};
  init_info.Instance = instance;
  init_info.PhysicalDevice = physical_device;
  init_info.Device = device;
  init_info.Queue = queue_graphics;
  init_info.DescriptorPool = imguiPool;
  init_info.MinImageCount = 3;
  init_info.ImageCount = 3;
  init_info.MSAASamples = VK_SAMPLE_COUNT_1_BIT;
  ImGui_ImplVulkan_Init(&init_info, renderPass);

  //execute a gpu command to upload imgui font textures
	/*immediate_submit([&](VkCommandBuffer cmd) {
		ImGui_ImplVulkan_CreateFontsTexture(cmd);
  });*/


  //---------------------------
}
void GUI::cleanup(){
  //---------------------------

  ImGui_ImplVulkan_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  //---------------------------
}

void GUI::loop(){
  //---------------------------

  this->loop_start();
  //this->show_basic_stuff();
  //this->loop_end();

  //---------------------------
}
void GUI::loop_start(){
  GLFWwindow* window = vk_window->get_window();
  //---------------------------

  // Start the Dear ImGui frame
  ImGui_ImplVulkan_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  //ImGui::NewFrame();

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
