#ifndef UI_LOOP_H
#define UI_LOOP_H

#include <imgui/core/imgui.h>
#include <imgui/core/imgui_impl_glfw.h>
#include <imgui/core/imgui_internal.h>
#include <imgui/vulkan/imgui_impl_vulkan.h>

class Engine;


class UI_loop
{
public:
  //Constructor / Destructor
  UI_loop();
  ~UI_loop();

public:
  //Main functions
  void loop(Engine* engine);
  void loop_start();
  void loop_end();
  void loop_draw(VkCommandBuffer command);

private:
  ImDrawData* draw_data;
};

#endif
