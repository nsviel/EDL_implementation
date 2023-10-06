#ifndef UI_MAsssIN_H
#define UI_MAsssIN_H

#include <imgui/core/imgui.h>
#include <imgui/core/imgui_impl_glfw.h>
#include <imgui/core/imgui_internal.h>
#include <imgui/vulkan/imgui_impl_vulkan.h>

class UI_vulkan;
class Window;


class UI_main
{
public:
  //Constructor / Destructor
  UI_main(Window* window);
  ~UI_main();

public:
  //Main functions
  void init_gui();
  void clean_gui();
  void run_gui_main();

private:
  Window* window;
  UI_vulkan* ui_vulkan;

  ImGui_ImplVulkanH_Window* wd;
};

#endif
