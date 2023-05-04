#ifndef DIMENSION_H
#define DIMENSION_H

#include "struct_tab.h"
#include "../../common.h"


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
  vec2 get_gl_middle();
  vec2 get_cursorPos_gl();
  vec2 get_mouse_pose();
  void set_mouse_pose(vec2 pos);

  inline GLFWwindow* get_window(){return window;}
  inline void set_window(GLFWwindow* win){this->window = win;}
  inline vec2* get_gui_ltp_dim(){update();return &gui_ltp_dim;}
  inline vec2* get_gui_ltp_pos(){update();return &gui_ltp_pos;}
  inline vec2* get_gui_lbp_dim(){update();return &gui_lbp_dim;}
  inline vec2* get_gui_lbp_pos(){update();return &gui_lbp_pos;}
  inline vec2* get_gui_bp_pos(){update();return &gui_bp_pos;}
  inline vec2* get_gui_bp_dim(){update();return &gui_bp_dim;}
  inline vec2* get_gui_tp_dim(){update();return &gui_tp_dim;}

  inline void set_gl_dim(vec2 value){this->gl_dim = value;}
  inline vec2 get_gl_dim(){update();return gl_dim;}
  inline vec2 get_gl_pos(){update();return gl_pos;}
  inline vec2 get_win_dim(){update();return win_dim;}
  inline void set_is_resized(bool value){this->is_resized = value;}
  inline bool get_is_resized(){return is_resized;}
  inline bool* get_with_custom_gl_dim(){return &with_custom_gl_dim;}

private:
  GLFWwindow* window;
  list<Tab*> list_tab;
  vec2 win_dim;





  //Rendering
  vec2 gl_pos;
  vec2 gl_dim;


  //GUI
  vec2 gui_ltp_dim;
  vec2 gui_ltp_pos;
  vec2 gui_lbp_dim;
  vec2 gui_lbp_pos;
  vec2 gui_tp_dim;
  vec2 gui_bp_dim;
  vec2 gui_bp_pos;
  float gui_lp_mid;

  //Flag
  bool with_custom_gl_dim;
  bool is_visualization;
  bool is_resized;
};

#endif
