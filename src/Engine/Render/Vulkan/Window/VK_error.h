#ifndef VK_ERROR_H
#define VK_ERROR_H

#include "../Struct/struct_binding.h"
#include <Specific/common.h>

class VK_engine;
class VK_param;


class VK_error
{
public:
  //Constructor / Destructor
  VK_error(VK_engine* vk_engine);
  ~VK_error();

public:
  //Binding error
  void uniform_name_not_recognized(Struct_binding* binding, string name);
  void sampler_name_not_recognized(Struct_binding* binding, string name);

private:
  VK_engine* vk_engine;
  VK_param* vk_param;

};

#endif
