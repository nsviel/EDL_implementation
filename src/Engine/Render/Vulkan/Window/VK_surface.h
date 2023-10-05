#ifndef VK_WINDOW_H
#define VK_WINDOW_H

#include "../../Render_common.h"

class VK_engine;
class Dimension;
class VK_param;
class Window;


class VK_surface
{
public:
  //Constructor / Destructor
  VK_surface(VK_engine* vk_engine);
  ~VK_surface();

public:
  //Main functions
  void init_window(Window* window);
  void clean_surface();

  //Subfunction
  void create_window_surface();
  void check_for_resizing();
  void get_required_extensions();

  inline GLFWwindow* get_window(){return window;}
  inline VkSurfaceKHR get_surface(){return surface;}
  inline vec2 get_window_dim(){return window_dim;}

private:
  Window* window_class;
  GLFWwindow* window;
  VK_param* vk_param;
  Dimension* dimManager;

  VkSurfaceKHR surface;
  vec2 window_dim;
};

#endif
