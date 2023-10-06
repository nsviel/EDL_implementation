#ifndef GUI_DATA_H
#define GUI_DATA_H

#include <Specific/common.h>

class GUI;
class Render_node;
class VK_engine;
class VK_param;


class GUI_data
{
public:
  //Constructor / Destructor
  GUI_data(GUI* gui);
  ~GUI_data();

public:
  //Main function
  void design_data();

  //Subfunction


private:
  GUI* gui;
  Render_node* render_node;
  VK_engine* vk_engine;
  VK_param* vk_param;

  int width;
};

#endif
