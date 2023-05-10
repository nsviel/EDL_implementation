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

  //Info
  int nb_obj = 0;
  std::string name;

  //Data
  Object* selected_obj = nullptr;
  std::list<Object*> list_obj;
  std::list<Set*> list_set;

  //---------------------------
};

#endif
