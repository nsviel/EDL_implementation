#ifndef ENGINE_H
#define ENGINE_H

#include "common.h"

class Render_node;
class GUI_node;
class Data_node;
class Window;


class Engine
{
public:
  //Constructor / Destructor
  Engine(Window* window);
  ~Engine();

public:
  void init();
  void loop();
  void exit();
  void reset();

  inline Render_node* get_node_render(){return render_node;}
  inline GUI_node* get_gui_node(){return gui_node;}
  inline Data_node* get_data_node(){return data_node;}
  inline Window* get_window(){return window;}

private:
  Render_node* render_node;
  GUI_node* gui_node;
  Data_node* data_node;
  Window* window;
};

#endif
