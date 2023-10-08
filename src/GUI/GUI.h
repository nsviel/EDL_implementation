#ifndef GUI_NODE_H
#define GUI_NODE_H

#include <Specific/common.h>

class Engine;
class Render_node;
class Data_node;

class Panel;
class GUI_panel;
class GUI_control;
class GUI_option;
class GUI_scene;
class GUI_mainmenubar;
class GUI_shader;
class GUI_timing;
class GUI_style;
class GUI_init;
class GUI_editor_text;
class GUI_editor_node;
class GUI_engine;
class GUI_camera;
class GUI_object;
class GUI_set;
class Window;


class GUI
{
public:
  //Constructor / Destructor
  GUI(Engine* engine);
  ~GUI();

public:
  void init();
  void loop();

  inline Engine* get_engine(){return engine;}
  inline Render_node* get_node_render(){return render_node;}
  inline Data_node* get_data_node(){return data_node;}
  inline Window* get_window(){return window;}

  inline Panel* get_panel(){return panel;}
  inline GUI_panel* get_gui_panel(){return gui_panel;}
  inline GUI_control* get_gui_control(){return gui_control;}
  inline GUI_option* get_gui_option(){return gui_option;}
  inline GUI_scene* get_gui_scene(){return gui_scene;}
  inline GUI_mainmenubar* get_gui_menubar(){return gui_menubar;}
  inline GUI_shader* get_gui_shader(){return gui_shader;}
  inline GUI_timing* get_gui_profiling(){return gui_timing;}
  inline GUI_style* get_gui_style(){return gui_style;}
  inline GUI_init* get_gui_init(){return gui_init;}
  inline GUI_editor_text* get_gui_editor_text(){return gui_editor_text;}
  inline GUI_engine* get_gui_engine(){return gui_engine;}
  inline GUI_object* get_gui_object(){return gui_object;}
  inline GUI_set* get_gui_set(){return gui_set;}

private:
  Engine* engine;
  Render_node* render_node;
  Data_node* data_node;
  Window* window;
  Panel* panel;
  
  GUI_panel* gui_panel;
  GUI_control* gui_control;
  GUI_option* gui_option;
  GUI_scene* gui_scene;
  GUI_mainmenubar* gui_menubar;
  GUI_shader*gui_shader;
  GUI_timing* gui_timing;
  GUI_style* gui_style;
  GUI_init* gui_init;
  GUI_editor_text* gui_editor_text;
  GUI_engine* gui_engine;
  GUI_editor_node* gui_editor_node;
  GUI_object* gui_object;
  GUI_camera* gui_camera;
  GUI_set* gui_set;
};

#endif
