#ifndef GUI_PROFILING_H
#define GUI_PROFILING_H

#include "../../common.h"

class Node_gui;
class Node_engine;
class VK_engine;
class VK_param;


class GUI_profiling
{
public:
  //Constructor / Destructor
  GUI_profiling(Node_gui* node_gui);
  ~GUI_profiling();

public:
  //Main function
  void design_profiling();

  //Subfunctions
  void device_model();
  bool time_update();
  void time_drawig(bool update);
  void time_general(bool update);

private:
  Node_gui* node_gui;
  Node_engine* node_engine;
  VK_engine* vk_engine;
  VK_param* vk_param;
  Timer timer;

  int width;
};

#endif
