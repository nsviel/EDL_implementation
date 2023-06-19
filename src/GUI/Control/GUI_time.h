#ifndef GUI_TIME_H
#define GUI_TIME_H

#include "../../common.h"

class Node_gui;
class Node_engine;
class VK_engine;
class VK_param;


class GUI_time
{
public:
  //Constructor / Destructor
  GUI_time(Node_gui* node_gui);
  ~GUI_time();

public:
  //Main function
  void design_time();

  //Subfunctions
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
