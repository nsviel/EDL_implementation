#ifndef NODE_H
#define NODE_H

#include "common.h"

class Render_node;
class Node_gui;
class Data_node;


class Node
{
public:
  //Constructor / Destructor
  Node();
  ~Node();

public:
  void init();
  void loop();
  void exit();
  void reset();

  inline Render_node* get_core_node(){return core_node;}
  inline Node_gui* get_node_gui(){return node_gui;}
  inline Data_node* get_data_node(){return data_node;}

private:
  Render_node* core_node;
  Node_gui* node_gui;
  Data_node* data_node;
};

#endif
