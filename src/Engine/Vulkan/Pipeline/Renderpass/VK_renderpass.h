#ifndef VK_RENDERPASS_H
#define VK_RENDERPASS_H

#include "../../Struct/struct_renderpass.h"
#include "../../Struct/struct_pipeline.h"
#include "../../../../common.h"

class VK_engine;
class VK_param;
class VK_color;
class VK_pipeline;
class VK_subpass;
class VK_scene;


class VK_renderpass
{
public:
  //Constructor / Destructor
  VK_renderpass(VK_engine* vk_engine);
  ~VK_renderpass();

public:
  //Main functions
  void init_renderpass();
  void clean_renderpass();
  void clean_renderpass_object(Struct_renderpass* renderpass);

  //Render pass object
  void init_renderpass_canvas(Struct_renderpass* renderpass);
  void init_renderpass_gui(Struct_renderpass* renderpass);

  //Subfunction
  void create_renderpass(Struct_renderpass* renderpass);
  void create_depth_attachment(Struct_renderpass* renderpass);
  void create_color_attachment(Struct_renderpass* renderpass);
  void create_subpass(Struct_subpass* subpass);
  void create_renderpass_obj(Struct_renderpass* renderpass);
  void create_renderpass_frame(Struct_renderpass* renderpass, string sw_or_rp);

private:
  VK_engine* vk_engine;
  VK_param* vk_param;
  VK_color* vk_color;
  VK_pipeline* vk_pipeline;
  VK_subpass* vk_subpass;
  VK_scene* vk_scene;
};

#endif
