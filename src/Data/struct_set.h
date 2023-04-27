#ifndef SET_STRUCT_H
#define SET_STRUCT_H

#include "../common.h"


//Collection are cloud containers
struct Set
{
  //---------------------------

  Set(std::string name);
  void reset();

  std::string name;
  std::list<Cloud*> list_cloud;

  //---------------------------
};

#endif
