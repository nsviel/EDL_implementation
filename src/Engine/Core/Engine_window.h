#ifndef ENGINE_WINDOW_H
#define ENGINE_WINDOW_H

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Node_engine;


class Engine_window
{
public:
  //Constructor / Destructor
  Engine_window(Node_engine* node_engine);
  ~Engine_window();

public:
  //Main functions
  void init_window();
  void clean_window();

  //Subfunction
  VkSurfaceKHR create_window_surface(VkInstance instance);
  glm::vec2 get_framebuffer_size();
  bool check_for_resizing();

  inline GLFWwindow* get_window(){return window;}
  inline VkSurfaceKHR get_vk_surface(){return surface;}

private:
  GLFWwindow* window;
  glm::vec2 render_dim;
  VkSurfaceKHR surface;
};

#endif
