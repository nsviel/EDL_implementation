#ifndef NODE_GUI_H
#define NODE_GUI_H

#include "../common.h"

class Node;
class Node_engine;
class Node_data;
class Node_load;

class GUI_param;
class GUI_panel;
class GUI_control;
class GUI_option;
class GUI_filemanager;
class GUI_menubar;
class GUI_windows;
class GUI_shader;
class GUI_profiling;
class GUI_style;
class GUI_init;
class GUI_editor;


class Node_gui
{
public:
  //Constructor / Destructor
  Node_gui(Node* node);
  ~Node_gui();

public:
  void init();
  void loop();

  inline Node_engine* get_node_engine(){return node_engine;}
  inline Node_data* get_node_data(){return node_data;}
  inline Node_load* get_node_load(){return node_load;}

  inline GUI_param* get_gui_param(){return gui_param;}
  inline GUI_panel* get_gui_panel(){return gui_panel;}
  inline GUI_control* get_gui_control(){return gui_control;}
  inline GUI_option* get_gui_option(){return gui_option;}
  inline GUI_filemanager* get_gui_filemanager(){return gui_filemanager;}
  inline GUI_menubar* get_gui_menubar(){return gui_menubar;}
  inline GUI_windows* get_gui_windows(){return gui_windows;}
  inline GUI_shader* get_gui_shader(){return gui_shader;}
  inline GUI_profiling* get_gui_profiling(){return gui_profiling;}
  inline GUI_style* get_gui_style(){return gui_style;}
  inline GUI_init* get_gui_init(){return gui_init;}
  inline GUI_editor* get_gui_editor(){return gui_editor;}

private:
  Node_engine* node_engine;
  Node_data* node_data;
  Node_load* node_load;

  GUI_param* gui_param;
  GUI_panel* gui_panel;
  GUI_control* gui_control;
  GUI_option* gui_option;
  GUI_filemanager* gui_filemanager;
  GUI_menubar* gui_menubar;
  GUI_windows* gui_windows;
  GUI_shader*gui_shader;
  GUI_profiling* gui_profiling;
  GUI_style* gui_style;
  GUI_init* gui_init;
  GUI_editor* gui_editor;
};

#endif
