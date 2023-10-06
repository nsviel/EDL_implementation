#ifndef GUI_NODE_H
#define GUI_NODE_H

#include <Specific/common.h>

class Engine;
class Render_node;
class Data_node;

class GUI_param;
class GUI_panel;
class GUI_control;
class GUI_option;
class GUI_object;
class GUI_menubar;
class GUI_windows;
class GUI_shader;
class GUI_profiling;
class GUI_style;
class GUI_init;
class GUI_editor_text;
class GUI_editor_node;
class GUI_engine;
class Control;
class Window;


class GUI_node
{
public:
  //Constructor / Destructor
  GUI_node(Engine* engine);
  ~GUI_node();

public:
  void init();
  void loop();

  inline Engine* get_engine(){return engine;}
  inline Render_node* get_node_render(){return render_node;}
  inline Data_node* get_data_node(){return data_node;}
  inline Window* get_window(){return window;}

  inline GUI_param* get_gui_param(){return gui_param;}
  inline GUI_panel* get_gui_panel(){return gui_panel;}
  inline GUI_control* get_gui_control(){return gui_control;}
  inline GUI_option* get_gui_option(){return gui_option;}
  inline GUI_object* get_gui_object(){return gui_object;}
  inline GUI_menubar* get_gui_menubar(){return gui_menubar;}
  inline GUI_windows* get_gui_windows(){return gui_windows;}
  inline GUI_shader* get_gui_shader(){return gui_shader;}
  inline GUI_profiling* get_gui_profiling(){return gui_profiling;}
  inline GUI_style* get_gui_style(){return gui_style;}
  inline GUI_init* get_gui_init(){return gui_init;}
  inline GUI_editor_text* get_gui_editor_text(){return gui_editor_text;}
  inline GUI_engine* get_gui_engine(){return gui_engine;}
  inline Control* get_controlManager(){return controlManager;}


private:
  Engine* engine;
  Render_node* render_node;
  Data_node* data_node;
  Window* window;

  GUI_param* gui_param;
  GUI_panel* gui_panel;
  GUI_control* gui_control;
  GUI_option* gui_option;
  GUI_object* gui_object;
  GUI_menubar* gui_menubar;
  GUI_windows* gui_windows;
  GUI_shader*gui_shader;
  GUI_profiling* gui_profiling;
  GUI_style* gui_style;
  GUI_init* gui_init;
  GUI_editor_text* gui_editor_text;
  GUI_engine* gui_engine;
  GUI_editor_node* gui_editor_node;
  Control* controlManager;
};

#endif
