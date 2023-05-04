#ifndef GUI_H
#define GUI_H

#include "../common.h"

#include "../../extern/imgui/imgui.h"
#include "../../extern/imgui/imgui_impl_glfw.h"
#include "../../extern/imgui/imgui_impl_vulkan.h"

class Node_engine;
class Dimension;


class GUI
{
public:
  //Constructor / Destructor
  GUI(Node_engine* node_engine);
  ~GUI();

public:
  //Main functions

  //Loop functions
  void loop();

private:
  Node_engine* node_engine;
  Dimension* dimManager;
};

#endif
