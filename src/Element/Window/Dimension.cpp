#include "Dimension.h"


//Constructor / Destructor
Dimension::Dimension(){
  //---------------------------

  this->win_dim = glm::vec2(0);
  this->init();

  //---------------------------
}
Dimension::~Dimension(){}

//Main functions
void Dimension::init(){
  //---------------------------
  
  //Rendering tab
  Tab* tab_rendering = new Tab("rendering");
  tab_rendering->pos = glm::vec2(100, 0);
  tab_rendering->dim = glm::vec2(100, 100);
  this->list_tab.push_back(tab_rendering);

  //---------------------------
}
Tab* Dimension::get_tab(std::string name){
  //---------------------------

  for(int i=0; i<list_tab.size(); i++){
    Tab* tab = *std::next(list_tab.begin(), i);
    if(tab->name == name){
      return tab;
    }
  }

  //---------------------------
  return nullptr;
}

//Update function
void Dimension::update(){
  Tab* tab_rendering = get_tab("rendering");
  //---------------------------

  this->update_window_dim();

  tab_rendering->dim.x = win_dim.x;
  tab_rendering->dim.y = win_dim.y;
  tab_rendering->center = glm::vec2(tab_rendering->dim.x/2, tab_rendering->dim.y/2);

  //---------------------------
}
void Dimension::update_window_dim(){
  //---------------------------

  //Check window size
  int win_w = 0;
  int win_h = 0;
  glfwGetWindowSize(window, &win_w, &win_h);

  //Set up new values
  if(win_w != win_dim.x || win_h != win_dim.y){
    this->win_dim = glm::vec2(win_w, win_h);
  }

  //---------------------------
}

//Subfunctions
glm::vec2 Dimension::get_gl_middle(){
  //---------------------------

  int x = gui_ltp_dim.x;
  int y = gui_tp_dim.y;
  glm::vec2 gl_middle = glm::vec2(x, y);

  //---------------------------
  return gl_middle;
}
glm::vec2 Dimension::get_cursorPos_gl(){
  double xpos, ypos;
  glm::vec2 pos = glm::vec2(0, 0);
  //---------------------------

  glfwGetCursorPos(window, &xpos, &ypos);
  pos = glm::vec2(xpos, ypos);

  //---------------------------
  return pos;
}
glm::vec2 Dimension::get_mouse_pose(){
  double xpos, ypos;
  glm::vec2 pos = glm::vec2(0, 0);
  //---------------------------

  glfwGetCursorPos(window, &xpos, &ypos);
  pos = glm::vec2(xpos, ypos);

  //---------------------------
  return pos;
}
void Dimension::set_mouse_pose(glm::vec2 pos){
  //---------------------------

  glfwSetCursorPos(window, pos.x, pos.y);

  //---------------------------
}
void Dimension::set_mouse_visibility(bool visible){
  //---------------------------

  if(visible){
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
  }else{
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  }

  //---------------------------
}