#ifndef UI_MAIN_H
#define UI_MAIN_H

#include <imgui/core/imgui.h>
#include <imgui/core/imgui_impl_glfw.h>
#include <imgui/core/imgui_internal.h>
#include <imgui/vulkan/imgui_impl_vulkan.h>


class UI_main
{
public:
  //Constructor / Destructor
  UI_main();
  ~UI_main();

public:
  //Main functions
  int run_gui_main();


private:
  ImDrawData* draw_data;
};

#endif
