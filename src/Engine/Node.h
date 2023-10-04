#ifndef NODE_H
#define NODE_H

#include "common.h"

class Node_core;
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

  inline Node_core* get_node_core(){return node_core;}
  inline Node_gui* get_node_gui(){return node_gui;}
  inline Data_node* get_data_node(){return data_node;}

private:
  Node_core* node_core;
  Node_gui* node_gui;
  Data_node* data_node;
};

#endif
