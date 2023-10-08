#ifndef GUI_ENGINE_H
#define GUI_ENGINE_H

#include <Specific/common.h>

class GUI;
class VK_param;
class GUI_control;
class GUI_mainmenubar;

class GUI_engine
{
public:
  //Constructor / Destructor
  GUI_engine(GUI* gui);
  ~GUI_engine();

public:
  //Main functions
  void design_panel();

  //Subfunction
  void engine_window();
  void engine_menubar();

private:
  VK_param* vk_param;
  GUI_control* gui_control;
  GUI_mainmenubar* gui_menubar;

  VkDescriptorSet descriptor;
  bool has_been_initialized;
};

#endif
