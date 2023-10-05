#ifndef DIMENSION_H
#define DIMENSION_H

#include "struct_tab.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>
#include <list>


class Dimension
{
public:
  Dimension();
  ~Dimension();

public:
  //Main functions
  void init();
  Tab* get_tab(std::string name);

  //Update function
  void update();
  void update_window_dim();

  //Subfunctions
  glm::vec2 get_gl_middle();
  glm::vec2 get_cursorPos_gl();
  glm::vec2 get_mouse_pose();
  void set_mouse_pose(glm::vec2 pos);
  void set_mouse_visibility(bool visible);

  inline GLFWwindow* get_window(){return window;}
  inline void set_window(GLFWwindow* win){this->window = win;}

  inline void set_gl_dim(glm::vec2 value){this->gl_dim = value;}
  inline glm::vec2 get_gl_dim(){update();return gl_dim;}
  inline glm::vec2 get_gl_pos(){update();return gl_pos;}
  inline glm::vec2 get_win_dim(){update();return win_dim;}
  inline void set_is_resized(bool value){this->is_resized = value;}
  inline bool get_is_resized(){return is_resized;}
  inline bool* get_with_custom_gl_dim(){return &with_custom_gl_dim;}

private:
  GLFWwindow* window;
  std::list<Tab*> list_tab;
  glm::vec2 win_dim;

  //Rendering
  glm::vec2 gl_pos;
  glm::vec2 gl_dim;

  //GUI
  glm::vec2 gui_ltp_dim;
  glm::vec2 gui_ltp_pos;
  glm::vec2 gui_lbp_dim;
  glm::vec2 gui_lbp_pos;
  glm::vec2 gui_tp_dim;
  glm::vec2 gui_bp_dim;
  glm::vec2 gui_bp_pos;
  float gui_lp_mid;

  //Flag
  bool with_custom_gl_dim;
  bool is_visualization;
  bool is_resized;
};

#endif
