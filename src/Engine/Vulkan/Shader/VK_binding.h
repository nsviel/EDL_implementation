#ifndef VK_BINDING_H
#define VK_BINDING_H

#include "../Struct/struct_binding.h"
#include "../../../common.h"

class Engine;
class Param_vulkan;


class VK_binding
{
public:
  //Constructor / Destructor
  VK_binding(Engine* engineManager);
  ~VK_binding();

public:
  //Main functions


private:
  Param_vulkan* param_vulkan;

};

#endif
