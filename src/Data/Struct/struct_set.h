#ifndef SET_STRUCT_H
#define SET_STRUCT_H

#include "struct_object.h"
#include "../../common.h"


//Collection are cloud containers
struct Set
{
  //---------------------------

  Set(std::string name);
  void reset();

  std::string name;
  std::list<Object*> list_obj;
  int nb_obj;

  //---------------------------
};

#endif
