#ifndef GUI_INITIALIZATION_H
#define GUI_INITIALIZATION_H

#include "Initialization/struct_node.h"
#include "Initialization/struct_init.h"
#include "../../common.h"

class GUI_node;
class Scene;
class Loader;
class Transformation;
class GUI_tree;


class GUI_init
{
public:
  //Constructor / Destructor
  GUI_init(GUI_node* gui_node);
  ~GUI_init();

public:
  //Main funxtion
  void design_init();
  void design_option();

  //Subfunction
  void init_init();
  void load_config_file();
  void operation_new_object(string path);

  //Custom scene
  void build_custom_scene(vector<vector<Tree_node*>>& nodes_path_vec);
  void build_scene_1();

private:
  Scene* sceneManager;
  Loader* loaderManager;
  Transformation* transformManager;
  GUI_tree* gui_tree;

  vector<Tree_node*> nodes_root;
  vector<vector<Tree_node*>> nodes_path_vec;

  Struct_init init;
};

#endif
