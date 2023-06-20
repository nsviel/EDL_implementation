#ifndef GUI_INITIALIZATION_H
#define GUI_INITIALIZATION_H

#include "struct_node.h"
#include "struct_init.h"
#include "../../../common.h"

class Node_gui;
class Scene;
class Loader;
class Transformation;


class GUI_init
{
public:
  //Constructor / Destructor
  GUI_init(Node_gui* node_gui);
  ~GUI_init();

public:
  //Main funxtion
  void design_init();
  void init_init();

  //Operation on loaded cloud
  void design_operation_option();
  void operation_new_object(Object* object);

  //Custom scene
  void build_custom_scene(vector<vector<Tree_node*>>& nodes_path_vec);
  void build_scene_1();

  //Treenode construction
  void treeview();
  void construst_tree();
  void construct_node(string path, vector<Tree_node*>& nodes);
  void construct_node_root(vector<string>& vec_path, vector<Tree_node*>& nodes);
  void display_node(Tree_node* node, vector<Tree_node*>& all_nodes);
  void display_node_root(vector<Tree_node*>& all_nodes);
  void node_child_scan(string path, vector<Tree_node*>& nodes, Tree_node* parent);
  bool check_file_format(string path);
  void open_selection(Tree_node* node);

private:
  Scene* sceneManager;
  Loader* loaderManager;
  Transformation* transformManager;

  vector<Tree_node*> nodes_root;
  vector<vector<Tree_node*>> nodes_path_vec;

  Struct_init init;
};

#endif
