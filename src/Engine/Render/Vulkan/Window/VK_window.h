#ifndef VK_WINDOW_H
#define VK_WINDOW_H

#include "../../Render_common.h"

class VK_engine;
class Dimension;
class VK_param;
class VK_instance;
class VK_viewport;


class VK_window
{
public:
  //Constructor / Destructor
  VK_window(VK_engine* vk_engine);
  ~VK_window();

public:
  //Main functions
  void init_window();
  void clean_surface();
  void clean_window();

  //Subfunction
  void create_window_surface();
  void check_for_resizing();
  vec2 get_framebuffer_size();
  void get_required_extensions();

  inline GLFWwindow* get_window(){return window;}
  inline VkSurfaceKHR get_surface(){return surface;}

private:
  GLFWwindow* window;
  VK_param* vk_param;
  Dimension* dimManager;
  VK_instance* vk_instance;
  VK_viewport* vk_viewport;

  VkSurfaceKHR surface;
  vec2 window_dim;
};

#endif
