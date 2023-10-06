#ifndef GUI_PARAM_H
#define GUI_PARAM_H

#include <Specific/Struct/struct_object.h>
#include <Specific/Struct/struct_set.h>
#include <string>
#include <vector>
#include <list>
#include <glm/glm.hpp>
#include <iostream>


struct GUI_param{
  //---------------------------

  bool show_camera;
  bool show_object;
  bool show_set;

  Object* object_selected;
  Set* set_selected;

  //---------------------------
};

#endif
