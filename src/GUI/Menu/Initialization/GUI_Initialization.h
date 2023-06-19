#ifndef GUI_INITIALIZATION_H
#define GUI_INITIALIZATION_H

#include "struct_treefile.h"
#include "struct_init.h"
#include "../../../common.h"

class Node_gui;
class Scene;
class Loader;
class Transformation;


class GUI_Initialization
{
public:
  //Constructor / Destructor
  GUI_Initialization(Node_gui* node_gui);
  ~GUI_Initialization();

public:
  //Main funxtion
  void init_gui();
  void update_configuration();

  //Operation on loaded cloud
  void operation_new_collection(Object* object);
  void operation_option();

  //Spacific scene construction
  void build_scene_1();
  void build_scene_2();
  void build_scene_3();

  //Treenode construction
  void treeview();
  void construst_tree();
  void construct_node_scene(vector<vector<Struct_treefile*>>& nodes_path_vec);
  void construct_node(string path, vector<Struct_treefile*>& nodes);
  void construct_node_root(vector<string>& vec_path, vector<Struct_treefile*>& nodes);
  void display_node(Struct_treefile* node, vector<Struct_treefile*>& all_nodes);
  void display_node_root(vector<Struct_treefile*>& all_nodes);
  void node_child_scan(string path, vector<Struct_treefile*>& nodes, Struct_treefile* parent);
  bool check_file_format(string path);
  void open_selection(Struct_treefile* node);

private:
  Scene* sceneManager;
  Loader* loaderManager;
  Transformation* transformManager;

  vector<Struct_treefile*> nodes_root;
  vector<vector<Struct_treefile*>> nodes_path_vec;
  vector<string> accepted_format;
  vector<string> path_init_vec;
  vector<string> path_init_file;
  bool with_remove_cloud;
  bool with_onthefly;
  float object_scale;
  string lidar_model;
};

#endif
