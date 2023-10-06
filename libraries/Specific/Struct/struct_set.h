#ifndef STRUCT_SET_H
#define STRUCT_SET_H

#include <Specific/Struct/struct_object.h>
#include <string>
#include <vector>
#include <list>


//Collection are cloud containers
struct Set
{
  //---------------------------

  Set(std::string name);
  void reset();

  //Info
  std::string name;
  int nb_object = 0;
  bool is_visible = true;

  //Data
  Object* selected_obj = nullptr;
  std::list<Object*> list_obj;
  std::list<Set*> list_set;

  //---------------------------
};

#endif
