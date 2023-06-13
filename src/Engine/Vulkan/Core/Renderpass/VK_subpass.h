#ifndef VK_SUBPASS_H
#define VK_SUBPASS_H

#include "../../Struct/struct_renderpass.h"
#include "../../../../common.h"

class VK_engine;
class VK_param;


class VK_subpass
{
public:
  //Constructor / Destructor
  VK_subpass(VK_engine* vk_engine);
  ~VK_subpass();

public:
  //Main functions
  void create_subpass_clear_info(Struct_renderpass* renderpass);
  void create_subpass_conserve_info(Struct_renderpass* renderpass);

private:
  VK_engine* vk_engine;
  VK_param* vk_param;
};

#endif
