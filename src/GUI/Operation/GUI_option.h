#ifndef GUI_OPION_H
#define GUI_OPION_H

#include "../../common.h"

class Node;
class Param_engine;


class GUI_option
{
public:
  //Constructor / Destructor
  GUI_option(Node* node);
  ~GUI_option();

public:
  //Main function
  void design_option();

  //Subfunctions
  void option_color();
  void option_glyph();
  void option_parameter();
  void option_mode();
  void option_font();

private:
  Param_engine* param_engine;
  
  int width;
};

#endif
