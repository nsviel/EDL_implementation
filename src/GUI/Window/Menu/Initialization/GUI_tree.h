#ifndef GUI_TREE_H
#define GUI_TREE_H

#include "struct_node.h"
#include "struct_init.h"
#include <Specific/common.h>

class GUI_init;


class GUI_tree
{
public:
  //Constructor / Destructor
  GUI_tree(GUI_init* gui_init);
  ~GUI_tree();

public:
  //Main function
  void design_tree();
  void construct_tree(Struct_init* init);

  //subfunction
  void construct_node(string path, vector<Tree_node*>& nodes);
  void construct_node_root(vector<string>& vec_path, vector<Tree_node*>& nodes);
  void display_node(Tree_node* node, vector<Tree_node*>& all_nodes);
  void display_node_root(vector<Tree_node*>& all_nodes);
  void node_child_scan(string path, vector<Tree_node*>& nodes, Tree_node* parent);
  bool check_display_file_format(string path);
  void open_selection(Tree_node* node);

private:
  GUI_init* gui_init;

  vector<Tree_node*> nodes_root;
  vector<vector<Tree_node*>> nodes_path_vec;
  Struct_init* init;
};

#endif
