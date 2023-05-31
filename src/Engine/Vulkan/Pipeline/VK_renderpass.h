#ifndef VK_RENDERPASS_H
#define VK_RENDERPASS_H

#include "../Struct/struct_renderpass.h"
#include "../../../common.h"

class VK_engine;
class Param_vulkan;
class VK_color;


class VK_renderpass
{
public:
  //Constructor / Destructor
  VK_renderpass(VK_engine* vk_engine);
  ~VK_renderpass();

public:
  //Main functions
  void init_renderpass();
  void cleanup();

  //Subfunction
  void create_depth_attachment(Struct_renderpass* renderpass);
  void create_color_attachment(Struct_renderpass* renderpass);
  void create_subpass(Struct_renderpass* renderpass);
  void create_renderpass_info(Struct_renderpass* renderpass);
  void create_renderpass(Struct_renderpass* renderpass);

  inline VkRenderPass get_renderPass(){return renderpass->renderpass;}

private:
  VK_engine* vk_engine;
  Param_vulkan* param_vulkan;
  VK_color* vk_color;

  Struct_renderpass* renderpass;
};

#endif
