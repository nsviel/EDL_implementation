#include "UI_main.h"
#include "UI_vulkan.h"

#define GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include <Window/Window.h>

#include <imgui/core/imgui.h>
#include <imgui/core/imgui_impl_glfw.h>
#include <imgui/core/imgui_internal.h>
#include <imgui/vulkan/imgui_impl_vulkan.h>
#include <stdio.h>          // printf, fprintf
#include <stdlib.h>         // abort



//Constructor / Destructor
UI_main::UI_main(Window* window){
  //---------------------------

  this->window = window;
  this->ui_vulkan = new UI_vulkan();

  //---------------------------
}
UI_main::~UI_main(){}

// Main code
void UI_main::init_gui(){
  //---------------------------

  //Extentions
  ImVector<const char*> extensions;
  uint32_t extensions_count = 0;
  const char** glfw_extensions = glfwGetRequiredInstanceExtensions(&extensions_count);
  for (uint32_t i = 0; i < extensions_count; i++){
    extensions.push_back(glfw_extensions[i]);
  }
  ui_vulkan->SetupVulkan(extensions);

  // Create Window Surface
  VkSurfaceKHR surface;
  window->create_window_surface(ui_vulkan->g_Instance, surface);

  //VkResult err = glfwCreateWindowSurface(ui_vulkan->g_Instance, window->get_window(), ui_vulkan->g_Allocator, &surface);
  //ui_vulkan->check_vk_result(err);

  // Create Framebuffers
  int w, h;
  glfwGetFramebufferSize(window->get_window(), &w, &h);
  this->wd = &ui_vulkan->g_MainWindowData;
  ui_vulkan->SetupVulkanWindow(wd, surface, w, h);

  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO(); (void)io;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
  io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
  //io.ConfigViewportsNoAutoMerge = true;
  //io.ConfigViewportsNoTaskBarIcon = true;

  // Setup Dear ImGui style
  ImGui::StyleColorsDark();

  // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
  ImGuiStyle& style = ImGui::GetStyle();
  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable){
      style.WindowRounding = 0.0f;
      style.Colors[ImGuiCol_WindowBg].w = 1.0f;
  }

  // Setup Platform/Renderer backends
  //ImGui_ImplGlfw_InitForVulkan(window->get_window(), true);
  ImGui_ImplVulkan_InitInfo init_info = {};
  init_info.Instance = ui_vulkan->g_Instance;
  init_info.PhysicalDevice = ui_vulkan->g_PhysicalDevice;
  init_info.Device = ui_vulkan->g_Device;
  init_info.QueueFamily = ui_vulkan->g_QueueFamily;
  init_info.Queue = ui_vulkan->g_Queue;
  init_info.PipelineCache = ui_vulkan->g_PipelineCache;
  init_info.DescriptorPool = ui_vulkan->g_DescriptorPool;
  init_info.Subpass = 0;
  init_info.MinImageCount = ui_vulkan->g_MinImageCount;
  init_info.ImageCount = wd->ImageCount;
  init_info.MSAASamples = VK_SAMPLE_COUNT_1_BIT;
  init_info.Allocator = ui_vulkan->g_Allocator;
  ImGui_ImplVulkan_Init(&init_info, wd->RenderPass);

  // Upload Fonts
  // Use any command queue
  VkCommandPool command_pool = wd->Frames[wd->FrameIndex].CommandPool;
  VkCommandBuffer command_buffer = wd->Frames[wd->FrameIndex].CommandBuffer;

  VkResult err = vkResetCommandPool(ui_vulkan->g_Device, command_pool, 0);
  ui_vulkan->check_vk_result(err);
  VkCommandBufferBeginInfo begin_info = {};
  begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
  begin_info.flags |= VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
  err = vkBeginCommandBuffer(command_buffer, &begin_info);
  ui_vulkan->check_vk_result(err);

  ImGui_ImplVulkan_CreateFontsTexture(command_buffer);

  VkSubmitInfo end_info = {};
  end_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
  end_info.commandBufferCount = 1;
  end_info.pCommandBuffers = &command_buffer;
  err = vkEndCommandBuffer(command_buffer);
  ui_vulkan->check_vk_result(err);
  err = vkQueueSubmit(ui_vulkan->g_Queue, 1, &end_info, VK_NULL_HANDLE);
  ui_vulkan->check_vk_result(err);

  err = vkDeviceWaitIdle(ui_vulkan->g_Device);
  ui_vulkan->check_vk_result(err);
  ImGui_ImplVulkan_DestroyFontUploadObjects();

  //---------------------------
}
void UI_main::clean_gui(){
  //---------------------------

  // Cleanup
  VkResult err = vkDeviceWaitIdle(ui_vulkan->g_Device);
  ui_vulkan->check_vk_result(err);
  ImGui_ImplVulkan_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  ui_vulkan->CleanupVulkanWindow();
  ui_vulkan->CleanupVulkan();

  glfwDestroyWindow(window->get_window());
  glfwTerminate();

  //---------------------------
}
void UI_main::run_gui_main(){
  //---------------------------

  // Our state
  ImGuiIO& io = ImGui::GetIO(); (void)io;
  bool show_demo_window = true;
  bool show_another_window = false;
  ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

  // Resize swap chain?
  if (ui_vulkan->g_SwapChainRebuild){
    int width, height;
    glfwGetFramebufferSize(window->get_window(), &width, &height);
    if (width > 0 && height > 0){
      ImGui_ImplVulkan_SetMinImageCount(ui_vulkan->g_MinImageCount);
      ImGui_ImplVulkanH_CreateOrResizeWindow(ui_vulkan->g_Instance, ui_vulkan->g_PhysicalDevice, ui_vulkan->g_Device, &ui_vulkan->g_MainWindowData, ui_vulkan->g_QueueFamily, ui_vulkan->g_Allocator, width, height, ui_vulkan->g_MinImageCount);
      ui_vulkan->g_MainWindowData.FrameIndex = 0;
      ui_vulkan->g_SwapChainRebuild = false;
    }
  }

  // Start the Dear ImGui frame
  ImGui_ImplVulkan_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
  if (show_demo_window){
    ImGui::ShowDemoWindow(&show_demo_window);
  }
  {
    static float f = 0.0f;
    static int counter = 0;

      ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

      ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
      ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
      ImGui::Checkbox("Another Window", &show_another_window);

      ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
      ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

      if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
          counter++;
      ImGui::SameLine();
      ImGui::Text("counter = %d", counter);

      ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
      ImGui::End();
  }
  if (show_another_window){
    ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
    ImGui::Text("Hello from another window!");
    if (ImGui::Button("Close Me"))
        show_another_window = false;
    ImGui::End();
  }

  // Rendering
  ImGui::Render();
  ImDrawData* main_draw_data = ImGui::GetDrawData();
  const bool main_is_minimized = (main_draw_data->DisplaySize.x <= 0.0f || main_draw_data->DisplaySize.y <= 0.0f);
  wd->ClearValue.color.float32[0] = clear_color.x * clear_color.w;
  wd->ClearValue.color.float32[1] = clear_color.y * clear_color.w;
  wd->ClearValue.color.float32[2] = clear_color.z * clear_color.w;
  wd->ClearValue.color.float32[3] = clear_color.w;
  if (!main_is_minimized){
    ui_vulkan->FrameRender(wd, main_draw_data);
  }

  // Update and Render additional Platform Windows
  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable){
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
  }

  // Present Main Platform Window
  if (!main_is_minimized){
    ui_vulkan->FramePresent(wd);
  }

  //---------------------------
  //out loop -> this->clean_gui();
}
