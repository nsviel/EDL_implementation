#ifndef GUI_PROFILING_H
#define GUI_PROFILING_H

#include "../../common.h"

class GUI_node;
class Render_node;
class VK_engine;
class VK_param;


class GUI_profiling
{
public:
  //Constructor / Destructor
  GUI_profiling(GUI_node* gui_node);
  ~GUI_profiling();

public:
  //Main function
  void design_panel();
  void design_profiling();

  //Subfunctions
  void device_model();
  bool time_update();
  void time_drawig(bool update);
  void time_general(bool update);

private:
  GUI_node* gui_node;
  Render_node* render_node;
  VK_engine* vk_engine;
  VK_param* vk_param;
  Timer timer;

  int width;
};

#endif
