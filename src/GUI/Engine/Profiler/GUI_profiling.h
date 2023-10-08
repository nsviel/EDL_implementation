#ifndef GUI_PROFILING_H
#define GUI_PROFILING_H

#include <Specific/common.h>
#include <imgui/profiler/ImGuiProfilerRenderer.h>

class GUI;
class Render_node;
class VK_engine;
class VK_param;


class GUI_profiling
{
public:
  //Constructor / Destructor
  GUI_profiling(GUI* gui);
  ~GUI_profiling();

public:
  //Main function
  void design_panel();

  //Subfunctions
  void design_profiling();

private:
  GUI* gui;
  Render_node* render_node;
  VK_engine* vk_engine;
  VK_param* vk_param;
  Timer timer;

  int width;
  ImGuiUtils::ProfilersWindow* profiler;
};

#endif
