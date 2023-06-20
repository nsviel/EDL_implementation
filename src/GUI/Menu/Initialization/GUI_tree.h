#ifndef GUI_TREE_H
#define GUI_TREE_H

#include "struct_node.h"
#include "struct_init.h"
#include "../../../common.h"


class GUI_tree
{
public:
  //Constructor / Destructor
  GUI_tree();
  ~GUI_tree();

public:
  //Main funxtion
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
  vector<Tree_node*> nodes_root;
  vector<vector<Tree_node*>> nodes_path_vec;

  Struct_init init;
};

#endif
