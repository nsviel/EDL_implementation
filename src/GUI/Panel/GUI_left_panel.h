#ifndef GUI_LEFT_PAN_H
#define GUI_LEFT_PAN_H

#include "../../common.h"

#include "../../../extern/imgui/imgui.h"
#include "../../../extern/imgui/imgui_impl_glfw.h"
#include "../../../extern/imgui/imgui_impl_vulkan.h"

class Node;
class Node_engine;
class Dimension;


class GUI_left_panel
{
public:
  //Constructor / Destructor
  GUI_left_panel(Node* node);
  ~GUI_left_panel();

public:
  //Main functions
  void draw_left_panel();
  void left_panel_dim();
  void left_panel_menu();
  void left_panel_content();

private:
  Node_engine* node_engine;
  Dimension* dimManager;
};

#endif
